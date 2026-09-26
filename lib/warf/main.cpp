//
// Created by 25137 on 2026/9/26.
// 简易命令行验证程序： dwarfapp_test <file.axf>
//

#include "dwarfapp.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>

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
                      << v.address << std::dec << "\n";
            if (!v.typeDetail.empty() && v.typeDetail != v.type) {
                std::cout << "      decl  " << v.typeDetail << "\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 2;
    }
    return 0;
}
