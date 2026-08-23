//
// Created by 25137 on 2026/8/23.
//
#include <srecord/arglex/tool.h>
#include <srecord/input/file.h>
#include <srecord/memory.h>
#include <srecord/record.h>

#include "binfile.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
BinFile::BinFile(std::string filePath)
{

}
BinFile::~BinFile()
{

}
bool BinFile::load(std::string filePath)
{
    return _load(filePath);
}
bool BinFile::_load(std::string filename)
{
    static const char* app_name = "srecord";
    char* filename_char = (char*)filename.c_str();
    int argc = 0;

    char* argv[3] = {(char*)app_name, (char*)filename_char, (char*)"-intel"};



    srecord::arglex_tool cmdline(argc, argv);
    cmdline.token_first();
    while (cmdline.token_cur() != srecord::arglex::token_eoln)
    {
        switch (cmdline.token_cur())
        {
        default:
            cmdline.default_command_line_processing();
            continue;

        case srecord::arglex_tool::token_paren_begin:
        case srecord::arglex_tool::token_string:
        case srecord::arglex_tool::token_stdio:
        case srecord::arglex_tool::token_generator:
           // infile.push_back(cmdline.get_input());
            continue;
        case srecord::arglex::token_verbose:
          //  verbose = true;
            break;
        }
        cmdline.token_next();
    }
    // Get input file pointer (auto-detects format)
    srecord::input::pointer ifp = cmdline.get_input();

    std::cout << "File format: " << ifp->get_file_format_name() << std::endl;
    std::cout << std::endl;

    // Read and process records
    srecord::record record;
    int record_count = 0;
    int data_record_count = 0;
    unsigned long total_data_bytes = 0;
    unsigned long start_address = 0;
    unsigned long end_address = 0;
    bool has_data = false;

    while (ifp->read(record))
    {
        record_count++;

        switch (record.get_type())
        {
        case srecord::record::type_header:
            {
                std::cout << "Header Record: ";
                if (record.get_length() > 0)
                {
                    std::string s((const char *)record.get_data(), record.get_length());
                    std::cout << s;
                }
                std::cout << std::endl;
            }
            break;

        case srecord::record::type_data:
            {
                data_record_count++;
                unsigned long addr = record.get_address();
                unsigned long len = record.get_length();
                total_data_bytes += len;

                if (!has_data)
                {
                    start_address = addr;
                    end_address = addr + len;
                    has_data = true;
                }
                else
                {
                    if (addr < start_address)
                        start_address = addr;
                    if (addr + len > end_address)
                        end_address = addr + len;
                }

                // Print first few data records as example
                if (data_record_count <= 5)
                {
                    std::cout << "Data Record #" << data_record_count << ": "
                              << "Address=0x" << std::hex << std::setw(8) << std::setfill('0')
                              << addr << ", Length=" << std::dec << len << ", Data=";

                    for (unsigned long i = 0; i < len && i < 16; ++i)
                    {
                        std::cout << std::hex << std::setw(2) << std::setfill('0')
                                  << (int)record.get_data()[i] << " ";
                    }
                    if (len > 16)
                        std::cout << "...";
                    std::cout << std::dec << std::endl;
                }
            }
            break;

        case srecord::record::type_execution_start_address:
            {
                std::cout << "Execution Start Address: 0x"
                          << std::hex << std::setw(8) << std::setfill('0')
                          << record.get_address() << std::dec << std::endl;
            }
            break;

        case srecord::record::type_data_count:
            {
                std::cout << "Data Count Record: " << record.get_address() << " bytes" << std::endl;
            }
            break;

        default:
            // Other record types (EOF, etc.)
            break;
        }
    }

    std::cout << std::endl;
    std::cout << "=== Summary ===" << std::endl;
    std::cout << "Total records: " << record_count << std::endl;
    std::cout << "Data records: " << data_record_count << std::endl;
    std::cout << "Total data bytes: " << total_data_bytes << std::endl;

    if (has_data)
    {
        std::cout << "Address range: 0x" << std::hex << std::setw(8) << std::setfill('0')
                  << start_address << " - 0x" << (end_address - 1) << std::dec << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Hex file loaded successfully!" << std::endl;

    return EXIT_SUCCESS;
    return true;
}
std::list<std::map<uint64_t,uint64_t>> BinFile::data_splite()
{
    std::list<std::map<uint64_t,uint64_t>> dataSplite;

    for (auto&var:m_data)
    {
        if (dataSplite.empty())
        {
            dataSplite.emplace_back();
            dataSplite.back().insert(var);
            continue;
        }
        if (  dataSplite.back().rbegin()->first+1==var.first)
        {
            dataSplite.back().insert(var);
            continue;
        }
        else
        {
            dataSplite.emplace_back();
            dataSplite.back().insert(var);
        }
    }

    return dataSplite;
}