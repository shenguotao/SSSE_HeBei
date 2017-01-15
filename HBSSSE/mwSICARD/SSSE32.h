/*****************************************************************************************************
 *                           CopyRight(C), 1992-2014,M&W CARD TECH.Co,Ltd.
 * FileName:    SSSE32.h
 * Author:      申国涛       Version:   V0.0.0.1     Date:    2014年11月4日
 * Description:  
 * Others:      
 * Function List:   
 *   1. ....
 *
 * History:
 *  <author> <time> <version > <description  > 
 *  申国涛	2014年11月4日	V0.0.1.0	创建
 *
 *****************************************************************************************************/

#ifndef SSSE32_H_
#define SSSE32_H_

/**
 * ClassName:        SSSE32
 * Description:      社保规范接口
 * Others:           
 * Function List:    
 *	1. 
 *	
 * History:
 *  <author>        <time>        <version>        <desc> 
 *  申国涛        2014年11月4日        V0.0.1.0         创建
 *
 */

#define IFD_OK               0  //执行成功
#define IFD_ICC_TypeError   -1  //卡片类型不对
#define IFD_ICC_NoExist     -2  //无卡
#define IFD_ICC_NoPower     -3  //有卡未上电
#define IFD_ICC_NoResponse  -4  //卡片无应答
#define IFD_ConnectError    -11 //读卡器连接错
#define IFD_UnConnected     -12 //未建立连接(没有执行打开设备函数)
#define IFD_BadCommand      -13 //(动态库)不支持该命令
#define IFD_ParameterError  -14 //(发给动态库的)命令参数错
#define IFD_CheckSumError   -15 //信息校验和出错

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#ifdef __x86_64__
#define  HANDLE long long
#elif __i386__
#define  HANDLE int
#endif
#define INVALID_HANDLE_VALUE (HANDLE)(-1)
#define STDCALL
#else
#include <Windows.h>
#define STDCALL __stdcall
#endif

#else

#ifdef __x86_64__
#define  HANDLE long long
//#elif __i386__
//#define  HANDLE int32_t
#else
#define  HANDLE int
#endif

#define INVALID_HANDLE_VALUE (HANDLE)(-1)
#define STDCALL


#endif

#ifdef __cplusplus
extern "C"
{
#endif

    /*
    函数：long ICC_Reader_Open (char* dev_Name)
    功能：
        该函数通知终端操作系统打开与读卡器所对应的终端设备端口，以便两者建立通信的逻辑关系。
    参数说明：
        dev_Name：设备名称。取值范围”AUTO”、”COMn”、”USBn”、”LPTn”，其中”n”的取值范围为1~9。
    返回值：
        若正常，返回值为不小于0的设备句柄；反之返回值为状态码，其含义见B1.8。
        注：对16位Windows环境下运行的动态链接库、DOS环境下运行的静态函数库返回的设备句柄，其含义均不同于32位Windows环境下动态链接库返回的设备句柄，仅为区分设备之用。

    */
    long STDCALL ICC_Reader_Open(char *dev_Name);

    /*
    函数： long ICC_Reader_Close (long ReaderHandle)
    功能： 该函数通知操作系统关闭所指定的设备。
    参数说明： ReaderHandle：设备句柄。
    返回值：  返回值含义见B1.8。
    */
    long STDCALL ICC_Reader_Close(long ReaderHandle);

    /*
    函数： long ICC_Reader_PowerOn (long ReaderHandle，unsigned char ICC_Slot_No，unsigned char* Response)
    功能： 该函数要求读卡器对ICC进行冷复位，若冷复位失败读卡器应启动一个热复位。
    参数说明：   1. ReaderHandle：设备句柄；
                2. ICC_Slot_No：ICC连接器号；用户卡连接器号 0x0n，SAM卡连接器号0x1n，其中“n”的取值范围为1~F；
                3. Response：指向存放响应数据的存储区的指针。
    返回值：  如果对ICC复位成功，则在Response的存储区中返回ICC的复位应答字节，返回值为存储区中的字节数；返回值小于0为状态码，其含义见B1.8。
    */
    long STDCALL ICC_Reader_PowerOn(long ReaderHandle, unsigned char ICC_Slot_No, unsigned char* Response);

    /*
    函数： long ICC_Reader_PowerOff (long ReaderHandle，unsigned char ICC_Slot_No)
    功能： 该函数要求读卡器撤消与ICC之间的电气连接。
    参数说明：   1. ReaderHandle：设备句柄；
                2. ICC_Slot_No：ICC连接器号；用户卡连接器号 0x0n，SAM卡连接器号0x1n，其中“n”的取值范围为1~F；
    返回值：  如果该函数成功执行，则返回值为0；返回值小于0为状态码，其含义见B1.8。
    */
    long STDCALL ICC_Reader_PowerOff(long ReaderHandle, unsigned char ICC_Slot_No);

    /*
    函数： long ICC_Reader_GetStatus (long ReaderHandle，unsigned char ICC_Slot_No)
    功能： 查询有无卡以及卡片当前状态信息。
    参数说明：   1. ReaderHandle：设备句柄；
                2. ICC_Slot_No：ICC连接器号；用户卡连接器号 0x0n，SAM卡连接器号0x1n，其中“n”的取值范围为1~F；
    返回值：  返回0表示有卡且已上电；返回值小于0为状态码，其含义见B1.8。
    */
    long STDCALL ICC_Reader_GetStatus(long ReaderHandle, unsigned char ICC_Slot_No);

    /*
    函数： long ICC_Reader_Application (long ReaderHandle，unsigned char ICC_ Slot _No，long
    　　　　　　　　　　　　　　　　　　Lenth_of_Command_APDU，unsigned char* Command_APDU，unsigned char* Response_APDU)
    功能： 该函数用于将符合ISO 7816中所规定的基本和特殊功能的行业间交换用命令发送给指定的ICC连接器，并获取对应的响应。
    参数说明：   1. ReaderHandle：设备句柄；
                2. ICC_Slot_No：ICC连接器号；用户卡连接器号 0x0n，SAM卡连接器号0x1n，其中“n”的取值范围为1~F；
                3. Lenth_of_Command_APDU：其值为Command_APDU所指向缓冲区中的字节数；
                4. Command_APDU：指向存放命令的缓冲区的指针；
                5. Response_APDU：指向存放响应数据的存储区的指针(包括sw1,sw2)。
    返回值：  如果函数执行成功，则在Response_APDU的存储区中返回响应数据，函数返回值为存储区中的字节数；返回值小于0为状态码，其含义见B1.8，Response_APDU的存储区无任何数据。
    */
    long STDCALL ICC_Reader_Application(long ReaderHandle, unsigned char ICC_Slot_No,
        long Lenth_of_Command_APDU, unsigned char* Command_APDU, unsigned char* Response_APDU);

    /*
    函数： long ICC_Reader_Libinfo (char* info)
    功能： 该函数取得当前函数库的厂家信息。
    参数说明：   info：指向存放厂家信息的存储区的指针。
                    厂家信息的存储格式
                第1~16字符	第17~30字符	第31、32字符
                厂家名称（不足补空格）	设备型号或系列号（不足补空格）	函数库版本号

    返回值：  返回值的含义见B1.8。
    */  
    long STDCALL ICC_Reader_Libinfo(char* info);

    /*
     功能：获得用户键盘密码的输入,该函数会一直等待用户输入直到超时
     参数： ReaderHandle通讯设备标识符
     ctime     等待用户按键输入的超时时间，以second为单位；最大255s，最小1s；超过该时间退出.
     Rlen 密码位数
     Cpass 输入的密码
     cshow 液晶屏显示汉字，最长16字节长度（共两行，每行8汉字）

     cmd 语音提示，1-请输入密码 2-请重新输入密码 3-请输入旧密码 4-请输入新密码

     返回： 0， 成功取得密码，rlen ＝ 密码位数（1－16之间，根据客户输入而定）cpass就是密码
     -1， 用户取消密码输入，rlen ＝0，无data段；
     -2， 用户密码输入操作超时，rlen ＝0，无data段；
     */
    long STDCALL ICC_GetInputPassEx(long ReaderHandle, unsigned char ctime, unsigned char *rlen,
        unsigned char * cpass, unsigned char *cshow, unsigned char cmd);

    /*
    函数： long STDCALL ICC_Reader_Sn(char* sn)
    功能： 该函数取得当前终端社保号。
    参数说明：   info：指向存放厂家信息的存储区的指针。最长32位              
    返回值：  返回值的含义见B1.8。
    注：该接口不是标准规定接口，如果厂家没有实现则不启用该功能
    */  
    long STDCALL ICC_Reader_Sn(long ReaderHandle, char* sn);
#ifdef __cplusplus
};
#endif
#endif /* SSSE32_H_ */
