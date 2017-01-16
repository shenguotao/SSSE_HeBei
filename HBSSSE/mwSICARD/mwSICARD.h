/*****************************************************************************************************
 *                           CopyRight(C), 1993-2015,M&W CARD TECH.Co,Ltd.
 * FileName:    SSCardDriver.h
 * Author:      申国涛       Version:   V0.0.0.1     Date:    2015年9月25日
 * Description:  
 * Others:      
 * Function List:   
 *   1. ....
 *
 * History:
 *  <author> <time> <version > <description  > 
 *  申国涛	2015年9月25日	V0.0.1.0	创建
 *
 *****************************************************************************************************/
#ifndef __MWSICARD_H__
#define __MWSICARD_H__


#define STATUS_COMMUNICATION     0xffff	//Communication error                     	 通讯错误
#define STATUS_OK                0x9000	//OK"                                        操作正确
//#define STATUS_     0x6200	//No card or time out or invalid NAD or PIN"	 无卡
//#define STATUS_     0x6281	//Reading error/data error"                 	 读错误
//#define STATUS_     0x6282	//End of file"                              	 文件结束
//#define STATUS_     0x6300	//Error in PIN check"                       	 错误的PIN
//#define STATUS_     0x63Cx	//incorrect PIN,x retries possible"         	 x次错误PIN
//#define STATUS_     0x6400	//Reset not successful"                     	 复位不成功
//#define STATUS_     0x6500	//EDC or write error"                       	 校验错
//#define STATUS_     0x6581	//Update not successful"                    	 修改数据不成功
//#define STATUS_     0x6700	//Wrong length Lc"                          	 错误的命令长度
//#define STATUS_     0x6900	//Wrong state"                              	 错误的状态
//#define STATUS_     0x6981	//Wrong file type PUK point"                	 错误的文件类别
//#define STATUS_     0x6982	//No file selected"                         	 文件未选择
//#define STATUS_     0x6983	//No retry possible"                        	 不可再试
//#define STATUS_     0x6985	//file exists alread"                       	 文件已存在
//#define STATUS_     0x6A00	//Wrong P1/P2 or file not find"             	 错误的P1/P2
//#define STATUS_     0x6A80	//Wrong parameters command"                 	 错误的参数
//#define STATUS_     0x6A81	//Wrong value for P2"                       	 错误的P2
//#define STATUS_     0x6A82	//File not found"                           	 文件没找到
//#define STATUS_     0x6A84	//No enough memory in file"                 	 文件无足够空间
//#define STATUS_     0x6A86	//Wrong parameters"                         	 错误的参数
//#define STATUS_     0x6B00	//Wrong offset"                             	 错误的偏移量
//#define STATUS_     0x6D00	//Invalid instruction code"                 	 无效的指令代码
//#define STATUS_     0x6E00	//Invalid Class Byte"                       	 无效的CLA
#define STATUS_SYSTEM     0x6FF0	//System error"                             	 系统错误

#ifdef __cplusplus
extern "C"
{
#endif
    
    int __stdcall iDOpenPort(int iReaderPort, int *iReaderhandle, char * iERRInfo);
    int __stdcall iDCloseReader(int iReaderhandle, char * iERRInfo);
    int __stdcall iPChangePIN(int iReaderhandle, char * szOldPasswd, char * szNewPasswd, char * iERRInfo);
    int __stdcall iPReloadPIN(int iReaderhandle, char * SzCardPasswd, char * iERRInfo);
    int __stdcall iPOutputPIN(int iReaderhandle, char * szPasswd, char * iERRInfo);
    int __stdcall iRCardInfo(int iReaderhandle, char * iVerInfo, char * iPassword, char * iInputFileAddr, char * iOutFileData, char * iERRInfo);
    int __stdcall iWCardInfo(int iReaderhandle, char * iVerInfo, char * iPassword, char * iInputFileAddr, char * iOutFileData, char * iERRInfo);
    int __stdcall iRMFFingerPrintInfo(int iReaderhandle, char * bFingerPrint, char * iERRInfo);
    int __stdcall iWMFFingerPrintInfo(int iReaderhandle, char * bFingerPrint, char * iERRInfo);

    unsigned __stdcall iRCardType(HANDLE ireaderhandle, char *cardtype, char *ierrinfo);
/***********************************************************************
功能:
     识别读卡器中卡类型
参数:
     ireaderhandle  	    通讯端口句柄
     cardtype				卡类型，0-cpu卡；1-4428卡；2-4442卡；3-其他
     ierrinfo				出错时候返回错误信息，包括结尾“\0”最大256字节。
返回: 
     =0 	处理成功
     非0 	处理失败
举例:
     ret = iRCardType (ireaderhandle, cardtype, ierrinfo)；
************************************************************************/

    unsigned __stdcall iRPSAMCardInfo(HANDLE ireaderhandle, char *psamid, char *ierrinfo);
/***********************************************************************
功能:
     读PSAM卡号
参数:
     ireaderhandle  	    通讯端口句柄
     psamid				PSAM卡号
     ierrinfo				出错时候返回错误信息，包括结尾“\0”最大256字节。
返回: 
     =0 	处理成功
     非0 	处理失败
举例:
     ret = iRPSAMCardInfo (ireaderhandle, psamid, ierrinfo);
************************************************************************/

    unsigned __stdcall ICC_verify(HANDLE ireaderhandle, char pin_len, char *pin);

/***********************************************************************
功能:
     校验IC卡PIN，此函数只对逻辑加密卡有效
参数:
     ireaderhandle		已打开的通讯端口句柄
     pin_len 			PIN长度
     pin				PIN内容
返回: 
     =0 	处理成功
     非0 	处理失败
说明: 
适用于所有支持的带有加密逻辑的存储卡
举例:
     ret= ICC_verify (ireaderhandle, 2, "FFFF")	;
************************************************************************/

    unsigned __stdcall ICC_change_pin(HANDLE ireaderhandle, char pin_len, 
char *oldpin, char *newpin); 
/***********************************************************************
功能:
     核对PIN并修改PIN，此函数只对逻辑加密卡有效
参数:
     ireaderhandle		已打开的通讯端口句柄
     pin_len 			PIN长度
     oldpin			旧PIN内容
newpin			新PIN内容
返回: 
     =0 	处理成功
     非0 	处理失败
举例:
     ret= ICC_change_pin (ireaderhandle, 2, "FFFF", "FFFF")
************************************************************************/

unsigned __stdcall ICC_read_bin(HANDLE ireaderhandle, int offset, int len, char *data); 
/***********************************************************************
功能:
     从卡上地址offset开始读len个字节到缓冲区data中
参数:
     ireaderhandle		已打开的通讯端口句柄
	 offset			读数据开始的绝对地址
	 len     		欲读数据的长度
	 data			读出的数据
返回: 
     =0 	处理成功
     非0 	处理失败
举例:
     ret= ICC_read_bin (ireaderhandle, 10, 16, data) //将IC卡上10开始26个字节的数据读至data
************************************************************************/

unsigned __stdcall ICC_write_bin(HANDLE ireaderhandle, int offset, int len, char *data); 
/***********************************************************************
功能:
     将缓冲区data中数据写入卡上地址从offset开始len个字节
参数:
     Ireaderhandle		已打开的通讯端口句柄
	 offset			写入数据的绝对地址
	 len     		欲写数据的长度
	 data			写入的数据
返回: 
     =0 	处理成功
     非0 	处理失败
举例:
     ret= ICC_write_bin (ireaderhandle, 10, 16, data) 
************************************************************************/











#ifdef __cplusplus
};
#endif


#endif