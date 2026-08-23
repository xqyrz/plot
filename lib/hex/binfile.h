//
// Created by 25137 on 2026/8/23.
//

#ifndef PLOT_BINFILE_H
#define PLOT_BINFILE_H
#ifdef HEX_MYLIB_EXPORTS
    #define MYLIB_API __declspec(dllexport)
#else
    #define MYLIB_API __declspec(dllimport)
#endif
#include <cstdint>
#include <map>
#include <list>
typedef enum
{
    Type32bit=4,
    Type64bit=8
}UnitDataType;

 class MYLIB_API BinFile
{
public:
    BinFile(std::string filePath);
    ~BinFile();
    bool load(std::string filePath);
    std::list<std::map<uint64_t,uint64_t>> data_splite();
    std::map<uint64_t,uint64_t> data()const{return m_data;}
private:
    bool _load(std::string filePath);
private:
    std::map<uint64_t,uint64_t> m_data{};
    std::string m_filePath{};
    UnitDataType m_type = Type32bit;
};


#endif // PLOT_BINFILE_H
