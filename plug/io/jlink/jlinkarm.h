#ifndef JLINK_ARM_H
#define JLINK_ARM_H



#include <QtCore/qglobal.h>
class QLibrary;
class JlinkARM
{
public:
    JlinkARM();
    ~JlinkARM();
private:
    typedef bool(*rjlinkOpenFunc)(void);
    typedef void(*rjlinkCloseFunc)(void);
    typedef bool(*rjlinkIsOpenFunc)(void);
    typedef unsigned int(*rjlinkTIFSelectFunc)(int);
    typedef void(*rjlinkSetSpeedFunc)(int);
    typedef unsigned int(*rjlinkGetSpeedFunc)(void);
    typedef void(*rjlinkResetFunc)(void);
    typedef int(*rjlinkHaltFunc)(void);
    typedef void(*rjlinkGoFunc)(void);

    typedef int(*rjlinkReadMemFunc)(unsigned int addr, int len, void* buf);
    typedef int(*rjlinkWriteMemFunc)(unsigned int addr, int len, void* buf);
    typedef int(*rjlinkWriteU8Func)(unsigned int addr, unsigned char data);
    typedef int(*rjlinkWriteU16Func)(unsigned int addr, unsigned short data);
    typedef int(*rjlinkWriteU32Func)(unsigned int addr, unsigned int data);

    typedef int(*rjlinkEraseChipFunc)(void);
    typedef int(*rjlinkDownloadFileFunc)(const char* file, unsigned int addr);
    typedef void(*rjlinkBeginDownloadFunc)(int index);
    typedef void(*rjlinkEndDownloadFunc)(void);
    typedef bool(*rjlinkExecCommandFunc)(const char* cmd, int a, int b);

    typedef unsigned int(*rjlinkReadRegFunc)(int index);
    typedef int(*rjlinkWriteRegFunc)(int index, unsigned int data);

    typedef void(*rjlinkSetLogFileFunc)(char* file);
    typedef unsigned int(*rjlinkGetDLLVersionFunc)(void);
    typedef unsigned int(*rjlinkGetHardwareVersionFunc)(void);
    typedef unsigned int(*rjlinkGetFirmwareStringFunc)(char* buff, int count);
    typedef unsigned int(*rjlinkGetSNFunc)(void);
    typedef unsigned int(*rjlinkGetIdFunc)(void);
    typedef bool(*rjlinkConnectFunc)(void);
    typedef bool(*rjlinkIsConnectedFunc)(void);


public:
    bool jlinkIsOpen(void) const;
    bool jlinkOpen(void) const;
    void jlinkClose(void) const;
    unsigned int jlinkTIFSelectFunc(int type) const;
    void jlinkSetSpeedFunc(unsigned int speed) const;
    unsigned int jlinkGetSpeedFunc(void) const;
    void jlinkResetFunc(void) const;
    int jlinkHaltFunc(void) const;
    int jlinkReadMemFunc(unsigned int addr, int len, void* buf) const;
    int jlinkWriteMemFunc(unsigned int addr, int len, void* buf) const;
    int jlinkEraseChipFunc(void) const;
    bool jlinkExecCommandFunc(const char* cmd, int a, int b) const;
    unsigned int jlinkGetDLLVersionFunc(void) const;
    unsigned int jlinkGetSNFunc(void) const;
    unsigned int jlinkGetIdFunc(void) const;
    bool jlinkConnectFunc(void) const;
    bool jlinkIsConnectedFunc(void) const;
private:
    rjlinkOpenFunc rjlinkOpenFuncPtr = NULL;
    rjlinkCloseFunc rjlinkCloseFuncPtr = NULL;
    rjlinkIsOpenFunc rjlinkIsOpenFuncPtr = NULL;
    rjlinkTIFSelectFunc rjlinkTIFSelectFuncPtr = NULL;
    rjlinkSetSpeedFunc rjlinkSetSpeedFuncPtr = NULL;
    rjlinkGetSpeedFunc rjlinkGetSpeedFuncPtr = NULL;
    rjlinkResetFunc rjlinkResetFuncPtr = NULL;
    rjlinkHaltFunc rjlinkHaltFuncPtr = NULL;
    rjlinkGoFunc rjlinkGoFuncPtr = NULL;
    rjlinkReadMemFunc rjlinkReadMemFuncPtr = NULL;
    rjlinkWriteMemFunc rjlinkWriteMemFuncPtr = NULL;
    rjlinkWriteU8Func rjlinkWriteU8FuncPtr = NULL;
    rjlinkWriteU16Func rjlinkWriteU16FuncPtr = NULL;
    rjlinkWriteU32Func rjlinkWriteU32FuncPtr = NULL;
    rjlinkEraseChipFunc rjlinkEraseChipFuncPtr = NULL;
    rjlinkDownloadFileFunc rjlinkDownloadFileFuncPtr = NULL;
    rjlinkBeginDownloadFunc rjlinkBeginDownloadFuncPtr = NULL;
    rjlinkEndDownloadFunc rjlinkEndDownloadFuncPtr = NULL;
    rjlinkExecCommandFunc rjlinkExecCommandFuncPtr = NULL;
    rjlinkReadRegFunc rjlinkReadRegFuncPtr = NULL;
    rjlinkWriteRegFunc rjlinkWriteRegFuncPtr = NULL;
    rjlinkSetLogFileFunc rjlinkSetLogFileFuncPtr = NULL;
    rjlinkGetDLLVersionFunc rjlinkGetDLLVersionFuncPtr = NULL;
    rjlinkGetHardwareVersionFunc rjlinkGetHardwareVersionFuncPtr = NULL;
    rjlinkGetFirmwareStringFunc rjlinkGetFirmwareStringFuncPtr = NULL;
    rjlinkGetSNFunc rjlinkGetSNFuncPtr = NULL;
    rjlinkGetIdFunc rjlinkGetIdFuncPtr = NULL;
    rjlinkConnectFunc rjlinkConnectFuncPtr = NULL;
    rjlinkIsConnectedFunc rjlinkIsConnectedFuncPtr = NULL;
public:
    //JLINKTIF
    const static  int  JLINKARM_TIF_JTAG = 0;
    const static  int  JLINKARM_TIF_SWD = 1;
    const static  int  JLINKARM_TIF_DBM3 = 2;
    const static  int  JLINKARM_TIF_FINE = 3;
    const static  int  JLINKARM_TIF_2wire_JTAG_PIC32 = 4;

    //RESETTYPE
    const static  int  JLINKARM_RESET_TYPE_NORMAL = 0;
    const static  int  JLINKARM_RESET_TYPE_CORE = 1;
    const static  int  JLINKARM_RESET_TYPE_PIN = 2;
private:
    QLibrary* jlinkLib;
};

#endif // JLINK_ARM_H