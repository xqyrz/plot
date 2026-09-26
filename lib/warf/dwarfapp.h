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

// 类型详情：完整展开文本 + 该类型声明所在的源文件
struct TypeDetailInfo
{
    std::string text;       // 类型完整展开：结构体/联合体成员、数组维度、指针、
                            // typedef 展开到基本类型（int、double、uint8_t 等）
    std::string filePath;   // 该类型声明所在的源文件路径（DW_AT_decl_file）
};

// 描述一个全局变量
struct GlobalVariableInfo
{
    std::string name;        // 变量名（DW_AT_name）
    std::string type;        // 顶层类型名（如 MOTORCONTROL_STRUCT、uint32_t、char*）
    TypeDetailInfo typeDetail;   // 类型完整展开 + 类型声明文件
    std::string filePath;    // 变量定义所在的源文件路径（DW_AT_decl_file）

    uint64_t    address;     // 地址（来自 DW_AT_location 的 DW_OP_addr）
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

    private:
        std::string m_filePath;
        std::vector<GlobalVariableInfo> m_vars;
};


#endif // PLOT_DWARFAPP_H
