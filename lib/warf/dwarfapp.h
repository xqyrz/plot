//
// Created by 25137 on 2026/9/26.
//

#ifndef PLOT_DWARFAPP_H
#define PLOT_DWARFAPP_H

#include <string>
#include <vector>
#include <cstdint>

// DLL 导出/导入宏：
//  - 构建 dwarfapp.dll 时，CMake 自动定义 dwarfapp_EXPORTS → dllexport（导出符号）
//  - 外部使用者 include 本头文件时 → dllimport（从导入库链接）
#ifdef _WIN32
#  ifdef dwarfapp_EXPORTS
#    define DWARFAPP_API __declspec(dllexport)
#  else
#    define DWARFAPP_API __declspec(dllimport)
#  endif
#else
#  define DWARFAPP_API
#endif
struct CuInfo
{
    uint64_t  start;                // CU 根 DIE 偏移
    uint64_t  end;                  // 下一个 CU 头偏移（本 CU 的 DIE 范围上界）
    std::vector<std::string> files;  // 该 CU 的源文件表
    std::string cuName;              // DW_AT_name（.c 源文件名）
    std::string compDir;             // DW_AT_comp_dir
};
// 类型详情：完整展开文本 + 该类型声明所在的源文件
struct TypeDetailInfo
{
    std::string text;       // 类型完整展开：结构体/联合体成员、数组维度、指针、
                            // typedef 展开到基本类型（int、double、uint8_t 等）
    std::string filePath;   // 该类型声明所在的源文件路径（DW_AT_decl_file）
};

// 描述结构体/联合体的一个成员（用于树形展开显示，可递归嵌套）
struct VarMemberInfo
{
    std::string name;        // 成员名
    std::string type;        // 成员顶层类型名
    uint64_t    offset = 0;  // 成员字节偏移（相对于所属结构体基址）
    uint64_t    size   = 0;  // 成员字节大小
    bool        isStructOrUnion = false; // 该成员本身是否为结构体/联合体（可继续展开）
    bool        isArray = false;         // 该成员本身是否为数组（可展开为元素）
    uint64_t    arrayCount = 0;         // 数组元素个数
    std::vector<VarMemberInfo> children; // 结构体成员的子成员（递归）
};

// 描述一个全局变量
struct GlobalVariableInfo
{
    std::string name;        // 变量名（DW_AT_name）
    std::string type;        // 顶层类型名（如 MOTORCONTROL_STRUCT、uint32_t、char*）
    TypeDetailInfo typeDetail;   // 类型完整展开 + 类型声明文件
    std::string filePath;    // 变量定义所在的源文件路径（DW_AT_decl_file）

    uint64_t    address;     // 地址（来自 DW_AT_location 的 DW_OP_addr）
    uint64_t    size = 0;    // 变量字节大小（DW_AT_byte_size / 数组累乘 / 结构体成员累加）

    bool        isArray = false;    // 顶层类型是否为数组
    uint64_t    arrayCount = 0;     // 数组元素个数（多维数组取总元素数）
    bool        isStatic = false;   // 是否为文件内 static（内部链接）
    std::vector<VarMemberInfo> members; // 结构体/联合体成员（非结构体时为空）
};

class DWARFAPP_API DwarfApp
{
    public:
        DwarfApp() = default;
        ~DwarfApp();

        void setFilePath(const std::string& path) { m_filePath = path; }

        // 加载并解析 AXF（ELF + DWARF）文件
        void loadFile();

        // 获取解析到的全局变量（loadFile 后可用）
        const std::vector<GlobalVariableInfo>& globalVariables() const { return m_vars; }
        const std::vector<CuInfo>& cus(){return m_cus;};

    private:
        std::string m_filePath;
        std::vector<GlobalVariableInfo> m_vars;
    std::vector<CuInfo> m_cus;
};


#endif // PLOT_DWARFAPP_H
