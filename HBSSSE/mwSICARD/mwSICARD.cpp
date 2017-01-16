// SSCardDriver.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include "Tools.h"
using mw::reader::utility::Tools;


#include "CLoger.h"
using mw::reader::utility::CLoger;


#include "mwSICARD.h"

#define LENGTH_BUFFER  600		//缓冲区大小


int __stdcall iDOpenPort(int iReaderPort, int *iReaderhandle, char * iERRInfo)
{
    int st = STATUS_SYSTEM;
    //TODO 

    return st;
}

int __stdcall iDCloseReader(int iReaderhandle, char * iERRInfo)
{
    int st = STATUS_SYSTEM;
    //TODO 

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
