//
// Created by 25137 on 2026/9/26.
// 简易命令行验证程序： dwarfapp_test <file.axf>
//

#include "dwarfapp.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <functional>

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <file.axf>\n";
        return 1;
    }

    try {
        DwarfApp app;
        app.setFilePath(argv[1]);
        app.loadFile();

        const auto& vars = app.globalVariables();
        std::cout << "global variables: " << vars.size() << "\n\n";
        for (const auto& v : vars) {
            std::cout << "name=" << v.name
                      << "  type=" << v.type
                      << "  addr=0x" << std::hex << std::nouppercase
                      << v.address << std::dec
                      << "  size=" << v.size
                      << "  isArray=" << v.isArray
                      << "  arrayCount=" << v.arrayCount << "\n";
            if (!v.filePath.empty()) {
                std::cout << "      varfile  " << v.filePath << "\n";
            }
            if (!v.typeDetail.text.empty() && v.typeDetail.text != v.type) {
                std::cout << "      decl  " << v.typeDetail.text << "\n";
                if (!v.typeDetail.filePath.empty()) {
                    std::cout << "      typefile " << v.typeDetail.filePath << "\n";
                }
            }
            std::function<void(const std::vector<VarMemberInfo>&, int)> printRec;
            printRec = [&](const std::vector<VarMemberInfo>& ms, int depth) {
                std::string pad(depth * 2, ' ');
                for (const auto& m : ms) {
                    std::cout << "      " << pad << "member " << m.name
                              << "  type=" << m.type
                              << "  off=0x" << std::hex << m.offset << std::dec
                              << "  size=" << m.size
                              << (m.isStructOrUnion ? "  [struct]" : "") << "\n";
                    printRec(m.children, depth + 1);
                }
            };
            printRec(v.members, 0);
        }
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 2;
    }
    return 0;
}
