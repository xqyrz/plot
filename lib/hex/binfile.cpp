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
    std::cout<<"load hex file:"<<filename<<std::endl;
    static  char ansy_app[] = "BinFile";
	int argc = 0;
    argc = 3;
	char* argv[3] = {(char*)ansy_app, (char*)filename.data(), (char*)"-intel"};
    m_data.clear();
    srecord::arglex_tool cmdline(argc, argv);
    cmdline.token_first();
    typedef std::vector<srecord::input::pointer> infile_t;
    infile_t infile;
    bool verbose = false;
    std::list<uint8_t> hex;
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
            infile.push_back(cmdline.get_input());
            continue;
        case srecord::arglex::token_verbose:
            verbose = true;
            break;
        }
        cmdline.token_next();
    }
    if (infile.size() == 0) infile.push_back(cmdline.get_input());
    uint32_t address = -1;
    for (infile_t::iterator it = infile.begin(); it != infile.end(); ++it)
    {
        srecord::input::pointer ifp = *it;
        srecord::record record;
        while (ifp->read(record))
        {
            switch (record.get_type())
            {
            case srecord::record::type_header:
                {
                    std::cout<<"srecord::record::type_header:"<<record.get_address()<<std::endl;
                    if (record.get_length() < 1)break;
                   // qDebug() << "srecord::record::type_header:" << record.get_address() << QString(QByteArray((char*)record.get_data(), record.get_length()));
                }
            break;
            case srecord::record::type_data:
                {
                    if (address != record.get_address()) {//new block mem
                       address = record.get_address();
                        std::cout << "address: 0x" << std::hex << address << std::dec << std::endl;
                    }
                    //std::cout<<"data:";
                    auto len = record.get_length();
                    auto p = record.get_data();
                    for (size_t i = 0; i < len; ++i) {
                        m_data.insert({address + i, p[i]});
                        //std::cout << std::hex << std::setw(2) << std::setfill('0')
                        //          << (unsigned)p[i] << ' ';
                    }
                    //std::cout << std::endl;
                    address += record.get_length();
                }
            break;
            case srecord::record::type_execution_start_address:
            {
                //STM32 / 类似 Cortex-M MCU 的复位向量 / 入口点
                //ARM Thumb 模式标志，实际代码在 0x80001d8
                std::cout<<"Execution Start Address: 0x"<<std::hex<<record.get_address()<<std::dec<<std::endl;
             //   qDebug() << QString("Execution Start Address:%1:%2").arg(record.get_address(),8,16,QChar('0'))
              //      .arg(QString(QByteArray((char*)record.get_data(),record.get_length()).toHex(' ')));
            }
            break;
            default:std::cout<< "default"<<std::endl;break;
            }
        }
    }
    auto d = data_splite();
    for (auto & var:d)
    {
        std::cout << std::hex<<"start:"<<var.begin()->first<<" end:"<<var.rbegin()->first<<" size:"<<var.size()<<std::endl;
    }
   // for (auto& var : data) {
   //
   //     qDebug() << QString("%1:%2").arg(var.startaddr, 8, 16, QChar('0')).arg(var.startaddr+var.data.size()-1, 8, 16, QChar('0'));
   // }
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
        if (dataSplite.back().rbegin()->first+1==var.first)
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