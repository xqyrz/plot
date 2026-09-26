//
// Created by 25137 on 2026/9/26.
//

#include "dwarfapp.h"

extern "C" {
#include <libdwarf.h>
#include <dwarf.h>
}

#include <cstdio>
#include <map>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------
// 说明：本工程自带的 libdwarf 为 0.9.0 老版本，API 与现代版不同。
// 以下按 0.9.0 的真实签名编写：
//   dwarf_init_path(..., DW_GROUPNUMBER_ANY, ...)
//   dwarf_next_cu_header_d(dbg, is_info, ...)
//   dwarf_siblingof_b / dwarf_child / dwarf_tag
//   dwarf_attr + dwarf_whatform + dwarf_formstring / dwarf_formflag / dwarf_formudata
//   dwarf_formblock + dwarf_global_formref_b + dwarf_offdie_b
// 返回值约定：DW_DLV_OK=0, DW_DLV_NO_ENTRY=-1, DW_DLV_ERROR=1
// ---------------------------------------------------------------
namespace {

constexpr Dwarf_Bool IS_INFO = 1;   // 遍历 .debug_info

// ---------- 基础属性读取 ----------

std::string attrString(Dwarf_Debug dbg, Dwarf_Die die,
                       Dwarf_Half attrnum, Dwarf_Error* err)
{
    Dwarf_Attribute attr = nullptr;
    if (dwarf_attr(die, attrnum, &attr, err) != DW_DLV_OK || !attr) {
        return std::string();
    }
    std::string result;
    Dwarf_Half form = 0;
    if (dwarf_whatform(attr, &form, err) == DW_DLV_OK
        && (form == DW_FORM_string || form == DW_FORM_strp)) {
        char* s = nullptr;
        if (dwarf_formstring(attr, &s, err) == DW_DLV_OK && s) {
            result = s;
            dwarf_dealloc(dbg, s, DW_DLA_STRING);
        }
    }
    dwarf_dealloc_attribute(attr);
    return result;
}

// 读取 DIE 上一个整数属性（data/udata/sdata 形式）
bool getUIntAttr(Dwarf_Debug dbg, Dwarf_Die die, Dwarf_Half attrnum,
                 Dwarf_Unsigned* out, Dwarf_Error* err)
{
    Dwarf_Attribute a = nullptr;
    if (dwarf_attr(die, attrnum, &a, err) != DW_DLV_OK || !a) {
        return false;
    }
    Dwarf_Half form = 0;
    dwarf_whatform(a, &form, err);
    bool ok = false;
    if (form == DW_FORM_data1 || form == DW_FORM_data2
        || form == DW_FORM_data4 || form == DW_FORM_data8
        || form == DW_FORM_udata || form == DW_FORM_sdata) {
        if (dwarf_formudata(a, out, err) == DW_DLV_OK) {
            ok = true;
        }
    }
    dwarf_dealloc_attribute(a);
    return ok;
}

// 取 die 的 DW_AT_type 指向的类型 DIE（跨 CU 也支持）。返回的 DIE 由调用方 dealloc。
Dwarf_Die getTypeDie(Dwarf_Debug dbg, Dwarf_Die die, Dwarf_Error* err)
{
    Dwarf_Attribute a = nullptr;
    if (dwarf_attr(die, DW_AT_type, &a, err) != DW_DLV_OK || !a) {
        return nullptr;
    }
    Dwarf_Off off = 0;
    Dwarf_Bool isInfo = 0;
    int rc = dwarf_global_formref_b(a, &off, &isInfo, err);
    dwarf_dealloc_attribute(a);
    if (rc != DW_DLV_OK) {
        return nullptr;
    }
    Dwarf_Die td = nullptr;
    if (dwarf_offdie_b(dbg, off, isInfo, &td, err) != DW_DLV_OK) {
        return nullptr;
    }
    return td;
}

// ---------- 类型展开 ----------

std::string describeType(Dwarf_Debug dbg, Dwarf_Die die,
                         Dwarf_Error* err, int depth);

// 数组维度，如 [8][16]（遍历 DW_TAG_subrange_type 子 DIE）
std::string arrayDims(Dwarf_Debug dbg, Dwarf_Die arrayDie, Dwarf_Error* err, int depth)
{
    std::string dims;
    Dwarf_Die c = nullptr;
    if (dwarf_child(arrayDie, &c, err) != DW_DLV_OK || !c) {
        return dims;
    }
    Dwarf_Die cur = c;
    while (cur) {
        Dwarf_Half tag = 0;
        dwarf_tag(cur, &tag, err);
        if (tag == DW_TAG_subrange_type) {
            Dwarf_Unsigned count = 0;
            Dwarf_Unsigned ub = 0;
            std::string n;
            if (getUIntAttr(dbg, cur, DW_AT_count, &count, err)) {
                n = "[" + std::to_string(count) + "]";
            } else if (getUIntAttr(dbg, cur, DW_AT_upper_bound, &ub, err)) {
                n = "[" + std::to_string(ub + 1) + "]";
            } else {
                n = "[]";
            }
            dims += n;
        }
        Dwarf_Die next = nullptr;
        int r = dwarf_siblingof_b(dbg, cur, IS_INFO, &next, err);
        dwarf_dealloc(dbg, cur, DW_DLA_DIE);
        cur = next;
        if (r != DW_DLV_OK) {
            break;
        }
    }
    if (cur) {
        dwarf_dealloc(dbg, cur, DW_DLA_DIE);
    }
    return dims;
}

// 成员偏移（DW_AT_data_member_location：unsigned 形式或 DW_OP_plus_uconst block）
std::string memberOffset(Dwarf_Debug dbg, Dwarf_Die die, Dwarf_Error* err)
{
    Dwarf_Attribute a = nullptr;
    if (dwarf_attr(die, DW_AT_data_member_location, &a, err) != DW_DLV_OK || !a) {
        return std::string();
    }
    Dwarf_Half form = 0;
    dwarf_whatform(a, &form, err);
    std::string r;
    Dwarf_Unsigned val = 0;
    if (form == DW_FORM_data1 || form == DW_FORM_data2
        || form == DW_FORM_data4 || form == DW_FORM_data8
        || form == DW_FORM_udata || form == DW_FORM_sdata) {
        if (dwarf_formudata(a, &val, err) == DW_DLV_OK) {
            char buf[32];
            std::snprintf(buf, sizeof(buf), "@0x%llx", (unsigned long long)val);
            r = buf;
        }
    } else if (form == DW_FORM_block || form == DW_FORM_block1
               || form == DW_FORM_block2 || form == DW_FORM_block4
               || form == DW_FORM_exprloc) {
        Dwarf_Block* blk = nullptr;
        if (dwarf_formblock(a, &blk, err) == DW_DLV_OK && blk
            && blk->bl_len >= 2 && blk->bl_data) {
            const unsigned char* p =
                reinterpret_cast<const unsigned char*>(blk->bl_data);
            if (p[0] == DW_OP_plus_uconst) {   // 0x23
                char buf[32];
                std::snprintf(buf, sizeof(buf), "@0x%llx", (unsigned long long)p[1]);
                r = buf;
            }
        }
    }
    dwarf_dealloc_attribute(a);
    return r;
}

// 结构体/联合体成员："@0x0 u16 Version; @0x2 u16 ..."
std::string describeMembers(Dwarf_Debug dbg, Dwarf_Die die,
                            Dwarf_Error* err, int depth)
{
    std::string out;
    Dwarf_Die c = nullptr;
    if (dwarf_child(die, &c, err) != DW_DLV_OK || !c) {
        return out;
    }
    Dwarf_Die cur = c;
    while (cur) {
        Dwarf_Half tag = 0;
        dwarf_tag(cur, &tag, err);
        if (tag == DW_TAG_member) {
            std::string mname = attrString(dbg, cur, DW_AT_name, err);
            Dwarf_Die td = getTypeDie(dbg, cur, err);
            std::string mt = td ? describeType(dbg, td, err, depth + 1) : "";
            if (td) {
                dwarf_dealloc(dbg, td, DW_DLA_DIE);
            }
            std::string off = memberOffset(dbg, cur, err);
            std::string seg;
            if (!off.empty()) { seg += off + " "; }
            if (!mt.empty())  { seg += mt + " "; }
            if (!mname.empty()) { seg += mname; }
            if (!seg.empty()) {
                if (!out.empty()) { out += "; "; }
                out += seg;
            }
        }
        Dwarf_Die next = nullptr;
        int r = dwarf_siblingof_b(dbg, cur, IS_INFO, &next, err);
        dwarf_dealloc(dbg, cur, DW_DLA_DIE);
        cur = next;
        if (r != DW_DLV_OK) {
            break;
        }
    }
    if (cur) {
        dwarf_dealloc(dbg, cur, DW_DLA_DIE);
    }
    return out;
}

// 枚举成员："A=0, B=1"
std::string describeEnumerators(Dwarf_Debug dbg, Dwarf_Die die,
                                Dwarf_Error* err)
{
    std::string out;
    Dwarf_Die c = nullptr;
    if (dwarf_child(die, &c, err) != DW_DLV_OK || !c) {
        return out;
    }
    Dwarf_Die cur = c;
    while (cur) {
        Dwarf_Half tag = 0;
        dwarf_tag(cur, &tag, err);
        if (tag == DW_TAG_enumerator) {
            std::string n = attrString(dbg, cur, DW_AT_name, err);
            Dwarf_Unsigned v = 0;
            getUIntAttr(dbg, cur, DW_AT_const_value, &v, err);
            std::string seg = n + "=" + std::to_string(v);
            if (!out.empty()) { out += ", "; }
            out += seg;
        }
        Dwarf_Die next = nullptr;
        int r = dwarf_siblingof_b(dbg, cur, IS_INFO, &next, err);
        dwarf_dealloc(dbg, cur, DW_DLA_DIE);
        cur = next;
        if (r != DW_DLV_OK) {
            break;
        }
    }
    if (cur) {
        dwarf_dealloc(dbg, cur, DW_DLA_DIE);
    }
    return out;
}

// 核心：把类型 DIE 展开为可读字符串，结构体/联合体递归展开成员，直到基本类型。
std::string describeType(Dwarf_Debug dbg, Dwarf_Die die, Dwarf_Error* err, int depth)
{
    if (!die || depth > 12) {
        return std::string();
    }
    Dwarf_Half tag = 0;
    dwarf_tag(die, &tag, err);
    std::string name = attrString(dbg, die, DW_AT_name, err);

    switch (tag) {
        case DW_TAG_base_type:          // int、double、unsigned char ...
            return name.empty() ? "(base)" : name;

        case DW_TAG_pointer_type: {
            Dwarf_Die t = getTypeDie(dbg, die, err);
            std::string b;
            if (t) {
                b = describeType(dbg, t, err, depth + 1);
                dwarf_dealloc(dbg, t, DW_DLA_DIE);
            }
            return b + "*";
        }
        case DW_TAG_reference_type: {
            Dwarf_Die t = getTypeDie(dbg, die, err);
            std::string b;
            if (t) {
                b = describeType(dbg, t, err, depth + 1);
                dwarf_dealloc(dbg, t, DW_DLA_DIE);
            }
            return b + "&";
        }
        case DW_TAG_const_type:
        case DW_TAG_volatile_type: {
            const char* q = (tag == DW_TAG_const_type) ? "const " : "volatile ";
            Dwarf_Die t = getTypeDie(dbg, die, err);
            std::string b;
            if (t) {
                b = describeType(dbg, t, err, depth + 1);
                dwarf_dealloc(dbg, t, DW_DLA_DIE);
            }
            return std::string(q) + b;
        }
        case DW_TAG_typedef: {
            // 保留 typedef 名，同时展开到底层基本类型，如 "u16 (=unsigned short)"
            Dwarf_Die t = getTypeDie(dbg, die, err);
            if (t) {
                std::string base = describeType(dbg, t, err, depth + 1);
                dwarf_dealloc(dbg, t, DW_DLA_DIE);
                if (name.empty()) {
                    return base;
                }
                if (!base.empty() && base != name) {
                    return name + " (=" + base + ")";
                }
            }
            return name;
        }
        case DW_TAG_structure_type:
        case DW_TAG_union_type: {
            std::string s = name.empty()
                            ? ((tag == DW_TAG_structure_type) ? "struct" : "union")
                            : name;
            std::string m = describeMembers(dbg, die, err, depth);
            if (!m.empty()) {
                s += " { " + m + " }";
            }
            return s;
        }
        case DW_TAG_array_type: {
            Dwarf_Die t = getTypeDie(dbg, die, err);
            std::string b;
            if (t) {
                b = describeType(dbg, t, err, depth + 1);
                dwarf_dealloc(dbg, t, DW_DLA_DIE);
            }
            return b + arrayDims(dbg, die, err, depth);
        }
        case DW_TAG_enumeration_type: {
            std::string s = name.empty() ? "enum" : name;
            std::string m = describeEnumerators(dbg, die, err);
            if (!m.empty()) {
                s += " { " + m + " }";
            }
            return s;
        }
        default:
            if (!name.empty()) {
                return name;
            }
            {   // 无名类型：追底层类型
                Dwarf_Die t = getTypeDie(dbg, die, err);
                if (t) {
                    std::string b = describeType(dbg, t, err, depth + 1);
                    dwarf_dealloc(dbg, t, DW_DLA_DIE);
                    return b;
                }
            }
            return std::string();
    }
}

// 顶层类型名（只取类型 DIE 的名字，不展开）：MOTORCONTROL_STRUCT、uint32_t、char* ...
std::string topTypeName(Dwarf_Debug dbg, Dwarf_Die die, Dwarf_Error* err)
{
    Dwarf_Die t = getTypeDie(dbg, die, err);
    if (!t) {
        return std::string();
    }
    std::string name = attrString(dbg, t, DW_AT_name, err);
    dwarf_dealloc(dbg, t, DW_DLA_DIE);
    return name;
}

// ---------- 地址 ----------

uint64_t decodeGlobalAddress(Dwarf_Debug dbg, Dwarf_Die die, Dwarf_Error* err)
{
    Dwarf_Attribute attr = nullptr;
    if (dwarf_attr(die, DW_AT_location, &attr, err) != DW_DLV_OK || !attr) {
        return 0;
    }
    uint64_t addr = 0;
    Dwarf_Half form = 0;
    if (dwarf_whatform(attr, &form, err) == DW_DLV_OK) {
        if (form == DW_FORM_block || form == DW_FORM_block1
            || form == DW_FORM_block2 || form == DW_FORM_block4
            || form == DW_FORM_exprloc) {
            Dwarf_Block* blk = nullptr;
            if (dwarf_formblock(attr, &blk, err) == DW_DLV_OK && blk
                && blk->bl_len >= 2 && blk->bl_data) {
                const unsigned char* p =
                    reinterpret_cast<const unsigned char*>(blk->bl_data);
                if (p[0] == DW_OP_addr) {   // 0x03
                    int n = static_cast<int>(blk->bl_len) - 1;   // 小端地址字节
                    for (int i = n - 1; i >= 0; --i) {
                        addr = (addr << 8) | p[1 + i];
                    }
                }
            }
        }
    }
    dwarf_dealloc_attribute(attr);
    return addr;
}

// ---------- 主遍历 ----------

void collectGlobalVariables(Dwarf_Debug dbg, std::vector<GlobalVariableInfo>& out)
{
    Dwarf_Error err = nullptr;
    std::vector<GlobalVariableInfo> tmp;      // 原始结果
    std::map<std::string, size_t> nameIndex;  // 去重：同名保留有地址的

    Dwarf_Unsigned cuHeaderLen = 0, typeOffset = 0, nextCu = 0;
    Dwarf_Off abbrevOffset = 0;
    Dwarf_Half version = 0, addressSize = 0, lengthSize = 0;
    Dwarf_Half extensionSize = 0, headerCuType = 0;

    while (true) {
        int rc = dwarf_next_cu_header_d(dbg, IS_INFO, &cuHeaderLen, &version,
                                        &abbrevOffset, &addressSize, &lengthSize,
                                        &extensionSize, nullptr, &typeOffset,
                                        &nextCu, &headerCuType, &err);
        if (rc == DW_DLV_ERROR || rc == DW_DLV_NO_ENTRY) {
            break;
        }

        Dwarf_Die cuDie = nullptr;
        rc = dwarf_siblingof_b(dbg, nullptr, IS_INFO, &cuDie, &err);
        if (rc != DW_DLV_OK || !cuDie) {
            continue;
        }

        Dwarf_Die die = nullptr;
        int rc2 = dwarf_child(cuDie, &die, &err);
        while (rc2 == DW_DLV_OK && die) {
            Dwarf_Half tag = 0;
            if (dwarf_tag(die, &tag, &err) == DW_DLV_OK
                && tag == DW_TAG_variable) {
                std::string name = attrString(dbg, die, DW_AT_name, &err);
                if (!name.empty()) {
                    Dwarf_Attribute a = nullptr;
                    Dwarf_Bool external = 0;
                    if (dwarf_attr(die, DW_AT_external, &a, &err) == DW_DLV_OK
                        && a) {
                        dwarf_formflag(a, &external, &err);
                        dwarf_dealloc_attribute(a);
                    }

                    uint64_t addr = decodeGlobalAddress(dbg, die, &err);
                    if (external || addr != 0) {
                        GlobalVariableInfo v;
                        v.name       = name;
                        v.type       = topTypeName(dbg, die, &err);
                        {
                            Dwarf_Die td = getTypeDie(dbg, die, &err);
                            v.typeDetail = td ? describeType(dbg, td, &err, 0) : "";
                            if (td) {
                                dwarf_dealloc(dbg, td, DW_DLA_DIE);
                            }
                        }
                        v.address    = addr;
                        tmp.push_back(std::move(v));
                    }
                }
            }
            Dwarf_Die nextDie = nullptr;
            rc2 = dwarf_siblingof_b(dbg, die, IS_INFO, &nextDie, &err);
            dwarf_dealloc(dbg, die, DW_DLA_DIE);
            die = nextDie;
        }
        if (die) {
            dwarf_dealloc(dbg, die, DW_DLA_DIE);
        }
        dwarf_dealloc(dbg, cuDie, DW_DLA_DIE);
    }

    // 去重：同名变量优先保留有地址的（定义），跳过纯 extern 声明
    for (auto& v : tmp) {
        auto it = nameIndex.find(v.name);
        if (it == nameIndex.end()) {
            nameIndex[v.name] = out.size();
            out.push_back(std::move(v));
        } else if (v.address != 0) {
            out[it->second] = std::move(v);   // 用有地址的覆盖
        }
    }
}

} // namespace

// ---------------------------------------------------------------

DwarfApp::~DwarfApp() = default;

void DwarfApp::loadFile()
{
    m_vars.clear();
    if (m_filePath.empty()) {
        throw std::runtime_error(
            "DwarfApp: file path is empty, call setFilePath() first");
    }

    Dwarf_Debug dbg = nullptr;
    Dwarf_Error err = nullptr;
    char truePathBuf[1] = { 0 };

    int rc = dwarf_init_path(m_filePath.c_str(), truePathBuf,
                             sizeof(truePathBuf), DW_GROUPNUMBER_ANY,
                             nullptr, nullptr, &dbg, &err);
    if (rc != DW_DLV_OK) {
        std::string msg = "dwarf_init_path failed";
        if (err) {
            char* s = dwarf_errmsg(err);
            if (s) { msg += ": "; msg += s; }
            if (dbg) dwarf_dealloc_error(dbg, err);
        }
        throw std::runtime_error(msg);
    }

    try {
        collectGlobalVariables(dbg, m_vars);
    } catch (...) {
        dwarf_finish(dbg);
        throw;
    }

    dwarf_finish(dbg);
}
