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
    // 原有函数指针定义...
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

    // ========== 新增函数指针定义 ==========
    typedef void(*rjlinkGoFunc)(void);
    typedef int(*rjlinkWriteU8Func)(unsigned int addr, unsigned char data);
    typedef int(*rjlinkWriteU16Func)(unsigned int addr, unsigned short data);
    typedef int(*rjlinkWriteU32Func)(unsigned int addr, unsigned int data);
    typedef int(*rjlinkDownloadFileFunc)(const char* file, unsigned int addr);
    typedef void(*rjlinkBeginDownloadFunc)(int index);
    typedef void(*rjlinkEndDownloadFunc)(void);
    typedef unsigned int(*rjlinkReadRegFunc)(int index);
    typedef int(*rjlinkWriteRegFunc)(int index, unsigned int data);
    typedef void(*rjlinkSetLogFileFunc)(char* file);
    typedef unsigned int(*rjlinkGetHardwareVersionFunc)(void);
    typedef unsigned int(*rjlinkGetFirmwareStringFunc)(char* buff, int count);

    // ========== 新增 J-Link 高级功能函数指针 ==========
    typedef unsigned int(*rjlinkGetDeviceIdFunc)(void);
    typedef int(*rjlinkReadMemU32Func)(unsigned int addr, unsigned int* data);
    typedef int(*rjlinkWriteMemU32Func)(unsigned int addr, unsigned int data);
    typedef int(*rjlinkReadMemU16Func)(unsigned int addr, unsigned short* data);
    typedef int(*rjlinkWriteMemU16Func)(unsigned int addr, unsigned short data);
    typedef int(*rjlinkReadMemU8Func)(unsigned int addr, unsigned char* data);
    typedef int(*rjlinkWriteMemU8Func)(unsigned int addr, unsigned char data);
    typedef void(*rjlinkSetResetTypeFunc)(int type);
    typedef unsigned int(*rjlinkGetCoreIdFunc)(void);
    typedef int(*rjlinkStepFunc)(void);

public:
    // 原有公有函数...
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

    // ========== 新增公有函数 ==========
    void jlinkGoFunc(void) const;
    int jlinkWriteU8Func(unsigned int addr, unsigned char data) const;
    int jlinkWriteU16Func(unsigned int addr, unsigned short data) const;
    int jlinkWriteU32Func(unsigned int addr, unsigned int data) const;
    int jlinkDownloadFileFunc(const char* file, unsigned int addr) const;
    void jlinkBeginDownloadFunc(int index) const;
    void jlinkEndDownloadFunc(void) const;
    unsigned int jlinkReadRegFunc(int index) const;
    int jlinkWriteRegFunc(int index, unsigned int data) const;
    void jlinkSetLogFileFunc(char* file) const;
    unsigned int jlinkGetHardwareVersionFunc(void) const;
    unsigned int jlinkGetFirmwareStringFunc(char* buff, int count) const;

    // ========== 新增高级功能公有函数 ==========
    unsigned int jlinkGetDeviceIdFunc(void) const;
    int jlinkReadMemU32Func(unsigned int addr, unsigned int* data) const;
    int jlinkWriteMemU32Func(unsigned int addr, unsigned int data) const;
    int jlinkReadMemU16Func(unsigned int addr, unsigned short* data) const;
    int jlinkWriteMemU16Func(unsigned int addr, unsigned short data) const;
    int jlinkReadMemU8Func(unsigned int addr, unsigned char* data) const;
    int jlinkWriteMemU8Func(unsigned int addr, unsigned char data) const;
    void jlinkSetResetTypeFunc(int type) const;
    unsigned int jlinkGetCoreIdFunc(void) const;
    int jlinkStepFunc(void) const;

private:
    // 原有私有成员...
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

    // ========== 新增私有成员 ==========
    rjlinkGetDeviceIdFunc rjlinkGetDeviceIdFuncPtr = NULL;
    rjlinkReadMemU32Func rjlinkReadMemU32FuncPtr = NULL;
    rjlinkWriteMemU32Func rjlinkWriteMemU32FuncPtr = NULL;
    rjlinkReadMemU16Func rjlinkReadMemU16FuncPtr = NULL;
    rjlinkWriteMemU16Func rjlinkWriteMemU16FuncPtr = NULL;
    rjlinkReadMemU8Func rjlinkReadMemU8FuncPtr = NULL;
    rjlinkWriteMemU8Func rjlinkWriteMemU8FuncPtr = NULL;
    rjlinkSetResetTypeFunc rjlinkSetResetTypeFuncPtr = NULL;
    rjlinkGetCoreIdFunc rjlinkGetCoreIdFuncPtr = NULL;
    rjlinkStepFunc rjlinkStepFuncPtr = NULL;

public:
// ==================== 接口类型常量 ====================
    enum
    {
        JLINKARM_TIF_JTAG = 0,              // JTAG 接口模式（5线）
        JLINKARM_TIF_SWD = 1,               // SWD 接口模式（2线，推荐）
        JLINKARM_TIF_DBM3 = 2,              // DBM3 接口模式
        JLINKARM_TIF_FINE = 3,             // FINE 接口模式
        JLINKARM_TIF_2wire_JTAG_PIC32 = 4 // PIC32 专用 2线 JTAG
    };

// ==================== 复位类型常量 ====================
const static int JLINKARM_RESET_TYPE_NORMAL = 0;     // 正常复位（硬件复位）
const static int JLINKARM_RESET_TYPE_CORE = 1;       // 仅复位内核
const static int JLINKARM_RESET_TYPE_PIN = 2;        // 引脚复位（拉低复位引脚）

// ==================== 寄存器索引常量 ====================
const static int JLINKARM_REG_R0 = 0;                // 通用寄存器 R0
const static int JLINKARM_REG_R1 = 1;                // 通用寄存器 R1
const static int JLINKARM_REG_R2 = 2;                // 通用寄存器 R2
const static int JLINKARM_REG_R3 = 3;                // 通用寄存器 R3
const static int JLINKARM_REG_R4 = 4;                // 通用寄存器 R4
const static int JLINKARM_REG_R5 = 5;                // 通用寄存器 R5
const static int JLINKARM_REG_R6 = 6;                // 通用寄存器 R6
const static int JLINKARM_REG_R7 = 7;                // 通用寄存器 R7
const static int JLINKARM_REG_R8 = 8;                // 通用寄存器 R8
const static int JLINKARM_REG_R9 = 9;                // 通用寄存器 R9
const static int JLINKARM_REG_R10 = 10;              // 通用寄存器 R10
const static int JLINKARM_REG_R11 = 11;              // 通用寄存器 R11
const static int JLINKARM_REG_R12 = 12;              // 通用寄存器 R12
const static int JLINKARM_REG_SP = 13;               // 堆栈指针（SP/R13）
const static int JLINKARM_REG_LR = 14;               // 链接寄存器（LR/R14）
const static int JLINKARM_REG_PC = 15;               // 程序计数器（PC/R15）
const static int JLINKARM_REG_XPSR = 16;             // 程序状态寄存器
const static int JLINKARM_REG_MSP = 17;              // 主堆栈指针
const static int JLINKARM_REG_PSP = 18;              // 进程堆栈指针
const static int JLINKARM_REG_PRIMASK = 19;          // 优先级屏蔽寄存器
const static int JLINKARM_REG_BASEPRI = 20;          // 基础优先级寄存器
const static int JLINKARM_REG_FAULTMASK = 21;        // 故障屏蔽寄存器
const static int JLINKARM_REG_CONTROL = 22;          // 控制寄存器

private:
    QLibrary* jlinkLib;
};

#endif // JLINK_ARM_H