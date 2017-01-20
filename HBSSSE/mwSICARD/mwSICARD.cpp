// SSCardDriver.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include "Tools.h"
using mw::reader::utility::Tools;


#include "CLoger.h"
using mw::reader::utility::CLoger;

#include "SSSE32.h"
#include "mwSICARD.h"

#define LENGTH_BUFFER  600		//缓冲区大小


//SSSE 自定义错误码
string getMessage(int nErrNo)
{
    int st = 0;
    unsigned int uiErrNo = abs(nErrNo);
    string strMessage; 
    char buffer[LENGTH_BUFFER] = {0x00};
    if(uiErrNo >= 0x6100 && uiErrNo <= 0x61FF)
    {
        uint8_t flag = uiErrNo &0x00FF;
        sprintf(buffer, "正常处理。 可以通过后续 GET RESPONSE 命令得到的额外数据长度: %d", flag);
        strMessage = string(buffer);
    } 
    else if(uiErrNo >= 0x63C0 && uiErrNo <= 0x63CF)
    {
        uint8_t flag = uiErrNo &0x000F;
        sprintf(buffer, "PIN校验失败，剩余次数%d次", flag);
        strMessage = string(buffer);
    }  
    else if(uiErrNo >= 0x6C00 && uiErrNo <= 0x6CFF)
    {
        uint8_t flag = uiErrNo &0x00FF;
        sprintf(buffer, "长度错误,Le 错误； 实际长度:0x%02X", flag);
        strMessage = string(buffer);
    }  
    else
    {
        if (nErrNo > 0)
        {
            nErrNo  = 0 - nErrNo;
        }
        switch(nErrNo)
        {
        case IFD_OK                                         : strMessage = string("执行成功");                      break;	//0  			//
        case IFD_ICC_TypeError                              : strMessage = string("卡片类型不对");                    break;	//-1  		//
        case IFD_ICC_NoExist                                : strMessage = string("无卡");                            break;	//-2  		//
        case IFD_ICC_NoPower                                : strMessage = string("有卡未上电");                     break;	//-3  		//
        case IFD_ICC_NoResponse                             : strMessage = string("卡无应答");                     break;	//-4  		//
        //case IFD_LoadLibrary                                : strMessage = string("加载动态库错");                    break;	//-5  		//
        case IFD_ConnectError                               : strMessage = string("读卡器连接错");                    break;	//-11 		//
        case IFD_UnConnected                                : strMessage = string("未建立连接");                     break;	//-12 		//
        case IFD_BadCommand                                 : strMessage = string("(动态库)不支持该命令");           break;	//-13 		//
        case IFD_ParameterError                             : strMessage = string("(发给动态库的)命令参数错");         break;	//-14 		//
        case IFD_CheckSumError                              : strMessage = string("信息校验和出错");                   break;	//-15 		//
        //case IFD_CardIDFormat                               : strMessage = string("卡识别码或规范版本格式错");          break;	//-20			//
        //case IFD_InternalAuthFailed                         : strMessage = string("内部认证失败（用户卡不合法）");        break;	//-21			//
        //case IFD_DataNotMatchCard                           : strMessage = string("传入数据与卡内不符");                 break;	//-22			//
        //case IFD_DataNotLegal                               : strMessage = string("传入数据不合法");                   break;	//-23			//
        //case IFD_PsamKeyLevelNotEnough                      : strMessage = string("密钥权限不够");                 break;	//-24			//转到加密机流程     
        //case IFD_DataNotExist                               : strMessage = string("此卡文件结构中无传入的文件名或数据项");                 break;	//-24			//转到加密机流程
        //case IFD_CancelEnterPass                            : strMessage = string("用户取消密码输入");                  break;	//-31			//
        //case IFD_EnterPassTimeout                           : strMessage = string("密码输入操作超时");                  break;	//-32			//
        //case IFD_PasswordLength                             : strMessage = string("输入密码长度错误");break;	//-33			//
        //case IFD_PasswordNotMatch                           : strMessage = string("两次输入密码不一致");                 break;	//-34			//
        //case IFD_DefaultPin                                 : strMessage = string("初始密码不能交易");                  break;	//-35			//（预留
        //case IFD_SetDefaultPin                              : strMessage = string("不能改为初始密码");                  break;	//-36			//（预留
        //case IFD_IDReaderNotExist                           : strMessage = string("未配置身份证读取模块");                break;	//-37			//
        //case IFD_DataFormat                                 : strMessage = string("运算数据含非法字符");                 break;	//-41			//
        //case IFD_DataLength                                 : strMessage = string("运算数据长度错");                   break;	//-42			//
        //case IFD_PinWrong                                   : strMessage = string("PIN校验失败，剩余次数N次"); break;    //-51			//
        //case IFD_PinLocked                                  : strMessage = string("PIN锁定");                                  break;    //-52			//
        //case IFD_PsamNotFound                               : strMessage = string("无PSAM卡");                               break;	//-2201		//转到加密机流程
        //case IFD_PsamAlgorithmNotSupport                    : strMessage = string("PSAM卡算法不支持");break;	//-2202		//转到加密机流程
        //case IFD_PsamRKssseNotSupport                       : strMessage = string("PSAM卡内没有RKssse密钥");break;	//-2203		//转到加密机流程
        //case IFD_NotNeedEncryptMachine                      : strMessage = string("不需要加密机认证");                               break;	//-2204		//转到加密机流程
        //case IFD_ExternalAuthFaileRemain2                   : strMessage = string("外部认证失败，剩余可尝试次数2次");        break;	//-25536	//
        //case IFD_ExternalAuthFaileRemain1                   : strMessage = string("外部认证失败，剩余可尝试次数1次");        break;	//-25537	//
        //case IFD_ExternalAuthFaileRemain0                   : strMessage = string("外部认证失败，剩余可尝试次数0次");        break;	//-25538	//
        //case IFD_WrongLength                                : strMessage = string("Lc/Le不正确");                              break;	//-26368	//
        //case IFD_InvalidStatus                              : strMessage = string("命令不接受（无效状态）");                   break;	//-26881	//
        //case IFD_INSNotMatchWithFileStruture                : strMessage = string("命令与文件结构不相符、当前文件非所需文件");break;	//-27009	//
        //case IFD_SaftyStatusNotSupport                      : strMessage = string("不满足安全条件");                           break;	//-27010	//
        //case IFD_KeyLocked                                  : strMessage = string("密钥锁定（算法锁定）鉴别方法锁定");          break;	//-27011	//
        //case IFD_ReferenceDataInvalid                       : strMessage = string("引用数据无效、随机数无效");                  break;	//-27012	//
        //case IFD_ConditionsNotSupport                       : strMessage = string("不满足使用条件、应用被锁定、应用未选择、余额上溢");break;	//-27013	//
        //case IFD_InvalidDataOfSafeMessage                   : strMessage = string("安全报文数据项不正确、MAC不正确");             break;	//-27016	//
        //case IFD_ParametersOfDataField                      : strMessage = string("数据域参数不正确");                          break;	//-27264	//
        //case IFD_FunctionNotSupportedOrCardLocked           : strMessage = string("不支持该功能、卡中无MF、卡被锁定、应用锁定");    break;	//-27265	//
        //case IFD_FileNotFound                               : strMessage = string("未找到文件、文件标识相重、SFI不正确");           break;	//-27266	//
        //case IFD_RecordNotFound                             : strMessage = string("未找到记录");                                 break;	//-27267	//
        //case IFD_IFD_ReferenceDataNotFoundOrKeyNotFound     : strMessage = string("未找到引用数据、密钥未找到");                 break;	//-27272	//
        //case IFD_MacWrong                                   : strMessage = string("MAC无效");                                 break;	//-37634	//
        //case IFD_ApplicationLocked                          : strMessage = string("应用已被永久锁定、卡片锁定");             break;	//-37635	//
        //case IFD_KeyNotFound                                : strMessage = string("PSAM卡不支持消费交易");             break;	//-37891	//
        //case IFD_MacNeededInvalid                           : strMessage = string("所需MAC（或/和TAC）不可用");              break;	//-37894	//
        default:
            strMessage = string("执行失败");break;
        }
    }

    return strMessage;
}


int __stdcall iDOpenPort(int iReaderPort, int *iReaderhandle, char * iERRInfo)
{
    int st = STATUS_SYSTEM;
    string port;
    string strErrInfo = "NULL";
    
    //TODO 
    if (0 == iReaderPort)
    {
        port = "AUTO";
    }
    else if(iReaderPort >=1 && iReaderPort <= 4)
    {
        char buf[10] = {0x00};
        sprintf(buf, "COM%1d", iReaderPort);
    }
    else if (100 == iReaderPort)
    {
        port = "USB1";
    }
    else
    {
        st = IFD_ParameterError;
        strErrInfo = getMessage(st);
        strcpy(iERRInfo, strErrInfo.c_str());
        st = -1;
        return st;
    }
    st = ICC_Reader_Open((char *)port.c_str());
    if (st < 0 )
    {
        strErrInfo = getMessage(st);
    }
    else
    {
        *iReaderhandle = st;
    }


    strcpy(iERRInfo, strErrInfo.c_str());
    return st;
}

int __stdcall iDCloseReader(int iReaderhandle, char * iERRInfo)
{
    int st = STATUS_SYSTEM;
    string strErrInfo = "NULL";
    st = ICC_Reader_Close(iReaderhandle);
    if (st != IFD_OK)
    {
        strErrInfo = getMessage(st);
    }

    strcpy(iERRInfo, strErrInfo.c_str());
    return st;
}

int __stdcall iPChangePIN(int iReaderhandle, char * szOldPasswd, char * szNewPasswd, char * iERRInfo)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

int __stdcall iPReloadPIN(int iReaderhandle, char * SzCardPasswd, char * iERRInfo)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

int __stdcall iPOutputPIN(int iReaderhandle, char * szPasswd, char * iERRInfo)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

int __stdcall iRCardInfo(int iReaderhandle, char * iVerInfo, char * iPassword, char * iInputFileAddr, char * iOutFileData, char * iERRInfo)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

int __stdcall iWCardInfo(int iReaderhandle, char * iVerInfo, char * iPassword, char * iInputFileAddr, char * iOutFileData, char * iERRInfo)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

int __stdcall iRMFFingerPrintInfo(int iReaderhandle, char * bFingerPrint, char * iERRInfo)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

int __stdcall iWMFFingerPrintInfo(int iReaderhandle, char * bFingerPrint, char * iERRInfo)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

unsigned __stdcall iRCardType(HANDLE ireaderhandle, char *cardtype, char *ierrinfo)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

unsigned __stdcall iRPSAMCardInfo(HANDLE ireaderhandle, char *psamid, char *ierrinfo)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

unsigned __stdcall ICC_verify(HANDLE ireaderhandle, char pin_len, char *pin)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

unsigned __stdcall ICC_change_pin(HANDLE ireaderhandle, char pin_len, char *oldpin, char *newpin)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

unsigned __stdcall ICC_read_bin(HANDLE ireaderhandle, int offset, int len, char *data)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

unsigned __stdcall ICC_write_bin(HANDLE ireaderhandle, int offset, int len, char *data)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}
