#include <QLibrary>
#include <QDebug>
#include "jlinkarm.h"

#ifdef _WIN64
const QString jlinkPath = "JLink_x64.dll";
#else
const QString jlinkPath = "JLinkARM.dll";
#endif

JlinkARM::JlinkARM()
{
    jlinkLib = new QLibrary(jlinkPath);
    if (jlinkLib->load())
    {
        // ==================== J-Link ARM DLL 函数解析与封装 ====================
        // 该代码用于动态加载 J-Link DLL 并封装其功能函数

        // 原有函数解析 - 基础功能
        rjlinkOpenFuncPtr = (rjlinkOpenFunc)jlinkLib->resolve("JLINKARM_Open");
        // 打开 J-Link 设备，建立与仿真器的连接

        rjlinkCloseFuncPtr = (rjlinkCloseFunc)jlinkLib->resolve("JLINKARM_Close");
        // 关闭 J-Link 设备，释放资源

        rjlinkIsOpenFuncPtr = (rjlinkIsOpenFunc)jlinkLib->resolve("JLINKARM_IsOpen");
        // 检查 J-Link 设备是否已打开

        rjlinkTIFSelectFuncPtr = (rjlinkTIFSelectFunc)jlinkLib->resolve("JLINKARM_TIF_Select");
        // 选择目标接口（JTAG/SWD），设置调试接口类型

        rjlinkSetSpeedFuncPtr = (rjlinkSetSpeedFunc)jlinkLib->resolve("JLINKARM_SetSpeed");
        // 设置 JTAG/SWD 通信速度（kHz）

        rjlinkGetSpeedFuncPtr = (rjlinkGetSpeedFunc)jlinkLib->resolve("JLINKARM_GetSpeed");
        // 获取当前设置的通信速度

        rjlinkResetFuncPtr = (rjlinkResetFunc)jlinkLib->resolve("JLINKARM_Reset");
        // 复位目标芯片，执行硬件复位

        rjlinkHaltFuncPtr = (rjlinkHaltFunc)jlinkLib->resolve("JLINKARM_Halt");
        // 暂停目标芯片运行，进入调试模式

        rjlinkReadMemFuncPtr = (rjlinkReadMemFunc)jlinkLib->resolve("JLINKARM_ReadMem");
        // 读取目标内存（任意长度），将数据存入缓冲区

        rjlinkWriteMemFuncPtr = (rjlinkWriteMemFunc)jlinkLib->resolve("JLINKARM_WriteMem");
        // 写入目标内存（任意长度），将缓冲区数据写入指定地址

        rjlinkEraseChipFuncPtr = (rjlinkEraseChipFunc)jlinkLib->resolve("JLINK_EraseChip");
        // 擦除整个芯片 Flash，用于编程前清空芯片

        rjlinkExecCommandFuncPtr = (rjlinkExecCommandFunc)jlinkLib->resolve("JLINKARM_ExecCommand");
        // 执行 J-Link 命令字符串，如 "device = STM32F103C8"

        rjlinkGetDLLVersionFuncPtr = (rjlinkGetDLLVersionFunc)jlinkLib->resolve("JLINKARM_GetDLLVersion");
        // 获取 J-Link DLL 版本号，用于版本兼容性检查

        rjlinkGetSNFuncPtr = (rjlinkGetSNFunc)jlinkLib->resolve("JLINKARM_GetSN");
        // 获取 J-Link 仿真器序列号，用于识别设备

        rjlinkGetIdFuncPtr = (rjlinkGetIdFunc)jlinkLib->resolve("JLINKARM_GetId");
        // 获取目标芯片 ID（如 ARM Cortex-M 的 DAP ID）

        rjlinkConnectFuncPtr = (rjlinkConnectFunc)jlinkLib->resolve("JLINKARM_Connect");
        // 连接到目标设备，建立与目标芯片的通信

        rjlinkIsConnectedFuncPtr = (rjlinkIsConnectedFunc)jlinkLib->resolve("JLINKARM_IsConnected");
        // 检查是否已连接到目标设备

        // ========== 新增函数解析 - 扩展功能 ==========

        rjlinkGoFuncPtr = (rjlinkGoFunc)jlinkLib->resolve("JLINKARM_Go");
        // 继续执行目标程序，从暂停状态恢复运行

        rjlinkWriteU8FuncPtr = (rjlinkWriteU8Func)jlinkLib->resolve("JLINKARM_WriteU8");
        // 写8位数据到目标内存（字节），适用于小数据写入

        rjlinkWriteU16FuncPtr = (rjlinkWriteU16Func)jlinkLib->resolve("JLINKARM_WriteU16");
        // 写16位数据到目标内存（半字），注意地址对齐

        rjlinkWriteU32FuncPtr = (rjlinkWriteU32Func)jlinkLib->resolve("JLINKARM_WriteU32");
        // 写32位数据到目标内存（字），效率最高的写入方式

        rjlinkDownloadFileFuncPtr = (rjlinkDownloadFileFunc)jlinkLib->resolve("JLINKARM_DownloadFile");
        // 下载文件到目标芯片，支持 HEX/BIN 格式

        rjlinkBeginDownloadFuncPtr = (rjlinkBeginDownloadFunc)jlinkLib->resolve("JLINKARM_BeginDownload");
        // 开始下载会话，为批量下载做准备

        rjlinkEndDownloadFuncPtr = (rjlinkEndDownloadFunc)jlinkLib->resolve("JLINKARM_EndDownload");
        // 结束下载会话，清理下载状态

        rjlinkReadRegFuncPtr = (rjlinkReadRegFunc)jlinkLib->resolve("JLINKARM_ReadReg");
        // 读取 CPU 寄存器（R0-R15, PC, SP 等）

        rjlinkWriteRegFuncPtr = (rjlinkWriteRegFunc)jlinkLib->resolve("JLINKARM_WriteReg");
        // 写入 CPU 寄存器值，用于修改程序执行状态

        rjlinkSetLogFileFuncPtr = (rjlinkSetLogFileFunc)jlinkLib->resolve("JLINKARM_SetLogFile");
        // 设置日志文件路径，记录调试信息到文件

        rjlinkGetHardwareVersionFuncPtr = (rjlinkGetHardwareVersionFunc)jlinkLib->resolve("JLINKARM_GetHardwareVersion");
        // 获取 J-Link 硬件版本号（V8/V9/V10等）

        rjlinkGetFirmwareStringFuncPtr = (rjlinkGetFirmwareStringFunc)jlinkLib->resolve("JLINKARM_GetFirmwareString");
        // 获取固件版本字符串，如 "J-Link V9 compiled 2023"

        // ========== 解析高级功能函数 - 高性能操作 ==========

        rjlinkGetDeviceIdFuncPtr = (rjlinkGetDeviceIdFunc)jlinkLib->resolve("JLINKARM_GetDeviceId");
        // 获取设备 ID，用于识别目标芯片型号

        rjlinkReadMemU32FuncPtr = (rjlinkReadMemU32Func)jlinkLib->resolve("JLINKARM_ReadMemU32");
        // 快速读取32位数据，适用于大批量数据读取

        rjlinkWriteMemU32FuncPtr = (rjlinkWriteMemU32Func)jlinkLib->resolve("JLINKARM_WriteMemU32");
        // 快速写入32位数据，编程速度最快

        rjlinkReadMemU16FuncPtr = (rjlinkReadMemU16Func)jlinkLib->resolve("JLINKARM_ReadMemU16");
        // 快速读取16位数据，注意半字对齐要求

        rjlinkWriteMemU16FuncPtr = (rjlinkWriteMemU16Func)jlinkLib->resolve("JLINKARM_WriteMemU16");
        // 快速写入16位数据，适用于特定外设寄存器

        rjlinkReadMemU8FuncPtr = (rjlinkReadMemU8Func)jlinkLib->resolve("JLINKARM_ReadMemU8");
        // 快速读取8位数据，读取字节数组

        rjlinkWriteMemU8FuncPtr = (rjlinkWriteMemU8Func)jlinkLib->resolve("JLINKARM_WriteMemU8");
        // 快速写入8位数据，写入字节数组

        rjlinkSetResetTypeFuncPtr = (rjlinkSetResetTypeFunc)jlinkLib->resolve("JLINKARM_SetResetType");
        // 设置复位类型（硬件复位/软件复位/内核复位）

        rjlinkGetCoreIdFuncPtr = (rjlinkGetCoreIdFunc)jlinkLib->resolve("JLINKARM_GetCoreId");
        // 获取 CPU 核心 ID，用于多核设备识别

        rjlinkStepFuncPtr = (rjlinkStepFunc)jlinkLib->resolve("JLINKARM_Step");
        // 单步执行一条指令，用于调试时逐行调试

        // ==================== 使用示例与注意事项 ====================
        /*
         * 1. 典型使用流程：
         *    Open -> TIF_Select -> SetSpeed -> Connect -> [调试操作] -> Close
         *
         * 2. 调试操作示例：
         *    - Halt: 暂停目标
         *    - ReadReg/WriteReg: 读写寄存器
         *    - ReadMem/WriteMem: 读写内存
         *    - Go: 恢复运行
         *    - Reset: 复位芯片
         *
         * 3. 编程 Flash 流程：
         *    BeginDownload -> EraseChip/DownloadFile -> EndDownload
         *
         * 4. 注意事项：
         *    - 所有函数需要 DLL 正确加载才能调用
         *    - 需要在 Connect 成功后才能进行内存/寄存器操作
         *    - 部分函数需要目标处于 Halt 状态才能正常工作
         *    - 64位系统使用 JLink_x64.dll，32位系统使用 JLinkARM.dll
         *
         * 5. 错误处理：
         *    - 函数返回值通常为 0 表示成功，非 0 表示错误
         *    - 可使用 ExecCommand 执行 "ShowError" 查看详细错误信息
         */
    }
    else
    {
        qWarning() << "JLinkARM.dll 加载失败";
    }
}

JlinkARM::~JlinkARM()
{
    if (jlinkLib && jlinkLib->isLoaded())
    {
        jlinkClose();
        jlinkLib->unload();
        jlinkLib->deleteLater();
    }
}

// ========== 原有函数实现 ==========

bool JlinkARM::jlinkOpen(void) const
{
    if (rjlinkOpenFuncPtr) {
        rjlinkOpenFuncPtr();
        return jlinkIsOpen();
    }
    return false;
}

void JlinkARM::jlinkClose(void) const
{
    if (rjlinkCloseFuncPtr) {
        rjlinkCloseFuncPtr();
    }
}

bool JlinkARM::jlinkIsOpen(void) const
{
    if (rjlinkIsOpenFuncPtr) {
        return rjlinkIsOpenFuncPtr();
    }
    return false;
}

unsigned int JlinkARM::jlinkTIFSelectFunc(int type) const
{
    if (rjlinkTIFSelectFuncPtr) {
        return rjlinkTIFSelectFuncPtr(type);
    }
    return 0;
}

void JlinkARM::jlinkSetSpeedFunc(unsigned int speed) const
{
    if (rjlinkSetSpeedFuncPtr) {
        rjlinkSetSpeedFuncPtr(speed);
    }
}

unsigned int JlinkARM::jlinkGetSpeedFunc(void) const
{
    if (rjlinkGetSpeedFuncPtr) {
        return rjlinkGetSpeedFuncPtr();
    }
    return 0;
}

void JlinkARM::jlinkResetFunc(void) const
{
    if (rjlinkResetFuncPtr) {
        rjlinkResetFuncPtr();
    }
}

int JlinkARM::jlinkHaltFunc(void) const
{
    if (rjlinkHaltFuncPtr) {
        return rjlinkHaltFuncPtr();
    }
    return -1;
}

int JlinkARM::jlinkReadMemFunc(unsigned int addr, int len, void* buf) const
{
    if (rjlinkReadMemFuncPtr) {
        return rjlinkReadMemFuncPtr(addr, len, buf);
    }
    return -1;
}

int JlinkARM::jlinkWriteMemFunc(unsigned int addr, int len, void* buf) const
{
    if (rjlinkWriteMemFuncPtr) {
        return rjlinkWriteMemFuncPtr(addr, len, buf);
    }
    return -1;
}

int JlinkARM::jlinkEraseChipFunc(void) const
{
    if (rjlinkEraseChipFuncPtr) {
        return rjlinkEraseChipFuncPtr();
    }
    return -1;
}

bool JlinkARM::jlinkExecCommandFunc(const char* cmd, int a, int b) const
{
    if (rjlinkExecCommandFuncPtr) {
        return rjlinkExecCommandFuncPtr(cmd, a, b);
    }
    return false;
}

unsigned int JlinkARM::jlinkGetDLLVersionFunc(void) const
{
    if (rjlinkGetDLLVersionFuncPtr) {
        return rjlinkGetDLLVersionFuncPtr();
    }
    return 0;
}

unsigned int JlinkARM::jlinkGetSNFunc(void) const
{
    if (rjlinkGetSNFuncPtr) {
        return rjlinkGetSNFuncPtr();
    }
    return 0;
}

unsigned int JlinkARM::jlinkGetIdFunc(void) const
{
    if (rjlinkGetIdFuncPtr) {
        return rjlinkGetIdFuncPtr();
    }
    return 0;
}

bool JlinkARM::jlinkConnectFunc(void) const
{
    if (rjlinkConnectFuncPtr) {
        return rjlinkConnectFuncPtr();
    }
    return false;
}

bool JlinkARM::jlinkIsConnectedFunc(void) const
{
    if (rjlinkIsConnectedFuncPtr) {
        return rjlinkIsConnectedFuncPtr();
    }
    return false;
}

// ========== 新增函数实现 ==========

void JlinkARM::jlinkGoFunc(void) const
{
    if (rjlinkGoFuncPtr) {
        rjlinkGoFuncPtr();
    }
}

int JlinkARM::jlinkWriteU8Func(unsigned int addr, unsigned char data) const
{
    if (rjlinkWriteU8FuncPtr) {
        return rjlinkWriteU8FuncPtr(addr, data);
    }
    return -1;
}

int JlinkARM::jlinkWriteU16Func(unsigned int addr, unsigned short data) const
{
    if (rjlinkWriteU16FuncPtr) {
        return rjlinkWriteU16FuncPtr(addr, data);
    }
    return -1;
}

int JlinkARM::jlinkWriteU32Func(unsigned int addr, unsigned int data) const
{
    if (rjlinkWriteU32FuncPtr) {
        return rjlinkWriteU32FuncPtr(addr, data);
    }
    return -1;
}

int JlinkARM::jlinkDownloadFileFunc(const char* file, unsigned int addr) const
{
    if (rjlinkDownloadFileFuncPtr) {
        return rjlinkDownloadFileFuncPtr(file, addr);
    }
    return -1;
}

void JlinkARM::jlinkBeginDownloadFunc(int index) const
{
    if (rjlinkBeginDownloadFuncPtr) {
        rjlinkBeginDownloadFuncPtr(index);
    }
}

void JlinkARM::jlinkEndDownloadFunc(void) const
{
    if (rjlinkEndDownloadFuncPtr) {
        rjlinkEndDownloadFuncPtr();
    }
}

unsigned int JlinkARM::jlinkReadRegFunc(int index) const
{
    if (rjlinkReadRegFuncPtr) {
        return rjlinkReadRegFuncPtr(index);
    }
    return 0;
}

int JlinkARM::jlinkWriteRegFunc(int index, unsigned int data) const
{
    if (rjlinkWriteRegFuncPtr) {
        return rjlinkWriteRegFuncPtr(index, data);
    }
    return -1;
}

void JlinkARM::jlinkSetLogFileFunc(char* file) const
{
    if (rjlinkSetLogFileFuncPtr) {
        rjlinkSetLogFileFuncPtr(file);
    }
}

unsigned int JlinkARM::jlinkGetHardwareVersionFunc(void) const
{
    if (rjlinkGetHardwareVersionFuncPtr) {
        return rjlinkGetHardwareVersionFuncPtr();
    }
    return 0;
}

unsigned int JlinkARM::jlinkGetFirmwareStringFunc(char* buff, int count) const
{
    if (rjlinkGetFirmwareStringFuncPtr) {
        return rjlinkGetFirmwareStringFuncPtr(buff, count);
    }
    return 0;
}

// ========== 高级功能函数实现 ==========

unsigned int JlinkARM::jlinkGetDeviceIdFunc(void) const
{
    if (rjlinkGetDeviceIdFuncPtr) {
        return rjlinkGetDeviceIdFuncPtr();
    }
    return 0;
}

int JlinkARM::jlinkReadMemU32Func(unsigned int addr, unsigned int* data) const
{
    if (rjlinkReadMemU32FuncPtr) {
        return rjlinkReadMemU32FuncPtr(addr, data);
    }
    return -1;
}

int JlinkARM::jlinkWriteMemU32Func(unsigned int addr, unsigned int data) const
{
    if (rjlinkWriteMemU32FuncPtr) {
        return rjlinkWriteMemU32FuncPtr(addr, data);
    }
    return -1;
}

int JlinkARM::jlinkReadMemU16Func(unsigned int addr, unsigned short* data) const
{
    if (rjlinkReadMemU16FuncPtr) {
        return rjlinkReadMemU16FuncPtr(addr, data);
    }
    return -1;
}

int JlinkARM::jlinkWriteMemU16Func(unsigned int addr, unsigned short data) const
{
    if (rjlinkWriteMemU16FuncPtr) {
        return rjlinkWriteMemU16FuncPtr(addr, data);
    }
    return -1;
}

int JlinkARM::jlinkReadMemU8Func(unsigned int addr, unsigned char* data) const
{
    if (rjlinkReadMemU8FuncPtr) {
        return rjlinkReadMemU8FuncPtr(addr, data);
    }
    return -1;
}

int JlinkARM::jlinkWriteMemU8Func(unsigned int addr, unsigned char data) const
{
    if (rjlinkWriteMemU8FuncPtr) {
        return rjlinkWriteMemU8FuncPtr(addr, data);
    }
    return -1;
}

void JlinkARM::jlinkSetResetTypeFunc(int type) const
{
    if (rjlinkSetResetTypeFuncPtr) {
        rjlinkSetResetTypeFuncPtr(type);
    }
}

unsigned int JlinkARM::jlinkGetCoreIdFunc(void) const
{
    if (rjlinkGetCoreIdFuncPtr) {
        return rjlinkGetCoreIdFuncPtr();
    }
    return -1;
}

int JlinkARM::jlinkStepFunc(void) const
{
    if (rjlinkStepFuncPtr) {
        return rjlinkStepFuncPtr();
    }
    return -1;
}