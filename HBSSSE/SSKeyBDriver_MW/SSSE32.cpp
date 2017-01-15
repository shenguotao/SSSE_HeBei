/*****************************************************************************************************
 *                           CopyRight(C), 1992-2014,M&W CARD TECH.Co,Ltd.
 * FileName:    SSSE32.cpp
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

#include "stdafx.h"
//#include <jni.h>
#include "mwReader.h"
//#include "com_mwcard_Reader.h"

#include "SSSE32.h"

string gs_remark = "M&W Reader";    //动态库中必须定义该字段，要在静态库中使用

    //jlong JNICALL Java_com_mwcard_Reader_mwDevOpenAllReader(JNIEnv* env, jobject object, jstring port, jstring paras);
    int STDCALL mwDevOpenAllReader(const char* port, const char* paras, HANDLE* handle);
#ifdef __cplusplus
extern "C"
{
#endif
    ///**
    // * 下面函数为项目定制打开接口
    // */   
    //JNIEXPORT jlong JNICALL Java_com_mwcard_Reader_mwDevOpen(JNIEnv* env, jobject object,
    //        jstring port, jstring paras)
    //{
    //    return Java_com_mwcard_Reader_mwDevOpenAllReader(env, object, port, paras);
    //}
    
    int STDCALL mwDevOpen(const char *port, const char *paras, HANDLE *handle)
    {
        return mwDevOpenAllReader(port, paras, handle);
    }

#ifdef __cplusplus
}
;
#endif


#ifdef __cplusplus
extern "C"
{
#endif


    static int getSSSE32Slot(unsigned char ICC_Slot_No)
    {
        int32_t CardType = SLOT_CONTACT;
        if (ICC_Slot_No == 0x00)
        {
            CardType = SLOT_CONTACTLESS; //非接触卡座
            return CardType;
        }

        else if (ICC_Slot_No > 0 && ICC_Slot_No < 0x10)
        {
            CardType = SLOT_CONTACT; //接触卡座
        } 
        else if (ICC_Slot_No > 0x10 && ICC_Slot_No < 0x20)
        {
            CardType = 1+ ICC_Slot_No& 0x0F; //SAM
        }
        else
        {
            return IFD_ParameterError;
        }


        //改版本使用最新的跨省应用标准
        //int32_t CardType = SLOT_CONTACT;
        //if (ICC_Slot_No == 0x00)
        //{
        //    CardType = SLOT_CONTACTLESS; //非接触卡座
        //    return CardType;
        //}

        //else if (ICC_Slot_No > 0 && ICC_Slot_No < 0x10)
        //{
        //    CardType = SLOT_CONTACT; //接触卡座
        //} 
        //else if (ICC_Slot_No > 0x10 && ICC_Slot_No < 0x20)
        //{
        //    CardType = 1+ ICC_Slot_No& 0x0F; //SAM
        //}
        //else
        //{
        //    return IFD_ParameterError;
        //}


        return CardType;
    }

    //输入 mwReaderErrorCode mwReader基础库错误码
    static int getSSSEErrorCode(int mwReaderErrorCode)
    { 
        int st = 0;
        switch(mwReaderErrorCode)
        {
        case MWERROR_OK                   :st = IFD_OK; break;//操作成功 
        case MWERROR_INIT                 :st = IFD_ConnectError; break;  //初始化通信端口失败
        case MWERROR_CLOSE                :st = IFD_ConnectError; break;  //关闭通信端口失败
        case MWERROR_NOT_INIT             :st = IFD_UnConnected; break;  //指定的端口未打开
        case MWERROR_NOTEXIST             :st = IFD_UnConnected; break;  //设备未连接
        case MWERROR_PORT_COMMUNICATE     :st = IFD_ConnectError; break;	//端口通讯发生错误
        case MWERROR_NORESPONSE           :st = IFD_ConnectError; break; //设备模块无响应
        case MWERROR_SET_PORT             :st = IFD_ConnectError; break;  //设置端口属性失败
        case MWERROR_PARAM                :st = IFD_ParameterError; break;  //参数错误
        case MWERROR_PARAM_MODE           :st = IFD_ParameterError; break;  //通讯模式错误，暂时只支持COM/USB口通讯
        case MWERROR_PARAM_BAUD           :st = IFD_ParameterError; break;  //不支持的串口波特率
        case MWERROR_PARAM_HANDLE         :st = IFD_ParameterError; break;  //无效的句柄
        case MWERROR_PARAM_LENGTH         :st = IFD_ParameterError; break;  //数据长度错误
        case MWERROR_ED                   :st = IFD_CheckSumError; break;  //加解密失败
        case MWERROR_KEYTYPE              :st = IFD_ParameterError; break;	//非法的密码类型     
        case MWERROR_PARAM_SLOT           :st = IFD_ParameterError; break;  //不支持的卡座编号
        case MWERROR_PARAM_CARDTYPE       :st = IFD_ICC_TypeError; break;  //不支持的卡片类型
        case MWERROR_OPEN_MODE            :st = IFD_ParameterError; break;  //寻卡模式不合法
        case MWERROR_BLOCK_OVERFLOW       :st = IFD_ParameterError; break;  //块号不合法
        case MWERROR_SECTOR_OVERFLOW      :st = IFD_ParameterError; break;  //扇区号不合法
        case MWERROR_VALUE_FORMAT         :st = IFD_ParameterError; break;  //非值存储区域
        case MWERROR_ADDRESS_OVERFLOW     :st = IFD_ParameterError; break;	//地址越界      
        case MWERROR_PARAM_OVERFLOW       :st = IFD_ParameterError; break;  //缓冲区溢出
        case MWERROR_NOT_SUPPORT          :st = IFD_BadCommand; break;   //命令不支持
        case MWERROR_SC_RESET             :st = IFD_ICC_TypeError; break;	//CPU卡复位出错
        case MWERROR_SC_APDU              :st = IFD_ICC_TypeError; break;	//CPU卡APDU失败
        case MWERROR_NOCARD               :st = IFD_ICC_NoExist; break;	//未检测到卡片
        case MWERROR_NOPOWER              :st = IFD_ICC_NoPower; break;  //卡座有卡未上电
        case MWERROR_NOTAG                :st = IFD_ICC_NoExist; break;	//无卡
        case MWERROR_AUTH                 :st = IFD_ICC_NoResponse; break;	//验证失败
        case MWERROR_NOT_AUTH             :st = IFD_ParameterError; break;	//卡片尚未被认证 
        case MWERROR_VALUE_OVERFLOW       :st = IFD_ParameterError; break;	//值溢出错误
        case MWERROR_RESTORE              :st = IFD_ICC_NoResponse; break;	//调用restore函数出错
        case MWERROR_TRANSFER             :st = IFD_ICC_NoResponse; break;	//调用transfer函数出错
        case MWERROR_READ                 :st = IFD_ICC_NoResponse; break;	//调用read函数出错
        case MWERROR_WRITE                :st = IFD_ICC_NoResponse; break;	//调用write函数出错
        case MWERROR_INCREMENT            :st = IFD_ICC_NoResponse; break;	//调用increment函数出错
        case MWERROR_DECREMENT            :st = IFD_ICC_NoResponse; break;	//调用decrement函数出错 
        case MWERROR_LOADKEY              :st = IFD_ICC_NoResponse; break;	//调用LOADKEY函数出错
        case MWERROR_ANTICOLL             :st = IFD_ICC_NoResponse; break;	//防冲突失败
        case MWERROR_SELECT               :st = IFD_ICC_NoResponse; break;	//选卡失败
        case MWERROR_MEMCOUNT_ZERO        :st = IFD_ICC_NoResponse; break;   //存储卡错误计数等于0
        case MWERROR_MEM_VERIFY           :st = IFD_ICC_NoResponse; break;   //存储卡密码错误
        case MWERROR_MEM_READ             :st = IFD_ICC_NoResponse; break;   //存储卡读失败
        case MWERROR_MEM_WRITE            :st = IFD_ICC_NoResponse; break;   //存储卡写失败
        case MWERROR_MEM_ADDR             :st = IFD_ICC_NoResponse; break;   //存储卡地址溢出
        case MWERROR_FONT_NOTSUPPORT      :st = IFD_ParameterError; break;  //非GB2312字符
        case MWERROR_LOCALE_NOTSUPPORT    :st = IFD_ParameterError; break;  //主机不支持GB2312编码
        case MWERROR_FONT_OVERFLOW        :st = IFD_ParameterError; break;  //显示的信息太长
        case MWERROR_PINPAD_CC            :st = -1; break;   //用户取消密码输入
        case MWERROR_PINPAD_TO            :st = -2; break;   //用户密码输入操作超时
        case MWERROR_PINPAD_STAT          :st = IFD_ParameterError; break;   //未处于密码输入状态
        case MWERROR_PINPAD_GOING         :st = IFD_ParameterError; break;   //输入密码还未完成，返回按键个数、*号串
        case MWERROR_WRITE_EEPROM         :st = IFD_ICC_NoResponse; break;  //写配置信息失败
        case MWERROR_UNKNOWN              :st = IFD_ICC_NoResponse; break;  //读卡器未知错误
        case MWERROR_DATAFORMAT           :st = IFD_CheckSumError; break;  //通讯数据格式错误
        case MWERROR_TIMEOUT              :st = IFD_ICC_NoResponse; break;  //操作超时
        case MWERROR_MIFARE_VALUE         :st = IFD_ICC_NoResponse; break;  //Mifare值操作失败
        case MWERROR_NO_KEY               :st = IFD_ParameterError; break;  //缺少密钥
        case MWERROR_MAGCARD_DATA         :st = IFD_CheckSumError; break;   //磁条卡数据错误
        case MWERROR_PROTOCOL             :st = IFD_CheckSumError; break;  //通信协议不支持
        case MWERROR_VERSION              :st = IFD_CheckSumError; break;  //版本信息不一致
        case MWERROR_FIELD                :st = IFD_CheckSumError; break;  //未找到该属性ID
        case MWERROR_CARDNORESPONSE       :st = IFD_ICC_NoResponse;break;   //卡片无应答
        case MWERROR_CARDTYPE             :st = IFD_ICC_TypeError;break;    //卡片类型不对
        default:
            st = IFD_ConnectError;
        }
        return st;
    }

    //1. 必须
    long STDCALL ICC_Reader_Open(char* dev_Name)
    {
        int32_t st = IFD_OK;
        HANDLE icdev = INVALID_HANDLE_VALUE;
        //1. 参数检查
        if (dev_Name == NULL || strlen(dev_Name) != 4)
        {
            st = IFD_ParameterError;
            return st;
        }
        string strPort;
        string strBaud;
        if (dev_Name[3] >= '0' && dev_Name[3] <= '9')
        {
            if (0 == memcmp(dev_Name, "COM", 3) )
            {
                strBaud = "115200";
                st = mwDevOpen( dev_Name,  strBaud.c_str(), &icdev);
                if (st >= 0)
                {
                    st = (long) (icdev);
                }
                else
                {
                    st = getSSSEErrorCode(st);
                }
            }
            else if (0 == memcmp(dev_Name, "USB", 3))
            {
                st = mwDevOpen( dev_Name,  strBaud.c_str(), &icdev);
                if (st >= 0)
                {
                    st = (long) (icdev);
                }
                else
                {
                    st = getSSSEErrorCode(st);
                }
            }
            else
            {
                st = IFD_ParameterError;
            }
        }
        else 
        {
            if (0 == memcmp(dev_Name, "AUTO", 4) )
            {
                // 先打开USB,然后打开COM
                char name[10] = {0x00};
                int index = 1;
                for (index = 1; index <= 9; index++)
                {
                    sprintf(name, "USB%d", index);
                    st = mwDevOpen( name, NULL, &icdev);
                    if (st >= 0)
                    {
                        st = (long) (icdev);
                        return st;
                    }
                }
                for (index = 1; index <= 9; index++)
                {
                    sprintf(name, "COM%d", index);
                    st = mwDevOpen( name, "115200", &icdev);
                    if (st >= 0)
                    {
                        st = (long) (icdev);
                        return st;
                    }
                }
                st = getSSSEErrorCode(st);

            }
            else
            {
                st = IFD_ParameterError;
            }
        }


        return st;
    }

    //2. 必须
    long STDCALL ICC_Reader_Close(long ReaderHandle)
    {
        int32_t st = IFD_OK;
        if(ReaderHandle < 0)
        {
            return IFD_ParameterError;
        }
        st = mwDevClose((HANDLE) ReaderHandle);
        if (st >= 0)
        {
            st = IFD_OK;
        }
        else
        {
            st = getSSSEErrorCode(st);
        }
        return st;
    }

    //3. 必须
    long STDCALL ICC_Reader_PowerOn(long ReaderHandle, unsigned char ICC_Slot_No,
        unsigned char* Response)
    {
        int32_t st = IFD_OK;
        //1. 参数检查
        if(ReaderHandle < 0)
        {
            return IFD_ParameterError;
        }
        int32_t CardType = getSSSE32Slot(ICC_Slot_No);
        if (CardType < 0)
        {
            return CardType;
        }

        st = mwSmartCardReset((HANDLE) ReaderHandle, CardType, Response, 0x00); //社保卡使用0x00-9600 波特率复位
        if (st < 0)
        {
            //TODO 处理特定的返回值，
            if (st == MWERROR_PARAM_HANDLE)
            {
                //当句柄为社保有效句柄但不为当前返回句柄时
                st = IFD_UnConnected;
            }
            else if(MWERROR_PARAM == st)
            {
                st = IFD_ParameterError;
            }
            else
            {
                st = getSSSEErrorCode(st);
            }
        }
        return st; //report_error(st);
    }

    //4. 必须
    long STDCALL ICC_Reader_PowerOff(long ReaderHandle, unsigned char ICC_Slot_No)
    {
        int32_t st = IFD_OK;
        //1. 参数检查
        if(ReaderHandle < 0)
        {
            return IFD_ParameterError;
        }
        int32_t CardType = getSSSE32Slot(ICC_Slot_No);
        if (CardType < 0)
        {
            return CardType;
        }
        st = mwSmartCardPowerDown((HANDLE) ReaderHandle, CardType);
        if (st < 0)
        {
            if (st == MWERROR_PARAM_HANDLE)
            {
                //当句柄为社保有效句柄但不为当前返回句柄时
                st = IFD_UnConnected;
            }
            else if(MWERROR_PARAM == st)
            {
                st = IFD_ParameterError;
            }
            else
            {
                st = getSSSEErrorCode(st);
            }
        }
        else
        {
            st = IFD_OK;
        }
        return st;
    }

    //5. 必须
    long STDCALL ICC_Reader_GetStatus(long ReaderHandle, unsigned char ICC_Slot_No)
    {
        int32_t st = IFD_OK;
        //1. 参数检查
        if(ReaderHandle < 0)
        {
            return IFD_ParameterError;
        }
        int32_t CardType = getSSSE32Slot(ICC_Slot_No);
        if (CardType < 0)
        {
            return CardType;
        }
        int32_t status = 0;
        st = mwGetCardStatus((HANDLE) ReaderHandle, CardType, &status);
        if (st < 0)
        {
            if (st == MWERROR_PARAM_HANDLE)
            {
                //当句柄为社保有效句柄但不为当前返回句柄时
                st = IFD_UnConnected;
            }
            else if(MWERROR_PARAM == st)
            {
                st = IFD_ParameterError;
            }
            else
            {
                st = getSSSEErrorCode(st);
            }
        }
        else
        {
            if (status == 0)
            {
                st = IFD_ICC_NoExist; //无卡
            }
            else if (status == 1)
            {
                st = IFD_ICC_NoPower; //有卡未上电
            }
            else if (status == 2)
            {
                st = IFD_OK; //有卡已上电
            }

        }
        return st;
    }

    //6. 必须
    long STDCALL ICC_Reader_Application(long ReaderHandle, unsigned char ICC_Slot_No,
        long Lenth_of_Command_APDU, unsigned char* Command_APDU, unsigned char* Response_APDU)
    {
        int32_t st = IFD_OK;

        //1. 参数检查
        if(ReaderHandle < 0)
        {
            return IFD_ParameterError;
        }
        int32_t CardType = getSSSE32Slot(ICC_Slot_No);
        if (CardType < 0)
        {
            return CardType;
        }
        st = mwSmartCardCommand((HANDLE) ReaderHandle, CardType, Command_APDU, Lenth_of_Command_APDU,
            Response_APDU);
        if (st < 0)
        {
            //TODO 处理特定的返回值，
            if (st == MWERROR_PARAM_HANDLE)
            {
                //当句柄为社保有效句柄但不为当前返回句柄时
                st = IFD_UnConnected;
            }
            else if(MWERROR_PARAM == st)
            {
                st = IFD_ParameterError;
            }
            else
            {
                st = getSSSEErrorCode(st);
            }
        }
        return st;
    }

    //7. 必须
    long STDCALL ICC_Reader_Libinfo(char* info)
    {
        char TempInfo[33] = "\0";   //社保规定长度为32个字符

        strcpy(TempInfo, "M&W             ");
        strcat(TempInfo, "X9            ");
        strcat(TempInfo, "12");
        memcpy(info, TempInfo, sizeof(TempInfo));
        return IFD_OK;
    }


    //8. 必须
    long STDCALL ICC_GetInputPassEx(long ReaderHandle, unsigned char ctime, unsigned char* rlen,
        unsigned char* cpass, unsigned char* cshow, unsigned char cmd)
    {
        int32_t st = IFD_OK;
        if(ReaderHandle < 0)
        {
            return IFD_ParameterError;
        }
        //否则使用最新接口
        st = mwPassGetInputExt((HANDLE) ReaderHandle, ctime, cmd, *rlen, (char *) cpass);
        if (st < 0)
        {
            if (st == MWERROR_PINPAD_CC)
            {
                st = -1;
            }
            else if (st == MWERROR_PINPAD_TO)
            {
                st = -2;
            }
            else
            {
                st = getSSSEErrorCode(st);
            }
        }
        else
        {
            *rlen = st;
            st = IFD_OK;
        }

        return st;

    }

    //9 非必须
    long STDCALL ICC_Reader_Sn(long ReaderHandle, char* sn)
    {
        if(ReaderHandle < 0)
        {
            return IFD_ParameterError;
        }
        char TempInfo[33] = "\0";   //社保规定长度为32个字符
        int st = mwDevGetSerialNumber((HANDLE)ReaderHandle, sn);
        if (st < 0)
        {
            st = getSSSEErrorCode(st);
        }
        else
        {
            st = IFD_OK;
        }
        return st;
    }


#ifdef __cplusplus
}
;
#endif
