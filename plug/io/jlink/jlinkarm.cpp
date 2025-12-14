#include <QLibrary>
#include <QDebug>
#include "jlinkarm.h"
#ifdef _WIN64
const QString jlinkPath = "./bin/JLink_x64.dll";
#else
const QString jlinkPath = "./bin/JLinkARM.dll";
#endif
JlinkARM::JlinkARM() {

    jlinkLib = new QLibrary(jlinkPath);
    if (jlinkLib->load())
    {

        rjlinkOpenFuncPtr = (rjlinkOpenFunc)jlinkLib->resolve("JLINKARM_Open");//打开设备
        rjlinkCloseFuncPtr = (rjlinkCloseFunc)jlinkLib->resolve("JLINKARM_Close");//关闭设备
        rjlinkIsOpenFuncPtr = (rjlinkIsOpenFunc)jlinkLib->resolve("JLINKARM_IsOpen");//判断设备是否打开
        rjlinkTIFSelectFuncPtr = (rjlinkTIFSelectFunc)jlinkLib->resolve("JLINKARM_TIF_Select");//选择设备
        rjlinkSetSpeedFuncPtr = (rjlinkSetSpeedFunc)jlinkLib->resolve("JLINKARM_SetSpeed");//设置烧录速度
        rjlinkGetSpeedFuncPtr = (rjlinkGetSpeedFunc)jlinkLib->resolve("JLINKARM_GetSpeed");//获取烧录速度
        rjlinkResetFuncPtr = (rjlinkResetFunc)jlinkLib->resolve("JLINKARM_Reset");//复位设备
        rjlinkHaltFuncPtr = (rjlinkHaltFunc)jlinkLib->resolve("JLINKARM_Halt");//中断程序执行
        rjlinkReadMemFuncPtr = (rjlinkReadMemFunc)jlinkLib->resolve("JLINKARM_ReadMem");//读取内存
        rjlinkWriteMemFuncPtr = (rjlinkWriteMemFunc)jlinkLib->resolve("JLINKARM_WriteMem");//写入内存
        rjlinkEraseChipFuncPtr = (rjlinkEraseChipFunc)jlinkLib->resolve("JLINK_EraseChip");//擦除芯片
        rjlinkExecCommandFuncPtr = (rjlinkExecCommandFunc)jlinkLib->resolve("JLINKARM_ExecCommand");//执行命令
        rjlinkGetDLLVersionFuncPtr = (rjlinkGetDLLVersionFunc)jlinkLib->resolve("JLINKARM_GetDLLVersion");//获取DLL版本号
        rjlinkGetSNFuncPtr = (rjlinkGetSNFunc)jlinkLib->resolve("JLINKARM_GetSN");//获取sn号
        rjlinkGetIdFuncPtr = (rjlinkGetIdFunc)jlinkLib->resolve("JLINKARM_GetId");//获取ID
        rjlinkConnectFuncPtr = (rjlinkConnectFunc)jlinkLib->resolve("JLINKARM_Connect");//连接设备
        rjlinkIsConnectedFuncPtr = (rjlinkIsConnectedFunc)jlinkLib->resolve("JLINKARM_IsConnected");//判断是否连接设备
    }
    else
    {
        qCritical() << "JLinkARM.dll 加载失败";
    }
}

JlinkARM::~JlinkARM()
{

    if (jlinkLib->isLoaded())
        jlinkLib->deleteLater();
}
bool JlinkARM::jlinkOpen(void) const
{
    if (rjlinkOpenFuncPtr) {
        return rjlinkOpenFuncPtr();
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
    else return false;
}
unsigned int JlinkARM::jlinkTIFSelectFunc(int type) const
{
    if (rjlinkTIFSelectFuncPtr) {
        return rjlinkTIFSelectFuncPtr(type);
    }
    return false;
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
    return 0;
}
/**
 * @brief JlinkARM::jlinkReadMemFunc 读取内存
 * @param addr 地址
 * @param len 长度
 * @param buf 缓存
 * @return
 */
int JlinkARM::jlinkReadMemFunc(unsigned int addr, int len, void* buf) const
{
    if (rjlinkReadMemFuncPtr) {
        return rjlinkReadMemFuncPtr(addr, len, buf);
    }
    return 0;
}
/**
 * @brief jlink烧写flash
 *
 * @param addr MCU内存起始地址
 * @param len buf数据长度
 * @param buf buf数据
 * @return int 烧写结果
 */
int JlinkARM::jlinkWriteMemFunc(unsigned int addr, int len, void* buf) const
{
    if (rjlinkWriteMemFuncPtr) {
        return rjlinkWriteMemFuncPtr(addr, len, buf);
    }
    return 0;
}
int JlinkARM::jlinkEraseChipFunc(void) const
{
    if (rjlinkEraseChipFuncPtr) {
        return rjlinkEraseChipFuncPtr();
    }
    return 0;
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

