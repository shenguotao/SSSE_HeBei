// SSCardDriver.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include "Tools.h"
using mw::reader::utility::Tools;


#include "CLoger.h"
using mw::reader::utility::CLoger;

#include "SSSE32.h"
#include "SSKeyBDriver_MW.h"

#define LENGTH_BUFFER  600		//缓冲区大小


long __stdcall iReaderGetPass(unsigned char ctimeout, char *cdsp, unsigned char audiocmd, unsigned char *cpasslen, char * cpass)
{
    int32_t st = 0;
    long handle = -1;
    uint8_t info[LENGTH_BUFFER] = {0x00};
    uint8_t iLen = 0;
    // 0. 参数检查
    if (audiocmd < 1 || audiocmd > 4 || NULL == cpasslen || NULL == cpass)
    {
        st = -39;
        *cpasslen = 0;
        strcpy(cpass, (char *)info);
        return st;
    }
    

    // 1. 打开设备
    handle = ICC_Reader_Open((char *)"AUTO");
    if (handle < 0)
    {
        st = -39;
        *cpasslen = 0;
        strcpy(cpass, (char *)info);
        return st;
    }
    
    //2. 获取密码
    st = ICC_GetInputPassEx(handle, ctimeout, &iLen, info, (unsigned char *)cdsp, audiocmd);
    if (IFD_OK != st)
    {
        if (IFD_ICC_TypeError == st )
        {
            st = -31;
        } 
        else if (IFD_ICC_NoExist == st)
        {
            st = -32;
        }
        else
        {
            st = -39;
        }
        *cpasslen = 0;
        return st;
    }
    else
    {
        *cpasslen = iLen;
    }
    
    strcpy(cpass, (char *)info);
    ICC_Reader_Close(handle);
    return st;
}
