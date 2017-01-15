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
#ifndef __SSKEYBDRIVER_MW_H__
#define __SSKEYBDRIVER_MW_H__

#ifdef __cplusplus
extern "C"
{
#endif

    /*
    功能描述	操作密码键盘，显示字符，提示语音后，获取用户输入的密码。
    （1）参数说明	    
    序号	    参数	        输入/输出	    类型	长度（十进制）	    含义
    1	    ctimeout	IN	无符号字符	1	                    键盘输入超时秒数
    2	    cdsp	    IN	字符串	    128	                    要密码键盘显示的内容（预留参数，暂不启用）
    3	    audiocmd	IN	无符号字符	1	                    语音提示代码
    4	    cpasslen	OUT	无符号字符	1	                    输入密码的位数
    5	    cpass	    OUT	字符串	    128	                    用户输入的密码
    返回值	0表示成功；非0表示失败。

    （2）输入参数：
    ctimeout：等待键盘输入的超时时间，单位为秒；
    cdsp：密码键盘液晶显示汉字字符串（预留参数，暂不启用）；
    audiocmd：密码键盘语音提示代码：
    1：语音提示“请输入密码”
    2：语音提示“请再输入一次”
    3：语音提示“请输入原密码”
    4：语音提示“请输入新密码”

    （3）输出参数
    cpasslen：输入密码的长度；
    cpass：输入的密码值，字符串格式；

    （4）函数返回：
     0-成功取得密码，cpasslen=密码位数，cpass=密码；
    -31-用户取消密码输入，cpasslen=0，cpass为空；
    -32-输入操作超时，cpasslen=0，cpass为空；
    -39-其它错误，cpasslen=0，cpass为空；
    */
    long __stdcall iReaderGetPass(unsigned char ctimeout, char *cdsp, unsigned char audiocmd, unsigned char *cpasslen,  char * cpass);


#ifdef __cplusplus
};
#endif


#endif