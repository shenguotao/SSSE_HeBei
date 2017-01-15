/*****************************************************************************************************
 *                           CopyRight(C), 1992-2014,M&W CARD TECH.Co,Ltd.
 * FileName:    mwReader.h
 * Author:      申国涛       Version:   V0.0.0.1     Date:    2014年9月5日
 * Description:  
 * Others:      
 * Function List:   
 *   1. ....
 *
 * History:
 *  <author> <time> <version > <description  > 
 *  申国涛	2014年9月5日	V0.0.1.0	创建
 *
 *****************************************************************************************************/

#ifndef MWREADER_H_
#define MWREADER_H_

//===============================错误码===========================================
#define MWERROR_OK                   0	//操作成功 
#define MWERROR_INIT                 -0X0001  //初始化通信端口失败
#define MWERROR_CLOSE                -0X0002  //关闭通信端口失败
#define MWERROR_NOT_INIT             -0X0003  //指定的端口未打开
#define MWERROR_NOTEXIST             -0X0004  //设备未连接
#define MWERROR_PORT_COMMUNICATE     -0X0005	//端口通讯发生错误
#define MWERROR_NORESPONSE           -0X0006 //设备模块无响应
#define MWERROR_SET_PORT             -0X0007  //设置端口属性失败
#define MWERROR_PARAM                -0X0008  //参数错误
#define MWERROR_PARAM_MODE           -0X0009  //通讯模式错误，暂时只支持COM/USB口通讯
#define MWERROR_PARAM_BAUD           -0X000A  //不支持的串口波特率
#define MWERROR_PARAM_HANDLE         -0X000B  //无效的句柄
#define MWERROR_PARAM_LENGTH         -0X000C  //数据长度错误
#define MWERROR_ED                   -0X000D  //加解密失败
#define MWERROR_KEYTYPE              -0X000E	//非法的密码类型     
#define MWERROR_PARAM_SLOT           -0X000F  //不支持的卡座编号
#define MWERROR_PARAM_CARDTYPE       -0X0010  //不支持的卡片类型
#define MWERROR_OPEN_MODE            -0X0011  //寻卡模式不合法
#define MWERROR_BLOCK_OVERFLOW       -0X0012  //块号不合法
#define MWERROR_SECTOR_OVERFLOW      -0X0013  //扇区号不合法
#define MWERROR_VALUE_FORMAT         -0X0014  //非值存储区域
#define MWERROR_ADDRESS_OVERFLOW     -0X0015	//地址越界      
#define MWERROR_PARAM_OVERFLOW       -0X0016  //缓冲区溢出
#define MWERROR_NOT_SUPPORT          -0X0017   //命令不支持
#define MWERROR_SC_RESET             -0X0018	//CPU卡复位出错
#define MWERROR_SC_APDU              -0X0019	//CPU卡APDU失败
#define MWERROR_NOCARD               -0X001A	//未检测到卡片
#define MWERROR_NOPOWER              -0X001B  //卡座有卡未上电
#define MWERROR_NOTAG                -0X001C	//无卡
#define MWERROR_AUTH                 -0X001D	//验证失败
#define MWERROR_NOT_AUTH             -0X001E	//卡片尚未被认证 
#define MWERROR_VALUE_OVERFLOW       -0x001F	//值溢出错误
#define MWERROR_RESTORE              -0X0020	//调用restore函数出错
#define MWERROR_TRANSFER             -0X0021	//调用transfer函数出错
#define MWERROR_READ                 -0X0022	//调用read函数出错
#define MWERROR_WRITE                -0X0023	//调用write函数出错
#define MWERROR_INCREMENT            -0X0024	//调用increment函数出错
#define MWERROR_DECREMENT            -0X0025	//调用decrement函数出错 
#define MWERROR_LOADKEY              -0X0026	//调用LOADKEY函数出错
#define MWERROR_ANTICOLL             -0X0027	//防冲突失败
#define MWERROR_SELECT               -0X0028	//选卡失败
#define MWERROR_MEMCOUNT_ZERO        -0X0029   //存储卡错误计数等于0
#define MWERROR_MEM_VERIFY           -0X002A   //存储卡密码错误
#define MWERROR_MEM_READ             -0X002B   //存储卡读失败
#define MWERROR_MEM_WRITE            -0X002C   //存储卡写失败
#define MWERROR_MEM_ADDR             -0X002D   //存储卡地址溢出
#define MWERROR_FONT_NOTSUPPORT      -0X002E  //非GB2312字符
#define MWERROR_LOCALE_NOTSUPPORT    -0X002F  //主机不支持GB2312编码
#define MWERROR_FONT_OVERFLOW        -0X0030  //显示的信息太长
#define MWERROR_PINPAD_CC            -0X0031   //用户取消密码输入
#define MWERROR_PINPAD_TO            -0X0032   //用户密码输入操作超时
#define MWERROR_PINPAD_STAT          -0X0033   //未处于密码输入状态
#define MWERROR_PINPAD_GOING         -0X0034   //输入密码还未完成，返回按键个数、*号串
#define MWERROR_WRITE_EEPROM         -0X0035  //写配置信息失败
#define MWERROR_UNKNOWN              -0X0036  //读卡器未知错误
#define MWERROR_DATAFORMAT           -0X0037  //通讯数据格式错误
#define MWERROR_TIMEOUT              -0X0038  //操作超时
#define MWERROR_MIFARE_VALUE         -0X0039  //Mifare值操作失败
#define MWERROR_NO_KEY               -0X003A  //缺少密钥
#define MWERROR_MAGCARD_DATA         -0X003B   //磁条卡数据错误
#define MWERROR_PROTOCOL             -0X003C  //通信协议不支持
#define MWERROR_VERSION              -0X003D  //版本信息不一致
#define MWERROR_FIELD                -0X003E  //未找到该属性ID
#define MWERROR_IDCARD               -0X003F    //二代身份证不存在或者读取出错
#define MWERROR_CARDNORESPONSE       -0X0040 //卡片无响应
#define MWERROR_CARDTYPE             -0X0041  //卡片类型错误

//===============================通讯接口类型===========================================
#define COMMUNICATION_COM   0   //串口设备
#define COMMUNICATION_USB   1   //USB设备
#define COMMUNICATION_TCP   2   //TCP/IP设备

//===============================LED灯状态===========================================
#define LED_CLOSE       0X00    //关闭
#define LED_OPEN        0X01    //打开
#define LED_NOCHANGE    0X10    //保持现状
#define LED_FLASHING    0X11    //以1秒的间隔交互闪烁 


//===============================读卡器卡座编号===========================================
#define SLOT_CONTACT        0x00    //接触式卡座
#define SLOT_CONTACTLESS    0x01    //非接触式卡座
#define SLOT_SAM1           0x02    //扩展的SAM卡座
#define SLOT_SAM2           0x03    //扩展的SAM卡座
#define SLOT_SAM3           0x04    //扩展的SAM卡座
#define SLOT_SAM4           0x05    //扩展的SAM卡座


//
//===============================寻卡模式===========================================
#define OPEN_MODE_STD   0   //STD模式,只能寻到空闲状态下的卡片，被激活或停活（Halt）的卡片不会响应
#define OPEN_MODE_ALL   1   //ALL模式,能寻到空闲状态和已经被停活（Halt）的卡片		

//
//===============================密码类型===========================================
#define MIFARE_KEY_A	0X00	//A密码
#define	MIFARE_KEY_B	0X01	//B密码

//
//===============================卡座状态===========================================
#define CARDSTATUS_NONE         0   //无卡
#define CARDSTATUS_NOPOWERON    1   //有卡未上电
#define CARDSTATUS_POWERON      2   //有卡已上电


//
//===============================存储卡卡片类型表===========================================
#define CONTACT_AT24C01A        1	
#define CONTACT_AT24C02         2	
#define CONTACT_AT24C04         3	
#define CONTACT_AT24C08         4	
#define CONTACT_AT24C16	        5	
#define CONTACT_AT24C64	        6	
#define CONTACT_AT24C128	    7	
#define CONTACT_AT24C256	    8	
#define CONTACT_AT45D041        10	
#define CONTACT_AT24C32	        11  //add by sgt 2015-03-02
#define CONTACT_SSF1101         12	
#define CONTACT_AT88SC1608      13	
#define CONTACT_SLE4432         20	
#define CONTACT_SLE4442	        21	
#define CONTACT_SLE2042	        22	
#define CONTACT_SLE4418	        30	
#define CONTACT_SLE4428	        31	
#define CONTACT_SLE4404	        40	
#define CONTACT_SLE4406	        41	
#define CONTACT_AT88SC101	    50	
#define CONTACT_AT88SC102	    51	
#define CONTACT_AT88SC1604	    52	
#define CONTACT_AT88SC1604B	    53	
#define CONTACT_AT93C46A	    60	
#define CONTACT_AT93C46	        61	
#define CONTACT_AT93C57	        62	
#define CONTACT_CPU	            255


//
//===============================TYPEA 卡片类型===========================================
#define  CARDTYPE_MIFARE_S50	0x0004	//Mifare 标准 1k 卡
#define  CARDTYPE_MIFARE_S70	0x0002	//Mifare 标准 4k 卡
#define  CARDTYPE_MIFARE_LIGHT	0x0010	//Mifare Light
#define  CARDTYPE_MIFARE_UTRALIGHT	0x0044	//Mifare UtraLight
#define  CARDTYPE_CPU			0x0008	//非接触CPU卡

//
//===============================MIFARE 卡片参数===========================================
#define MIFARE_BLOCK_LENGTH 16//每块长度(bytes)
#define MIFARE_KEY_LENGTH   6//密钥长度(bytes)
#define MIFARE_SECTOR_S50_MAX   15//S50卡最大扇区号
#define MIFARE_SECTOR_S70_MAX   39//S70卡最大扇区号
#define MIFARE_BLOCK_S50_MAX    63//S50卡最大块号
#define MIFARE_BLOCK_S70_MAX    255//S70卡最大块号

//4442 
//===============================4442卡属性===========================================
#define CAPACITY_4442           256
#define PROTECTION_SIZE_4442    32
#define KEY_LENGTH_4442         3

//4428
//===============================4428卡属性===========================================
#define CAPACITY_4428           1024
#define PROTECTION_SIZE_4428    1024
#define KEY_LENGTH_4428         2

//
//===============================密码语音===========================================
#define VOICE_NONE          0X00    //不提示
#define VOICE_ENTERKEY	    0X01    //请输入密码
#define VOICE_RE_ENTER	    0X02    //请再输入一次
#define VOICE_ENTER_OLDKEY  0X03    //请输入原密码
#define VOICE_ENTER_NEWKEY  0X04    //请输入新密码

//
//===============================LCD参数===========================================
#define LCD_LINE_1          0X01    //lcd 第1行标志
#define LCD_LINE_2          0X02    //lcd 第2行标志
#define LCD_LINE_3          0X03    //lcd 第3行标志
#define LCD_LINE_4          0X04    //lcd 第4行标志
#define LCD_OFFSET_BEGIN    0X01    //lcd 每一行中字符的起始地址，从1开始，到16结束
#define LCD_OFFSET_END      0X10    //lcd 每一行中字符的起始地址，从1开始，到16结束

//
//===============================加密解密标志===========================================
#define ENTRDES_DE          0X00    //DES  解密
#define ENTRDES_EN          0X01    //DES  加密
#define ENTRDES_DE3         0X10    //3DES  解密
#define ENTRDES_EN3         0X11    //3DES  加密


//
//===============================标准磁条卡数据长度===========================================
#define TRACK1_LENGTH   79  //第一磁道数据长度
#define TRACK2_LENGTH   40  //第二磁道数据长度
#define TRACK3_LENGTH   107 //第三磁道数据长度

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
extern "C"{
#endif

    /*
    * Function:	mwDevGetUsbList		
    * Description:	获取插入的USB设备列表		
    * Input:       icdev:	通讯设备句柄		
    * Output:		list:	USB设备列表	格式如下:
    *            <READER>R60000113011200001</READER><READER>R60000113011200002</READER>
    * Return:		扫描到的设备个数,如果返回值小于0表示错误，请查看错误代码表
    * Others: 
    */
    int STDCALL mwDevGetUsbList(char *list);

    /*
    * Function:	mwDevOpen		
    * Description:	打开读卡器		
    * Input:       port:   "COM1","COM2",......"COM256"(串口读写器)
    *                      "USB","USB1","USB2",......"USB10"(USB接口读写器,"USB"后面跟的是顺序号)
    *              paras:  例如: "115200"(当操作串口读卡器时，该参数为波特率)。串口设备默认波特率为115200
    *                            "设备信息"(当port为"USB"时，通过设备信息来访问USB设备，可以打开指定的读卡器，如果没有设备信息，则默认打开找到的第一个明华读卡器)
    *                            ""(当通过序号打开USB设备时，该参数为空)
    * Output:		handle  通讯设备句柄		
    * Return:		如果返回值小于0表示错误，请查看错误代码表
    * Others:		当为串口操作时，波特率有效值如下：
    *                 "9600"
    *                 "19200"
    *                 "38400"
    *                 "57600"
    *                 "115200"
    * 举例：1. 打开串口2上的读写器,波特率为115200
    *         HANDLE icdev = -1;
    *         int32_t st = mwDevOpen("COM2", "115200", &icdev);
    *         if(st < 0){//请查看错误代码}
    *         else{//操作成功}
    * 
    *     2. 电脑上只有一个明华读卡器
    *         HANDLE icdev = -1;
    *         int32_t st = mwDevOpen("USB", "", &icdev);
    *         if(st < 0){//请查看错误代码}
    *         else{//操作成功}
    * 
    *     3. 打开指定的USB读卡器
    *         int32_t st = 0;
    *         UsbDevices devList;
    *         st = mwDevGetUsbList(&devList);
    *         if(st > 0)
    *         {
    *         HANDLE icdev = -1;
    *         int32_t st = mwDevOpen("USB", devList.usb1, &icdev);    //打开第一个设备
    *         if(st < 0){//请查看错误代码}
    *         else{//操作成功}
    *         }
    *         else
    *         {
    *         //没有找到设备
    *         }
    * 
    *     4. 根据顺序号打开USB设备，请注意：必须保证已插入指定数量的设备，否则会失败
    *         HANDLE icdev = -1;
    *         int32_t st = mwDevOpen("USB2", "", &icdev);
    *         if(st < 0){//请查看错误代码}
    *         else{//操作成功}
    */
    int STDCALL mwDevOpen(const char *port, const char *paras, HANDLE *handle);
    
    /*
    * Function:	mwDevClose		
    * Description:	关闭读卡器		
    * Input:       icdev:	通讯设备句柄		
    * Output:		无				
    * Return:		>=0	正确;	<0	错误	
    * Others: 
    */
    int STDCALL mwDevClose(HANDLE icdev);

    /*
    * Function:	mwDevGetHardwareVer		
    * Description:	获取硬件版本信息		
    * Input:       icdev:	通讯设备句柄		
    * Output:		strHardwareVer:   以'\0'为结尾的ANSI字符串。请最少预留51字节的存储空间			
    * Return:		字符串长度,如果返回值小于0表示错误，请查看错误代码表
    * Others: 
    */
    int STDCALL mwDevGetHardwareVer(HANDLE icdev, char *strHardwareVer);

    /*
    * Function:	mwDevGetSerialNumber		
    * Description:	获取产品序列号		
    * Input:       icdev:	通讯设备句柄		
    * Output:		strSerialNumber:   以'\0'为结尾的ANSI字符串。请最少预留17字节的存储空间				
    * Return:		字符串长度,如果返回值小于0表示错误，请查看错误代码表
    * Others: 
    */
    int STDCALL mwDevGetSerialNumber(HANDLE icdev, char *strSerialNumber);

    /*
    * Function:	mwDevGetRemark		
    * Description:	获取备注信息		
    * Input:       icdev:	通讯设备句柄		
    * Output:		strRemark:   以'\0'为结尾的ANSI字符串。请最少预留33字节的存储空间			
    * Return:		字符串长度,如果返回值小于0表示错误，请查看错误代码表
    * Others: 
    */
    int STDCALL mwDevGetRemark(HANDLE icdev, char *strRemark);

    /*
    * Function:	mwDevBeep		
    * Description:	蜂鸣器控制		
    * Input:       icdev:      通讯设备句柄
    *              beepTimes:	蜂鸣次数
    *              interval:	蜂鸣间隔 每100ms一个单位
    *              time:		蜂鸣时间 每100ms一个单位
    *              例如:	要蜂鸣3次，每次间隔100ms,蜂鸣时间200ms
    *              mw_dev_beep(devNo,3,1,2);
    * Output:		无  			
    * Return:		>=0	正确;	<0	错误		
    * Others:    
    */
    int STDCALL mwDevBeep(HANDLE icdev, int beepTimes, int interval, int time);

    /*
    * Function:	mwDevLed		
    * Description:	指示灯控制,最多支持4个指示灯	
    * Input:       icdev:	通讯设备句柄
    *           led1: 指示灯1控制信息
    *           led2: 指示灯2控制信息
    *           led3: 指示灯3控制信息
    *           led4: 指示灯4控制信息
    *               取值如下：
    *               0X00    保持现状
    *               0X01    关闭        
    *               0X10    打开 
    *               0X11    以1秒的间隔交互闪烁    
    * Output:		无				
    * Return:		>=0	正确;	<0	错误	
    * Others: 
    */
    int STDCALL mwDevLed(HANDLE icdev, int led1, int led2, int led3, int led4);

    /*
    * Function:	mwDevReadConfig		
    * Description:	读自定义数据区	
    * Input:       icdev:  通讯设备句柄
    *              offset:	起始地址
    *              length:	数据长度		
    * Output:	    data:	数据存储区		
    * Return:	    >=0	已正确读取的数据长度;	<0	错误		
    * Others:	
    */
    int STDCALL mwDevReadConfig(HANDLE icdev, int offset, int length, unsigned char data[]);

    /*
    * Function:	mwDevWriteConfig		
    * Description:	写自定义数据区	
    * Input:       icdev:  通讯设备句柄
    *              offset:	起始地址
    *              length:	数据长度
    *              data:	数据存储区
    * Output:	    无			
    * Return:	    >=0	已正确写入的数据长度;	<0	错误		
    * Others:	
    */
    int STDCALL mwDevWriteConfig(HANDLE icdev, int offset, int length, const unsigned char data[]);
    
     /*
     * Function: mwDevSetBaud
     * Description:  设置临时通信波特率,该操作执行成功后直到再次上电，一直使用传入的波特率进行通信。
     * Input:       icdev:   通讯设备句柄
     *               baud: 波特率，有效值如下：
     *                  1200
     *                  2400
     *                  4800
     *                  9600
     *                  19200
     *                  38400
     *                  57600
     *                  115200
     * Output:       无
     * Return:       >=0 正确; <0  错误
     * Others:       设置波特率后用户必须手动关闭当前句柄，然后再次使用指定的波特率打开设备.当设备端点后，恢复成默认波特率
     */
    int STDCALL mwDevSetBaud(HANDLE icdev, int baud);

    /*
    * Function:	mwDevSetTransferMode		
    * Description:	设置数据传输模式	
    * Input:       icdev:  通讯设备句柄
    *               mode:	0, 明文传输， 1 密文传输	
    * Output:	    	
    * Return:	    上次的传输模式;	<0	错误		
    * Others:		设备默认是明文传输，考虑到安全性，建议用户在打开设备后设置为密文传输
    */
    int STDCALL mwDevSetTransferMode(HANDLE icdev, int mode);
    
    /*
    * Function:	mwDevRFControl		
    * Description:	射频天线控制	
    * Input:       icdev:  通讯设备句柄
    *       mode:   0x00 - 关闭射频模块
    *               0x01~0xff - 表示复位时间，，以5ms为单位。
    *               例如：0x01: 复位射频，延时 5ms.   
    *                    0x81: 复位射频，延时(0x81 *5) ms.   
    * Output:	    无			
    * Return:	    >=0	正确;	<0	错误		
    * Others:	
    */
    int STDCALL mwDevRFControl(HANDLE icdev, int mode);
    
    /*
    * Function:	    mwGetCardStatus
    * Description:	获取卡片状态	
    * Input:        icdev:  通讯设备句柄
    *               slotNumber: 卡座编号
    *                   0	:   接触式卡座
    *                   1	:   非接触式大卡座
    *                   2--5:   扩展的第1--4个SAM卡座
    * Output:	    status: 0 无卡
    *                       1 有卡未上电
    *                       2 有卡已经上电
    * Return:	    >=0	正确;	<0	错误		
    * Others:	
    */
    int STDCALL mwGetCardStatus(HANDLE icdev, int slotNumber, int *status);

    /*
    mode 参数类型，具体内容如下
    0，传统蓝牙名称，最大32字节ASCII码；
    1，BLE蓝牙名称，最大24字节ASCII码；
    2，传统蓝牙地址，6字节小端格式；
    3，BLE蓝牙地址，6字节小端格式；

    len 数据长度
    data 数据
    */
    int STDCALL mwDevConfigBLE(HANDLE icdev, int mode, int len, char data[]);
    /*
    * Function:     mwSmartCardReset		
    * Description:	智能卡复位，返回复位应答信息
    * Input:        icdev:      通讯设备句柄    
    *               slotNumber: 卡座编号
    *                   0	:   接触式卡座
    *                   1	:   非接触式大卡座
    *                   2--5:   扩展的第1--4个SAM卡座  
    *               opFlag: 
    *                   -----------------------------------------------------------------------
    *                   当slotNumber=1 时表示打开模式：
    *                   0x00	STD模式,只能寻到空闲状态下的卡片，被激活或停活（Halt）的卡片不会响应
    *                   0x01	ALL模式,能寻到空闲状态和已经被停活（Halt）的卡片
    *                   -----------------------------------------------------------------------
    *                   当slotNumber为其他值时表示复位波特率标志，有效值如下：
    *                   0x00     -9600
    *                   0x01     -38400
    *                   0x02     -57600
    *                   0x03     -115200
    *                   0x04     -19200
    * Output:	    atrInfo:    复位信息，格式为byte数组.请最少预留50字节的存储空间.
    * Return:	    复位信息长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:    
    */
    int STDCALL mwSmartCardReset(HANDLE icdev, int slotNumber, unsigned char atrInfo[], int opFlag);

    /*
    * Function:     mwSmartCardReset_HEX		
    * Description:	智能卡复位，返回16进制字符串格式的复位应答信息
    * Input:        icdev:      通讯设备句柄    
    *               slotNumber: 卡座编号
    *                   0	:   接触式卡座
    *                   1	:   非接触式大卡座
    *                   2--5:   扩展的第1--4个SAM卡座     
    *               opFlag: 
    *                   -----------------------------------------------------------------------
    *                   当slotNumber=1 时表示打开模式：
    *                   0x00	STD模式,只能寻到空闲状态下的卡片，被激活或停活（Halt）的卡片不会响应
    *                   0x01	ALL模式,能寻到空闲状态和已经被停活（Halt）的卡片
    *                   -----------------------------------------------------------------------
    *                   当slotNumber为其他值时表示复位波特率标志，有效值如下：
    *                   0x00     -9600
    *                   0x01     -38400
    *                   0x02     -57600
    *                   0x03     -115200
    *                   0x04     -19200
    * Output:	    atrInfo:    复位信息，格式为16进制字符串.请最少预留100字节的存储空间.
    * Return:	    16进制字符串长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:    
    */
    int STDCALL mwSmartCardReset_HEX(HANDLE icdev, int slotNumber, char *strArtInfo, int opFlag);

    /*
    * Function:     mwSmartCardReset_EXT		
    * Description:	智能卡复位，返回扩展的复位应答信息
    * Input:        icdev:      通讯设备句柄    
    *               slotNumber: 卡座编号
    *                   0	:   接触式卡座
    *                   1	:   非接触式大卡座
    *                   2--5:   扩展的第1--4个SAM卡座    
    *               opFlag: 
    *                   -----------------------------------------------------------------------
    *                   当slotNumber=1 时表示打开模式：
    *                   0x00	STD模式,只能寻到空闲状态下的卡片，被激活或停活（Halt）的卡片不会响应
    *                   0x01	ALL模式,能寻到空闲状态和已经被停活（Halt）的卡片
    *                   -----------------------------------------------------------------------
    *                   当slotNumber为其他值时表示复位波特率标志，有效值如下：
    *                   0x00     -9600
    *                   0x01     -38400
    *                   0x02     -57600
    *                   0x03     -115200
    *                   0x04     -19200
    * Output:	    atrInfo:    复位信息，格式为byte数组.请最少预留50字节的存储空间.
    * Return:	    复位信息长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:    
    *       atrInfo 格式如下:
    *               Data[0]:    卡片协议信息，具体值定义如下表
    *                           非接触: 0x0A	 Type A
    *                                   0x0B  Type B
    *                                   0x0C  felica 
    *                           接触: 0x00	T=0协议	
    *                                   0x01 T=1协议
    *                           	
    *                           		
    *               Data[1]:	卡片UID长度n，若n=0，表示无UID
    *               Data[2]~[n+1]:	    UID
    *               Data[n+2]:		    复位信息ATR长度
    *               Data[n+3]~[...]:	复位信息ATR
    */
    int STDCALL mwSmartCardReset_EXT(HANDLE icdev, int slotNumber, unsigned char atrInfo[], int opFlag);

    /*
    * Function:     mwSmartCardReset_HEXEXT		
    * Description:	智能卡复位，返回16进制字符串格式的扩展的复位应答信息
    * Input:        icdev:      通讯设备句柄    
    *               slotNumber: 卡座编号
    *                   0	:   接触式卡座
    *                   1	:   非接触式大卡座
    *                   2--5:   扩展的第1--4个SAM卡座  
    *               opFlag: 
    *                   -----------------------------------------------------------------------
    *                   当slotNumber=1 时表示打开模式：
    *                   0x00	STD模式,只能寻到空闲状态下的卡片，被激活或停活（Halt）的卡片不会响应
    *                   0x01	ALL模式,能寻到空闲状态和已经被停活（Halt）的卡片
    *                   -----------------------------------------------------------------------
    *                   当slotNumber为其他值时表示复位波特率标志，有效值如下：
    *                   0x00     -9600
    *                   0x01     -38400
    *                   0x02     -57600
    *                   0x03     -115200
    *                   0x04     -19200
    * Output:	    atrInfo:    复位信息，格式为16进制字符串.请最少预留50字节的存储空间.
    * Return:	    复位信息长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:    
    *       atrInfo 格式如下:
    *               Data[0]:    卡片协议信息，具体值定义如下表
    *                           0x00	0x01	0x0A	0x0B
    *                           T=0协议	T=1协议	Type A	Type B
    *               Data[1]:	卡片UID长度n，若n=0，表示无UID
    *               Data[2]~[n+1]:	    UID
    *               Data[n+2]:		    复位信息ATR长度
    *               Data[n+3]~[...]:	复位信息ATR
    */
    int STDCALL mwSmartCardReset_HEXEXT(HANDLE icdev, int  slotNumber,  char* strArtInfo, int opFlag);

    /*
    * Function:     mwSmartCardCommand		
    * Description:	智能卡传输指令
    * Input:        icdev: 通讯设备句柄    
    *               slotNumber: 卡座编号
    *                   0	:   接触式卡座
    *                   1	:   非接触式大卡座
    *                   2--5:   扩展的第1--4个SAM卡座  
    *               srcData:    智能卡指令
    *               srcLen:     指令长度
    * Output:	    dstInfo:    应答数据，格式为byte数组. 	
    * Return:	    应答数据长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:     
    */
    int STDCALL mwSmartCardCommand(HANDLE icdev, int slotNumber, const unsigned char srcData[], int srcLen, unsigned char dstInfo[]);

    /*
    * Function:     mwSmartCardCommand_HEX		
    * Description:	智能卡传输指令,数据交互格式为16进制字符串
    * Input:        icdev: 通讯设备句柄    
    *               slotNumber: 卡座编号
    *                   0	:   接触式卡座
    *                   1	:   非接触式大卡座
    *                   2--5:   扩展的第1--4个SAM卡座  
    *               srcData:    智能卡指令(16进制字符串)
    * Output:	    dstInfo:    应答数据，格式为	16进制字符串，请用户保留足够的存储空间
    * Return:	    应答数据长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:     
    */
    int STDCALL mwSmartCardCommand_HEX(HANDLE icdev, int slotNumber, const char *strSrc, char *strDst);

    /*
     * Function:     mwSmartCardCommand_EXT
     * Description:  智能卡传输指令
     * Input:        icdev: 通讯设备句柄
     *              slotNumber: 卡座编号
     *                  0   :   接触式卡座
     *                  1   :   非接触式大卡座
     *                  2--5:   扩展的第1--4个SAM卡座
     *              srcData:    智能卡指令
     *              srcLen:     指令长度
     * Output:       dstInfo:    应答数据，格式为byte数组.
     * Return:       应答数据长度,如果返回值小于0表示错误，请查看错误代码表
     * Others:  该接口内部处理COS状态码(SW1SW2 = 0X61XX/SW1SW2 = 0X6CXX)
     */
    int STDCALL mwSmartCardCommand_EXT(HANDLE icdev, int slotNumber,
            const unsigned char srcData[], int srcLen, unsigned char  dstInfo[]);

    /*
     * Function:     mwSmartCardCommand_HEXEXT
     * Description: 智能卡传输指令,数据交互格式为16进制字符串
     * Input:        icdev: 通讯设备句柄
     *              slotNumber: 卡座编号
     *                  0   :   接触式卡座
     *                  1   :   非接触式大卡座
     *                  2--5:   扩展的第1--4个SAM卡座
     *              srcData:    智能卡指令(16进制字符串)
     * Output:      dstInfo:    应答数据，格式为    16进制字符串，请用户保留足够的存储空间
     * Return:      应答数据长度,如果返回值小于0表示错误，请查看错误代码表
     * Others:      该接口内部处理COS状态码(SW1SW2 = 0X61XX/SW1SW2 = 0X6CXX)
     */
    int STDCALL mwSmartCardCommand_HEXEXT(HANDLE icdev, int slotNumber,
            const char *strSrc, char *strDst);

    /*
     * Function:     mwSmartCardPowerDown
     * Description:	对CPU卡下电
     * Input:        icdev: 通讯设备句柄
     *              slotNumber: 卡座编号
     *              0	:   接触式大卡座
     *              1	:   非接触式卡座
     *              2--5:   扩展的第1--4个SAM卡座
     * Output:		无
     * Return:		>=0	正确;	<0	错误
     * Others:
     */
    int STDCALL mwSmartCardPowerDown(HANDLE icdev, int slotNumber);

    /*
    * Function:	mwRequestTypeB     
    * Description:	请求非接触TYPE-B类型的卡片 		
    * Input:       icdev:      通讯设备句柄
    *               mode:
    *               AFI:
    *               N:
    * Output:      ATQB:    卡片复位信息,格式为byte数组
    * Return:		复位信息长度	,如果返回值小于0表示错误，请查看错误代码表
    * Others:    
    */
    int STDCALL mwRequestTypeB(HANDLE icdev, int mode, int AFI, int N, unsigned char ATQB[]);

    /*
    * Function:	mwTypeBAttrib     
    * Description:	获取属性(非接触TYPE-B类型的卡片 )		
    * Input:       icdev:     通讯设备句柄
    *               PUPI:
    * Output:      attrib:    属性信息,格式为byte数组
    * Return:		属性信息长度	,如果返回值小于0表示错误，请查看错误代码表
    * Others:    
    */
    int STDCALL mwTypeBAttrib(HANDLE icdev, unsigned char PUPI[], unsigned char attrib[]);

    /*
    * Function:	mwRFTBHalt	
    * Description:	将选定的TYPE B 类型的卡片置于HALT模式		
    * Input:		icdev: 通讯设备句柄
    * Output:     	无
    * Return:      >=0	正确;	<0	错误
    * Others:     
    */
    int STDCALL mwHaltTypeB(HANDLE icdev);  

    /*
    * Function:     mwOpenCardDecimal     
    * Description:  打开非接触卡片     
    * Input:        icdev:      通讯设备句柄
    *               openMode:   打开模式：
    *                   0x00    STD模式,只能寻到空闲状态下的卡片，被激活或停活（Halt）的卡片不会响应
    *                   0x01    ALL模式,能寻到空闲状态和已经被停活（Halt）的卡片    
    * Output:       uid:    卡片序列号
    * Return:       卡号长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:       该接口最大只能找到卡号为4/7 byte 的卡片
    */
    int STDCALL mwOpenCardDecimal(HANDLE icdev, int openMode , unsigned long long *uid );

    /*
    * Function:     mwOpenCard     
    * Description:	打开非接触卡片 		
    * Input:        icdev:      通讯设备句柄
    *               openMode:   打开模式：
    *                   0x00	STD模式,只能寻到空闲状态下的卡片，被激活或停活（Halt）的卡片不会响应
    *                   0x01	ALL模式,能寻到空闲状态和已经被停活（Halt）的卡片	
    * Output:       cardUid:    卡片序列号,格式为byte数组
    * Return:       卡号长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:    
    */
    int STDCALL mwOpenCard(HANDLE icdev, int openMode , unsigned char cardUid[] );

    /*
    * Function:     mwOpenCard_EXT     
    * Description:	打开非接触卡片 		
    * Input:        icdev:      通讯设备句柄
    *               openMode:   打开模式：
    *                   0x00	STD模式,只能寻到空闲状态下的卡片，被激活或停活（Halt）的卡片不会响应
    *                   0x01	ALL模式,能寻到空闲状态和已经被停活（Halt）的卡片	
    * Output:       cardUid:    卡片序列号,格式为byte数组
    *               cardType:   卡片类型
    *               sak:        卡片SAK
    * Return:       卡号长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:    
    */
    int STDCALL mwOpenCard_EXT(HANDLE icdev, int openMode, unsigned char cardUid[], unsigned short *cardType, unsigned char *sak);

    /*
    * Function:	mwCloseCard	
    * Description:	关闭卡片	
    * Input:		icdev: 通讯设备句柄
    * Output:     	无
    * Return:      >=0	正确;	<0	错误
    * Others:     
    */
    int STDCALL mwCloseCard(HANDLE icdev);

    /*
    * Function:	mwRFTAHalt	
    * Description:	将选定的卡片置于HALT模式，需要Request All将其唤醒		
    * Input:		icdev: 通讯设备句柄
    * Output:     	无
    * Return:      >=0	正确;	<0	错误
    * Others:     
    */
    int STDCALL mwHalt(HANDLE icdev);
   
    /*
    * Function:	mwRFTARequest	
    * Description:	请求卡TYPE A 类型卡片		
    * Input:       icdev:      通讯设备句柄
    *               openMode:   打开模式
    *               0x00	STD模式,只能寻到空闲状态下的卡片，被激活或停活（Halt）的卡片不会响应
    *               0x01	ALL模式,能寻到空闲状态和已经被停活（Halt）的卡片	
    * Output:      cardType:   卡片类型  		            
    * Return:		>=0	正确;	<0	错误
    * Others:     
    *               卡片类型
    *               Mifare 标准 1k   : 0x0004
    *               Mifare 标准 4k   : 0x0002
    *               Mifare Light     : 0x0010
    *               Mifare UtraLight : 0x0044
    *               CPU :            :0x0008
    */
    int STDCALL mwRequest(HANDLE icdev, int openMode, unsigned short *cardType);

    /*
    * Function:	mwRFTAAnticoll
    * Description:	防冲突
    * Input:       icdev:      通讯设备句柄
    * Output:      cardUid:    卡片序列号,格式为byte数组
    * Return:		卡号长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:     
    */
    int STDCALL mwAnticoll(HANDLE icdev, unsigned char cardUid[]);

    /*
    * Function:	mwRFTASelect		
    * Description:	选卡	
    * Input:       icdev:	通讯设备句柄
    *               cardUid:    卡片序列号,格式为byte数组
    *               idLen：     卡号长度
    * Output:      cardSak:	卡片SAK
    * Return:	    >=0	正确;	<0	错误
    * Others:     
    */
    int STDCALL mwSelect(HANDLE icdev, const unsigned char cardUid[], int idLen, unsigned char *cardSak);

    /*
    * Function:	mwRFTARats		
    * Description:	获取TYPE-A类型的智能卡复位信息	
    * Input:       icdev:	    通讯设备句柄
    * Output:      atrInfo:    卡片复位信息,格式为byte数组 
    * Return:	    复位信息长度,如果返回值小于0表示错误，请查看错误代码表	
    * Others:     
    */
    int STDCALL mwRats(HANDLE icdev, unsigned char atrInfo[]);

    /*
    * Function:	mwMifareAuth	
    * Description:	验证密码		
    * Input:       icdev:	    通讯设备句柄
    *              mode:	    密码类型：	
    *                   0x00	验证A密码
    *                   0x01	验证B密码
    *              sectorNo:	要验证的扇区号
    *              key:	6字节长度的密码，格式为byte数组
    * Output:		无	
    * Return:		>=0	正确;	<0	错误	
    * Others:     
    */
    int STDCALL mwMifareAuth(HANDLE icdev, int mode, int sectorNo, const unsigned char key[]);

    /*
    * Function:	mwMifareAuthHex	
    * Description:	验证密码		
    * Input:       icdev:	    通讯设备句柄
    *              mode:	    密码类型：	
    *                   0x00	验证A密码
    *                   0x01	验证B密码
    *              sectorNo:	要验证的扇区号
    *              strKey:	    以'\0'为结尾的16进制字符串，密码长度应为12。
    * Output:		无	
    * Return:		>=0	正确;	<0	错误	
    * Others:     
    */
    int STDCALL mwMifareAuthHex(HANDLE icdev, int mode, int sectorNo, const char *strKey);

    /*
    * Function:	mwMifareBlockAbs			
    * Description:	获得指定扇区中第0块在卡片中的绝对索引号			
    * Input:       sectorNo: 扇区号
    * Output:      NULL
    * Return:	   指定扇区中第0块在卡片中的绝对索引号,如果返回值小于0表示错误，请查看错误代码表
    * Others:     	index = mwMifareBlockAbs(1) + 0;    //获得第1扇区中第0块的绝对地址应为4
    *               index = mwMifareBlockAbs(1) + 1;    //获得第1扇区中第1块的绝对地址应为5
    *               index = mwMifareBlockAbs(1) + 2;    //获得第1扇区中第2块的绝对地址应为6
    *               index = mwMifareBlockAbs(1) + 3;    //获得第1扇区中第3块的绝对地址应为7
    */
    int STDCALL mwMifareBlockAbs( int sectorNo);

    /*
    * Function:	mwMifareread			
    * Description:	读数据			
    * Input:       icdev: 通讯设备句柄
    *               blockNo:	要读取的块号，对于S50卡，取值为0～63;对于S70卡，取值为0～255;
    * Output:      blockData:	读取的数据，mifare卡每块数据共16字节。
    * Return:		数据长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:     
    */
    int STDCALL mwMifareRead(HANDLE icdev, int blockNo, unsigned char blockData[]);

    /*
    * Function:	mwMifarewrite		
    * Description:	写数据		
    * Input:       icdev: 通讯设备句柄
    *               blockNo:	要写的块号
    *               blockData:	写入的数据
    * Output:		无		
    * Return:		>=0	正确;	<0	错误			
    * Others:     
    */
    int STDCALL mwMifareWrite(HANDLE icdev, int blockNo, const unsigned char blockData[]);

    /*
    * Function:	mwMifareinitVal		
    * Description:	将数据块初始化为值存储区	 
    * Input:       icdev:      通讯设备句柄
    *               blockNo:	块号
    *               initValue:	写入的数据
    * Output:		无	
    * Return:		>=0	正确;	<0	错误	
    * Others:     
    */
    int STDCALL mwMifareInitVal(HANDLE icdev, int blockNo, unsigned int initValue);

    /*
    * Function:	mwMifarereadVal	
    * Description:	读值	
    * Input:       icdev:      通讯设备句柄
    *               blockNo:	块号
    * Output:      value:		读取的数值
    * Return:		>=0	正确;	<0	错误	
    * Others:      确保操作之前该块是值存储区
    */
    int STDCALL mwMifareReadVal(HANDLE icdev, int blockNo, unsigned int *value);

    /*
    * Function:	mwMifareincrement	
    * Description:	增值		
    * Input:       icdev:      通讯设备句柄
    *               boockNo:	块号
    *               value:	    增加的数值
    * Output:		无		
    * Return:		>=0	正确;	<0	错误		
    * Others:      确保操作之前该块是值存储区
    */
    int STDCALL mwMifareIncrement(HANDLE icdev, int blockNo, unsigned int value);

    /*
    * Function:	mwMifaredecrement
    * Description:	减值	
    * Input:       icdev:      通讯设备句柄
    *               blockNo:	减值的块号
    *               value:	    减少的值
    * Output:		无	
    * Return:		>=0	正确;	<0	错误	
    * Others:      确保操作之前该块是值存储区
    */
    int STDCALL mwMifareDecrement(HANDLE icdev, int blockNo, unsigned int value);

    /*
    * Function:	mwMifarerestore
    * Description:	将某值格式存储块的数据传入卡的内部寄存器中，进行此项操作必须验证该扇区的密码		
    * Input:       icdev:      通讯设备句柄
    *               blockNo:	寄存数据的块号
    * Output:		无
    * Return:		>=0	正确;	<0	错误
    * Others:     
    */
    int STDCALL mwMifareRestore(HANDLE icdev, int blockNo);

    /*
    * Function:	mwMifaretransfer	
    * Description:	将内部寄存器的数据传送到某一块中，进行此项操作必须验证该扇区的密码		
    * Input:       icdev:      通讯设备句柄
    *               blockNo:	传送数据的块号
    * Output:     	无
    * Return:      >=0	正确;	<0	错误
    * Others:     
    */
    int STDCALL mwMifareTransfer(HANDLE icdev, int blockNo);


    /*
    * Function:	mwSelectMemoryCard     
    * Description:	通知读卡器要操作的存储卡类型
    * Input:       icdev:      通讯设备句柄
    *              memoryCardType: 存储卡类型标志，请参考存储卡类型表
    * Output:      NULL
    * Return:		>=0	表示真正的卡片类型;	<0	错误
    * Others:    
    */
    int STDCALL mwSelectMemoryCard(HANDLE icdev, int memoryCardType);


    /**
    * Function:	mwRead4442
    * Description:	读4442/4432卡， 其容量为256字节
    * Input:		icdev:	通讯设备句柄
    *               offset: 偏移地址，其值范围0～1023
    *               length: 字符串长度，其值范围1～1024
    * Output:		data:	读出数据
    * Return:		数据长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:		
    */
    int STDCALL mwRead4442(HANDLE icdev, int offset, int length, unsigned char data[]);

    /**
    * Function:	mwWrite4442
    * Description:	写4442/4432卡， 其容量为256字节
    * Input:		icdev:	通讯设备句柄
    *               offset: 偏移地址，其值范围0～255
    *               length: 字符串长度，其值范围1～256
    *               data:	写入的数据
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwWrite4442(HANDLE icdev, int offset, int length, const unsigned char data[]);

    /**
    * Function:	mwPRead4442
    * Description:	读4442/4432保护位
    * Input:		icdev:	通讯设备句柄
    *               offset: 偏移地址，其值范围0～31
    *               length: 字符串长度，其值范围1～32
    * Output:		data:	读出保护位标志，
    * Return:		数据长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:		字节地址0～31为保护区，共32个字节，每个字节用1 bit的保护位来标志是否被置保护
    *               ，为0表示已置保护，为1表示未置保护。已置的保护位不可恢复，被保护的数据只可读，不可更改，成为固化数据。
    */
    int STDCALL mwPRead4442(HANDLE icdev, int offset, int length, unsigned char pData[]);

    /**
    * Function:	mwPWrite4442
    * Description:	4442/4432卡校验数据并写保护
    * Input:		icdev:	通讯设备句柄
    *               offset: 偏移地址，其值范围0～31
    *               length: 字符串长度，其值范围1～32
    *               data:	保护数据，必须和卡中已存在的数据一致
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwPWrite4442(HANDLE icdev, int offset, int length, const unsigned char data[]);


    /**
    * Function:	mwVerifyPassword4442
    * Description:	校验密码，4442卡密码长度为3字节.密码核对正确前，全部数据只可读，不可改写。 
    *               核对密码正确后可以更改数据，包括密码再内。
    * Input:		icdev:	通讯设备句柄
    *               key:	密码
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwVerifyPassword4442(HANDLE icdev, const unsigned char key[]);

    /**
    * Function:	mwReadPassword4442
    * Description:	读密码，4442卡密码长度为3字节
    * Input:		icdev:	通讯设备句柄
    * Output:		key:	密码
    * Return:		密码长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:		
    */
    int STDCALL mwReadPassword4442(HANDLE icdev, unsigned char key[]);

    /**
    * Function:	mwChangePassword4442
    * Description:	修改密码，4442卡密码长度为3字节
    * Input:		icdev:	通讯设备句柄
    *               key:	新密码
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwChangePassword4442(HANDLE icdev, const unsigned char key[]);

    /**
    * Function:	mwGetErrorCounter4442
    * Description:	读取错误计数错误计数器，初始值为3，密码核对出错1次，便减1，若计数器值为0
    *               ，则卡自动锁死，数据只可读出，不可再进行更改也无法再进行密码核对；
    *               若不为零时，有一次密码核对正确，可恢复到初始值3
    * Input:		icdev:	通讯设备句柄
    *               key:	新密码
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwGetErrorCounter4442(HANDLE icdev, int *counter);


    /**
    * Function:	mwRead4428
    * Description:	读4428/4418卡， 其容量为1024字节
    * Input:		icdev:	通讯设备句柄
    *               offset: 偏移地址，其值范围0～1023
    *               length: 字符串长度，其值范围1～1024
    * Output:		data:	读出数据
    * Return:		数据长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:		
    */
    int STDCALL mwRead4428(HANDLE icdev, int offset, int length, unsigned char data[]);

    /**
    * Function:	mwWrite4428
    * Description:	写4428/4418卡， 其容量为1024字节
    * Input:		icdev:	通讯设备句柄
    *               offset: 偏移地址，其值范围0～1023
    *               length: 字符串长度，其值范围1～1024
    *               data:	写入的数据
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwWrite4428(HANDLE icdev, int offset, int length, const unsigned char data[]);

    /**
    * Function:	mwPReadData4428
    * Description:	读4428/4418数据以及保护位
    * Input:		icdev:	通讯设备句柄
    *               offset: 偏移地址，其值范围0～1023
    *               length: 字符串长度，其值范围1～1024
    * Output:		data:	存放要读出的数据,其大小应为2*length 
    *
    * Return:		数据长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:		举例： uint8_t databuff[4];
    *               st=mwPReadData4428(icdev,0,2,databuff);
    *               //从偏移地址0开始带保护位读出2个字节数据放入databuff中，
    *               //每个字节的后面跟一个保护位标志字节，该字节值为0x00表示
    *               //相应的字节已保护，0xff表示未被保护。
    *               例如：读出
    *               databuff[0]=0x13,databuff[1]=0x00,
    *               databuff[2]=0x20,databuff[3]=0xff;
    *               表示偏移地址0字节被保护，偏移地址1字节未被保护。
    */
    int STDCALL mwPReadData4428(HANDLE icdev, int offset, int length,  unsigned char data[]);

    /**
    * Function:	mwPWrite4428
    * Description:	4428/4418卡校验数据并写保护
    * Input:		icdev:	通讯设备句柄
    *               offset: 偏移地址，其值范围0～1023
    *               length: 字符串长度，其值范围1～1024
    *               data:	保护数据，必须和卡中已存在的数据一致
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwPWrite4428(HANDLE icdev, int offset, int length, const unsigned char data[]);

    /**
    * Function:	mwPWriteData4428
    * Description:	4428/4418卡写数据并置保护
    * Input:		icdev:	通讯设备句柄
    *               offset: 偏移地址，其值范围0～1023
    *               length: 字符串长度，其值范围1～1024
    *               data:	要写入的数据
    * Output:		无
    * Return:		数据长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:		
    */
    int STDCALL mwPWriteData4428(HANDLE icdev, int offset, int length, const unsigned char data[]);

    /**
    * Function:	mwVerifyPassword4428
    * Description:	校验密码，4428卡密码长度为2字节.密码核对正确前，全部数据只可读，不可改写。 
    *               核对密码正确后可以更改数据，包括密码再内。
    * Input:		icdev:	通讯设备句柄
    *               key:	密码
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwVerifyPassword4428(HANDLE icdev, const unsigned char key[]);

    /**
    * Function:	mwReadPassword4428
    * Description:	读密码，4428卡密码长度为2字节
    * Input:		icdev:	通讯设备句柄
    * Output:		key:	密码
    * Return:		密码长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:		
    */
    int STDCALL mwReadPassword4428(HANDLE icdev, unsigned char key[]);

    /**
    * Function:	mwChangePassword4428
    * Description:	修改密码，4428卡密码长度为3字节
    * Input:		icdev:	通讯设备句柄
    *               key:	新密码
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwChangePassword4428(HANDLE icdev, const unsigned char key[]);

    /**
    * Function:	mwGetErrorCounter4428
    * Description:	读取错误计数错误计数器，初始值为8，密码核对出错1次，便减1，若计数器值为0
    *               ，则卡自动锁死，数据只可读出，不可再进行更改也无法再进行密码核对；
    *               若不为零时，有一次密码核对正确，可恢复到初始值8
    * Input:		icdev:	通讯设备句柄
    *               key:	新密码
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwGetErrorCounter4428(HANDLE icdev, int *counter);

    /**
    * Function:	mwRead24CXX
    * Description:	读24CXX系列卡片
    * Input:		cardType:
    *                 1---  AT24C01A 卡容量: 01 * 1024/8 = 256 字节
    *                 2---  AT24C02 卡容量: 02 * 1024/8 = 512 字节
    *                 3---  AT24C04 卡容量: 04 * 1024/8 = 1024 字节
    *                 4---  AT24C08 卡容量: 08 * 1024/8 = 2024 字节
    *                 5---  AT24C16 卡容量: 16 * 1024/8 = 4096 字节
    *                 11---  AT24C32 卡容量: 32 * 1024/8 = 8192 字节
    *                 6---  AT24C64 卡容量: 64 * 1024/8 = 16384 字节
    *                 7---  AT24C128 卡容量: 128 * 1024/8 = 32768 字节
    *                 8---  AT24C256 卡容量: 256 * 1024/8 = 65536 字节
    *               offset: 偏移地址
    *               length: 数据长度,与偏移地址相加，不能超过卡片类型本身的容量
    *
    * Output:		data:   数据缓冲区
    * Return:		>=0	正确;	<0	错误	
    * Others:		AT24CXX卡（XX为01A、02、04、08、16、32、64、128、256）是XXKb位的非加密存储器卡，只存在读、写两种操作。

    */
    int STDCALL mwRead24CXX(HANDLE icdev, int cardType, int offset, int length, unsigned char data[]);

    /**
    * Function:	mwWrite24CXX
    * Description:	写24CXX系列卡片
    * Input:		cardType:
    *                 1---  AT24C01A 卡容量: 01 * 1024/8 = 256 字节
    *                 2---  AT24C02 卡容量: 02 * 1024/8 = 512 字节
    *                 3---  AT24C04 卡容量: 04 * 1024/8 = 1024 字节
    *                 4---  AT24C08 卡容量: 08 * 1024/8 = 2024 字节
    *                 5---  AT24C16 卡容量: 16 * 1024/8 = 4096 字节
    *                 11---  AT24C32 卡容量: 32 * 1024/8 = 8192 字节
    *                 6---  AT24C64 卡容量: 64 * 1024/8 = 16384 字节
    *                 7---  AT24C128 卡容量: 128 * 1024/8 = 32768 字节
    *                 8---  AT24C256 卡容量: 256 * 1024/8 = 65536 字节
    *               offset: 偏移地址
    *               length: 数据长度,与偏移地址相加，不能超过卡片类型本身的容量
    *
    *               data:   数据缓冲区
    * Output:		NULL
    * Return:		>=0	正确;	<0	错误	
    * Others:		AT24CXX卡（XX为01A、02、04、08、16、32、64、128、256）是XXKb位的非加密存储器卡，只存在读、写两种操作。
    */
    int STDCALL mwWrite24CXX(HANDLE icdev, int cardType, int offset, int length, const unsigned char data[]);


    /**
    * Function: mwRead102
    * Description:  通用读卡操作，按照卡内的绝对地址来寻址。
    * Input:        icdev: 打开的设备句柄
    *               offset: 起始偏移地址，最大为0x00B2
    *               length: 读取的字节数，与偏移地址相加，不能超过0x00B2
    *                
    * Output:       data:  读取到的数据
    * Return:       >=0 正确; <0  错误  
    * Others:       
    */
    int STDCALL mwRead102(HANDLE icdev, int offset, int length, unsigned char data[]);

    /**
    * Function: mwWrite102
    * Description:  通用写卡操作，按照卡内的绝对地址来寻址。
    * Input:        icdev: 打开的设备句柄
    *               offset: 起始偏移地址，最大为0x00B2
    *               length: 写入的字节数，与偏移地址相加，不能超过0x00B2
    *               data:   要写入的数据
    *
    * Output:       NULL
    * Return:       >=0 正确; <0  错误  
    * Others:       
    */
    int STDCALL mwWrite102(HANDLE icdev, int offset, int length, const unsigned char data[]);

    /**
    * Function: mwErase102
    * Description:  通用擦除操作，按照卡内的绝对地址来寻址。
    * Input:        icdev: 打开的设备句柄
    *               offset: 起始偏移地址，最大为0x00B2
    *               length: 擦除的字节数，与偏移地址相加，不能超过0x00B2
    *
    * Output:       NULL
    * Return:       >=0 正确; <0  错误  
    * Others:       
    */
    int STDCALL mwErase102(HANDLE icdev, int offset, int length);

    /**
    * Function: mwReadPassword102
    * Description:  读密码
    * Input:        icdev: 打开的设备句柄
    *               type:   0x00 - 主密码,长度为2字节
    *                       0x01 - 应用区1密码,长度为6字节
    *                       0x02 - 应用区2密码,长度为4字节
    *
    * Output:       password: 读取到的密码
    * Return:       >=0 正确; <0  错误  
    * Others:       
    */
    int STDCALL mwReadPassword102(HANDLE icdev, int type, unsigned char password[]);

    /**
    * Function: mwVerifyPassword102
    * Description:  校验密码
    * Input:        icdev: 打开的设备句柄
    *               type:   0x00 - 主密码,长度为2字节
    *                       0x01 - 应用区1密码,长度为6字节
    *                       0x02 - 应用区2密码,长度为4字节
    *               password: 卡片密码
    *
    * Output:       NULL
    * Return:       >=0 正确; <0  错误  
    * Others:       
    */
    int STDCALL mwVerifyPassword102(HANDLE icdev, int type, const unsigned char password[]);

    /**
    * Function: mwChangePassword102
    * Description:  修改密码
    * Input:        icdev: 打开的设备句柄
    *               type:   0x00 - 主密码,长度为2字节
    *                       0x01 - 应用区1密码,长度为6字节
    *                       0x02 - 应用区2密码,长度为4字节
    *               password: 卡片密码
    *
    * Output:       NULL
    * Return:       >=0 正确; <0  错误  
    * Others:       
    */
    int STDCALL mwChangePassword102(HANDLE icdev, int type, const unsigned char password[]);

    /**
    * Function: mwReadEraseCount102
    * Description:  读应用区2的擦除计数，卡片个人化之前该计数不起作用。
    * Input:        icdev: 打开的设备句柄
    *
    * Output:       count: 擦除计数
    * Return:       >=0 正确; <0  错误  
    * Others:       
    */
    int STDCALL mwReadEraseCount102(HANDLE icdev, int *count);

    /**
    * Function: mwReadErrorCount102
    * Description:  读密码错误计数，初始值为4，用户密码核对出错1次，则计数器值减1
    *               ，连续4次出错，卡片会自动锁死；如果其中对1次，则恢复为4
    * Input:        icdev: 打开的设备句柄
    *
    * Output:       count: 密码错误计数
    * Return:       >=0 正确; <0  错误  
    * Others:       
    */
    int STDCALL mwReadErrorCount102(HANDLE icdev, int *count);

    /**
    * Function: mwReadPartition102
    * Description:  按分区来读102卡，地址0为各扇区的起始地址
    * Input:        icdev: 打开的设备句柄
    *               sector:  0x00 - 厂商代码区，共2字节，本区域一般情况下已固化，只可读；
    *                        0x01 - 发行商代码区，共8字节；
    *                        0x02 - 代码保护区，共8字节；
    *                        0x03 - 应用区1，共64字节；
    *                        0x04 - 应用区2，共64字节；
    *                        0x05 - 测试区，共2字节

    *               offset: 起始偏移的字节地址，从0开始。
    *               length: 要读的字节数，与偏移地址相加，不能超过该分区的总长度
    *
    * Output:       data: 读取到的分区数据
    * Return:       >=0 正确; <0  错误  
    * Others:       例如：读应用区1中10-19共10个字节,sector = 0x03,offset = 0x09, legth = 10
    */
    int STDCALL mwReadPartition102(HANDLE icdev, int sector, int offset, int length, unsigned char data[]);

    /**
    * Function: mwWritePartition102
    * Description:  按分区来写102卡，地址0为各扇区的起始地址
    * Input:        icdev: 打开的设备句柄
    *               sector:  0x00 - 厂商代码区，共2字节，本区域一般情况下已固化，只可读；
    *                        0x01 - 发行商代码区，共8字节；
    *                        0x02 - 代码保护区，共8字节；
    *                        0x03 - 应用区1，共64字节；
    *                        0x04 - 应用区2，共64字节；
    *                        0x05 - 测试区，共2字节

    *               offset: 起始偏移的字节地址，从0开始。
    *               length: 要写的字节数，与偏移地址相加，不能超过该分区的总长度
    *               data:   要写入的数据
    *
    * Output:       NULL
    * Return:       >=0 正确; <0  错误  
    * Others:       例如：写应用区2中20-29共10个字节,sector = 0x04,offset = 19, legth = 10
    */
    int STDCALL mwWritePartition102(HANDLE icdev, int sector, int offset, int length, const unsigned char data[]);

    /**
    * Function: mwSimulationPersonalization102
    * Description:  模拟熔断操作，通过FUSE引脚控制，将卡虚拟成Level 2模式，当取消模拟时，恢复Level 1模式。
    * Input:        icdev: 打开的设备句柄
    *               flag:   0x00 - 取消模拟
    *                       0x01 - 模拟个人化
    *
    * Output:       NULL
    * Return:       >=0 正确; <0  错误  
    * Others:       
    */
    int STDCALL mwSimulationPersonalization102(HANDLE icdev, int flag);

    /**
    * Function: mwPersonalization102
    * Description:  个人化,此操作不可逆，需慎重。执行此指令前需先验证主密码
    * Input:        icdev: 打开的设备句柄
    *               
    * Output:       NULL
    * Return:       >=0 正确; <0  错误  
    * Others:       
    */
    int STDCALL mwPersonalization102(HANDLE icdev);

    /**
    * Function: mwInitReadControl102
    * Description:  将应用区的读保护位设置为0，设置后，需要验证主密码才可读应用区。
    * Input:        icdev: 打开的设备句柄
    *               sector: 0x01 - 用户区1
    *                       0x02 - 用户区2
    *
    * Output:       NULL
    * Return:       >=0 正确; <0  错误  
    * Others:       
    */
    int STDCALL mwInitReadControl102(HANDLE icdev, int sector);

    /**
    * Function: mwInitWriteControl102
    * Description:  将应用区的写保护位设置为0，设置后，Level 2模式下应用区不可写。
    * Input:        icdev: 打开的设备句柄
    *               sector: 0x01 - 用户区1
    *                       0x02 - 用户区2
    *
    * Output:       NULL
    * Return:       >=0 正确; <0  错误  
    * Others:       
    */
    int STDCALL mwInitWriteControl102(HANDLE icdev, int sector);

//=======================================工具函数====================================================

    /*
    * Function:	mwEntrdes	
    * Description:	DES/3DES 加密、解密		
    * Input:     flag   00  DES  解密
    *                   01  DES  加密
    *                   10  3DES 解密
    *                   11  3DES 加密
    *
    *           key:	密码，格式为二进制。
    *           keyLen: 密码长度，DES加密/解密为8，3DES为16或24
    *           ptrsource: 原文
    *           msglen: 原文长度必需为8的整数倍
    *
    * Output:   ptrdest: 密文	
    * Return:	>=0	正确;	<0	错误	
    * Others:   3DES加密过程为：C=Ek3(Dk2(Ek1(P))) 
    *           3DES解密过程为：P=Dk1((EK2(Dk3(C)))
    *           keyLen = 16: Byte0-Byte7 表示设置第一组密钥, Byte8-Byte15第二组密钥
    *           keyLen = 24: Byte0-Byte7 表示设置第一组密钥, Byte8-Byte15第二组密钥, Byte16-Byte23 第三组密钥
    */
    int STDCALL mwEntrdes(int flag, unsigned char key[],  int keyLen,  unsigned char ptrsource[], int msglen , unsigned char ptrdest[]);
    
    /*
    * Function:	mwEntrdes_HEX	
    * Description:	DES/3DES 加密、解密		
    * Input:     flag   00  DES  解密
    *                   01  DES  加密
    *                   10  3DES 解密
    *                   11  3DES 加密
    *
    *           key:	密码，格式为16进制字符串
    *           keyLen: 密码长度，DES加密/解密为16，3DES为32或48
    *           ptrsource: 原文，格式为16进制字符串
    * Output:   ptrdest: 密文，格式为16进制字符串	
    * Return:	>=0	正确;	<0	错误	
    * Others:   3DES加密过程为：C=Ek3(Dk2(Ek1(P))) 
    *           3DES解密过程为：P=Dk1((EK2(Dk3(C)))
    *           keyLen = 32: Byte0-Byte15 表示设置第一组密钥, Byte16-Byte31第二组密钥
    *           keyLen = 48: Byte0-Byte15 表示设置第一组密钥, Byte16-Byte31第二组密钥, Byte32-Byte47 第三组密钥
    */
    int STDCALL mwEntrdes_HEX(int  flag, const char *key, const char *ptrsource,  char * ptrdest);
    
    int STDCALL mwCalMac(const unsigned char initdata[], const unsigned char pin[], int PinLen, const unsigned char src[], int srcLen, unsigned char mac[]);

    int STDCALL mwCalMac_HEX(const char *strInitData, const char *strPin, const char *strSrc, char *strMac);

    /**
    * Function:	BinToHex
    * Description:	将二进制数据转化为16进制字符串。
    *               例如：输入数据为0X3a，则转化后的数据为0x33,0x41,即字符串"3A"
    * Input:		src: 要被转换的数据
    *               srcLen: src长度
    * Output:		dst: 保存转换后的16进制字符串，该存储空间至少是 srcLen*2+1 个字节的长度。
    * Return:		转换后的字符串长度
    * Others: 
    */
    unsigned int STDCALL BinToHex(const unsigned char src[],  char *dst, int srcLen);


    /**
    * Function:	HexToBin
    * Description:	将16进制字符串转化为二进制数据。
    *               例如：输入数据为"32"，则转化后的数据为0x32
    * Input:		src:	要被转换的16进制字符串
    *               srcLen: src长度,srcLen为0取字符串实际长度
    * Output:		dst:	保存转换后的byte数组。
    * Return:		转换后的字节长度
    * Others:		函数具有较强的容错性，它将忽略16进制字符串中的所有非法字符
    */
    unsigned int STDCALL HexToBin(const  char *src, unsigned char dst[], int srcLen);

    /**
    * Function:	getErrDescription
    * Description:	获取错误描述信息
    * Input:		errcode:    动态库返回的错误代码
    *               languageCode: 错误描述的语言, 0-GB2312 1-ENGLISH
    * Output:		message:	错误信息。
    * Return:		信息长度,如果返回值小于0表示错误，请查看错误代码表
    * Others:		
    */
    void STDCALL getErrDescription(int errcode, int languageCode, char* message);

//=======================================密码键盘/LCD/语音/磁条卡，R6/F1系列不支持此处的接口===============================
    /**
    * Function:	    mwKeyPadDownLoadMasterKeyAsc
    * Description:	下载主密钥到键盘
    * Input:		MKeyNo-     主密钥号（0x00-0x02）
    *               KeyLen -    密钥长度
    *               MasterKey-  主密钥， 字节数组
    *                           DES-长度为8
    *                           3DES- 长度为16/24
    * Output:		NULL             
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwKeyPadDownLoadMasterKeyAsc(HANDLE icdev, int MKeyNo, int KeyLen, const unsigned char MasterKey[]);

    /**
    * Function:	    mwKeyPadDownLoadMasterKey
    * Description:	下载主密钥到键盘
    * Input:		MKeyNo-     主密钥号（0x00-0x02）
    *               MasterKey-  主密钥，16进制字符串格式
    *                           DES-长度为16
    *                           3DES- 长度为32/48
    * Output:		NULL             
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwKeyPadDownLoadMasterKey(HANDLE icdev, int MKeyNo,const char *MasterKey);

    /**
    * Function:	    mwKeyPadDownLoadWorkkeyAsc
    * Description:	下载工作密钥到键盘
    * Input:		
    *               WKeyNo-     工作密钥号（0x00-0x02）
    *               KeyLen -    密钥长度
    *               Workkey-    工作密钥， 字节数组
    *                           DES-长度为 8
    *                           3DES- 长度为 16/24
    * Output:		NULL             
    * Return:		>=0	正确;	<0	错误	
    * Others:		工作密钥应该是用主密钥加密后的密文数据，当激活时通过指定的密钥组，设备会进行解密得到真正的密钥
    */
    int STDCALL mwKeyPadDownLoadWorkKeyAsc(HANDLE icdev, int WKeyNo, int KeyLen, const unsigned char Workkey[]);//下载工作密钥16/32/48

    /**
    * Function:	    mwKeyPadDownLoadWorkkey
    * Description:	下载工作密钥到键盘
    * Input:		
    *               WKeyNo-     工作密钥号（0x00-0x02）
    *               Workkey-    工作密钥，16进制字符串格式
    *                           DES-长度为16
    *                           3DES- 长度为32/48
    * Output:		NULL             
    * Return:		>=0	正确;	<0	错误	
    * Others:		工作密钥应该是用主密钥加密后的密文数据，当激活时通过指定的密钥组，设备会进行解密得到真正的密钥
    */
    int STDCALL mwKeyPadDownLoadWorkKey(HANDLE icdev, int WKeyNo, const char *Workkey);//下载工作密钥16/32/48
    
    /**
    * Function:	    mwKeyPadActiveKey
    * Description:	激活工作密钥
    * Input:		WKeyNo工作密钥号密钥号（0x00-0x02）
    * Output:		NULL             
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwKeyPadActiveKey(HANDLE icdev, int MKeyNo, int WKeyNo);

    /**
    * Function:	    mwPassGetInput
    * Description:	获得用户键盘密码的输入,该函数会一直等待用户输入直到超时	
    * Input:		ctime 等待用户按键输入的超时时间，以second为单位；最大255s，超过该时间退出. 如果为0 则表示使用设备默认超时。            
    *               cmd 语音提示, 
    *                             0x00-不提示, 关闭密码键盘,其他参数可以填空
    *                             0x01-请输入密码,同时LCD显示提示信息
    *                             0x02-请重新输入密码,同时LCD显示提示信息
    *                             0x03-请输入旧密码,同时LCD显示提示信息
    *                             0x04-请输入新密码 ,同时LCD显示提示信息
    *                             0x05-密码修改成功,其他参数可以填空
    *               passwordLen     指定用户要输入的密码长度，当用户输入足够的长度密码键盘会直接返回。
    *                               如果为0，则表示等待用户确认键.
    *               cardno 卡号， 参见ANSI X9.8 标准
    * Output:		cpass 输入的密码，返回的经过工作密钥加密后的数据(16进制字符串格式)， 加密前的数据按照ANSIX9.8标准组装             
    * Return:		密码位数（根据客户输入而定）cpass就是密码，<0	错误	
    * Others:		
    * (1) ANSI X9.8 Format（不带主账号信息）
    * PIN（个人识别码 Personal Identity Number）总共有8个byte长度，分为两个部分;（类似数据包的格式）
    * 1：Byte1 记录PIN的长度
    * 2：Byte2-Byte8 6-12位（字符）PIN(每个字符占4个BIT，不足8位右补F)
    * 例如：明文PIN为 123456，
    * 则PIN BLOCK为 0x06 0x12 0x34 0x56 0xFF 0xFF 0xFF 0xFF
    * 0x06记录了PIN的长度为6，后边不足16位均以F补齐，然后转换为BCD码（BCD码为8位二进制数为一个单元，也就是一个Byte的大小也是一个十六进制数HEX的占用长度）。
    * 
    * (2) ANSI X9.8 Format（带主帐号信息）
    * PIN BLOCK 格式：等于 PIN 按位异或主帐号
    * PIN 格式：（与1中的格式类似）
    * Byte 1 PIN的长度
    * Byte 2 – Byte 3/4/5/6/7 4--12个PIN(每个PIN占4个BIT)
    * Byte4/5/6/7/8 – Byte 8 FILLER “F” (每个“F“占4个BIT)
    * 
    * PAN（主帐号 Primary Account Number）同样包含8个byte，格式如下：
    * Byte 1 — Byte 2 0x00 0x00
    * Byte 3 — Byte 8 12个主帐号字符（最后一位为校验位）
    * 12位字符主帐号的取法：取主帐号的右12位（不包括最右边的校验位），不足12位左补“0X00”。
    * 例子：
    * 
    * 明文 PIN：123456，
    * 主帐号 PAN：123456789012345678
    * 截取下的主帐号为：678901234567 （最后一位校验位8的前12位字符为截取的主帐号）
    * 
    * 则用于PIN加密的主帐号为：0x00 0x00 0x67 0x89 0x01 0x23 0x45 0x67
    * 则 PIN BLOCK （PIN按位异或主帐号PAN）
    * 
    * 即是为：  0x06 0x12 0x34 0x56 0xFF 0xFF 0xFF 0xFF
    * 异或上：  0x00 0x00 0x67 0x89 0x01 0x23 0x45 0x67
    * 结果为：  0x06 0x12 0x53 0xDF 0xFE 0xDC 0xBA 0x98
    */
    int STDCALL mwPassGetInput(HANDLE icdev, int ctime, int cmd, int passwordLen, const char *cardno, char *cpass);

    /**
    * Function:	    mwPassGetInputExt
    * Description:	获得用户键盘密码的输入,该函数会一直等待用户输入直到超时	
    * Input:		ctime 等待用户按键输入的超时时间，以second为单位；最大255s，超过该时间退出. 如果为0 则表示使用设备默认超时。            
    *               cmd 语音提示, 
    *                             0x00-不提示, 关闭密码键盘,其他参数可以填空
    *                             0x01-请输入密码,同时LCD显示提示信息
    *                             0x02-请重新输入密码,同时LCD显示提示信息
    *                             0x03-请输入旧密码,同时LCD显示提示信息
    *                             0x04-请输入新密码 ,同时LCD显示提示信息
    *                             0x05-密码修改成功,其他参数可以填空
    *               passwordLen     指定用户要输入的密码长度，当用户输入足够的长度密码键盘会直接返回。
    *                               如果为0，则表示等待用户确认键.
    * Output:		cpass 输入的密码(明文ASCII 字符)，             
    * Return:		密码位数（根据客户输入而定）cpass就是密码，<0	错误	
    * Others:		
    */
    int STDCALL mwPassGetInputExt(HANDLE icdev, int ctime, int cmd, int passwordLen, char *cpass);


    /**
    * Function:	    mwPassIn
    * Description:	进入获取键盘密码的状态,进入该状态后只接收 mwPassGet 和 mwPassCancel 命令.	
    * Input:		icdev 通讯设备标识符
    *               ctime 等待用户按键输入的超时时间，以second为单位；最大255s，最小1s；超过该时间退出.
    *               cmd 语音提示, 
    *                             0x01-请输入密码,同时LCD显示提示信息
    *                             0x02-请重新输入密码,同时LCD显示提示信息
    *                             0x03-请输入旧密码,同时LCD显示提示信息
    *                             0x04-请输入新密码 ,同时LCD显示提示信息
    *               cardno 卡号， 参见ANSI X9.8 标准, see mwPassGetInput()
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwPassIn(HANDLE icdev, int ctime, int cmd, const char *cardno);

    /**
    * Function:	    mwPassGet
    * Description:	查询和获取输入的密码		
    * Input:		icdev 通讯设备标识符
    * Output:		cpass 输入的密码，返回的经过工作密钥加密后的数据(16进制字符串格式)， 加密前的数据按照ANSIX9.8标准组装    
    * Return:		0x00 - 成功取得密码，cpass 为加密后的密文密码,rlen 为加密后的密文密码长度
    *               -0X0031 - 用户取消密码输入
    *               -0X0032 - 用户密码输入操作超时
    *               -0X0033 - 未处于密码输入状态
    *               -0X0034 - 用户输入密码还未完成，返回按键个数、*号串
    *           注意：-0X0034 这个返回值很重要,在开始查询中会一直遇到,表示输入还没有完成,可以再次执行mwPassGet函数来获取密码
    *	
    * Others:		
    */
    int STDCALL mwPassGet(HANDLE icdev,  char *cpass);

    /**
    * Function:	    mwPassCancel
    * Description:	取消键盘密码的状态,执行后设备恢复普通状态		
    * Input:		icdev 通讯设备标识符
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwPassCancel(HANDLE icdev);

    /**
    * Function:	    mwLcdDispInfo
    * Description:	显示提示信息			
    * Input:		line    行号 范围为1~4
    *               offset  偏移 范围为1-16
    *               data    以空标志结束的字符串。
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		这里所说的'字'表示的是一个汉字或一个字符
    *               全部是汉字则每行可以显示8个GB2312编码的字符，仅仅是ANSI字符则每行可以显示16个。示例如下
    *               mwLcdDispInfo(icdev,1,1,"深圳明华澳汉公司");    //OK
    *               mwLcdDispInfo(icdev,1,1,"0123456789ABCDEF");    //OK
    *               mwLcdDispInfo(icdev,1,1,"深圳明华89ABCDEF");    //OK
    *               mwLcdDispInfo(icdev,1,1,"深圳市明华澳汉公司");   //ERROR                   
    *               mwLcdDispInfo(icdev,1,2,"0123456789ABCDEF");    //ERROR
    *               mwLcdDispInfo(icdev,1,2,"深圳明华89ABCDEF");    //ERROR
    */
    int STDCALL mwLcdDispInfo(HANDLE icdev, int line, int offset, const char *data);

    /**
    * Function:	    mwLcdDispFixedInfo
    * Description:	根据flag显示不同的提示信息			
    * Input:		line    行号 范围为1~4
    *               offset  偏移 范围为1-16
    *               flag 范围为0~9	，默认显示 主界面(明华LOGO)
    *				0x00: 显示主界面(明华LOGO)
    *				0x01: "请插上卡！"
    *				0x02: "请插下卡！"
    *				0x03: "请刷卡！"
    *				0x04: "读卡错误！"
    *				0x05: "请输入密码！"
    *				0x06: "密码错误！"
    *				0x07: "操作成功！"
    *				0x08: "操作失败！"
    *				0x09: "操作超时！"
    *               0x0a: "请重新输入密码"
    *               0x0b: "请输入旧密码"
    *               0x0c: "请输入新密码"
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwLcdDispFixedInfo(HANDLE icdev, int line, int offset, int flag);

    /**
    * Function:	mwLcdClear
    * Description:	清除LCD屏幕		
    * Input:		line 要清除的行号
    *                   0 清除全部
    *                   1 清除第一行
    *                   2 清除第二行
    *                   3 清除第三行
    *                   4 清除第四行
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwLcdClear(HANDLE icdev, int line);

    /**
    * Function:	mwLcdCtlBackLight
    * Description:	控制LCD的背光显示，可以关闭或打开背光		
    * Input:		flag 
    *               0 关背光
    *               1 开背光
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwLcdCtlBackLight(HANDLE icdev, int flag);

    /**
    * Function:	    mwVoiceControl
    * Description:	语音控制	
    * Input:		icdev 通讯设备标识符
    *               语音提示, 
    *                             0x00-不提示
    *                             0x01-请输入密码
    *                             0x02-请重新输入密码
    *                             0x03-请输入原密码
    *                             0x04-密码修改成功
    *                             0x05-请输入新密码
    * Output:		无
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwVoiceControl(HANDLE icdev, int cmd);

    /**
    * Function:	mwReadMagCard
    * Description:	读取磁条卡数据		
    * Input:		ctime 等待用户刷卡超时时间，以second为单位；最大255s，最小1s；超过该时间退出.
    * Output:		pMagCardData 存储磁条卡数据,格式如下
    *               <TRACK1>data</TRACK1><TRACK2>data</TRACK2><TRACK3>data</TRACK3>
    * Return:		>=0	正确;	<0	错误	
    * Others:		
    */
    int STDCALL mwReadMagCard( HANDLE icdev, int ctime, char *pMagCardData);

    //外接密码键盘操作
    int STDCALL mwKeyBGetInput(HANDLE icdev, int ctime, int cmd, int passwordLen, const char *cardno, char *cpass);
    int STDCALL mwKeyBGetInputExt(HANDLE icdev, int ctime, int cmd, int passwordLen, char *cpass);
    int STDCALL mwKeyBIn(HANDLE icdev, int ctime, int cmd, const char *cardno);
    int STDCALL mwKeyBGet(HANDLE icdev,  char *cpass);
    int STDCALL mwKeyBCancel(HANDLE icdev);
    //=======================================X9身份证===============================
    int STDCALL mwIDCARDReadSamA(HANDLE icdev, char samANumber[]);   //读SamA模块编号，返回读取到的长度，小于0表示失败
    int STDCALL mwIDCARDRequest(HANDLE icdev);  //第一步寻卡，小于0表示失败
    int STDCALL mwIDCARDSelect(HANDLE icdev);   //第二步选择卡片，小于0表示失败
    int STDCALL mwIDCARDRead(HANDLE icdev); //第三步读文字信息以及照片信息，该接口执行成功后才能查询信息，小于0表示失败
    int STDCALL mwIDCARDReadAll(HANDLE icdev); //读文字信息、照片信息、指纹信息，小于0表示失败
    int STDCALL mwIDCARDReadAppendMsg(HANDLE icdev); //读取追加地址信息，小于0表示失败
    /**
    * Function:	    mwIDCardQueryName
    * Description:	获得身份证姓名		
    * Input:		无
    * Output:		无
    * Return:		姓名
    * Others:		
    */
    const char* STDCALL mwIDCARDQueryName();

	/**
    * Function:	    mwIDCardQuerySex
    * Description:	获得身份证性别		
    * Input:		无
    * Output:		无
    * Return:		性别
    * Others:		
    */
    const char* STDCALL mwIDCARDQuerySex();

	/**
    * Function:	    mwIDCardQueryNation
    * Description:	获得身份证民族		
    * Input:		无
    * Output:		无
    * Return:		民族
    * Others:		
    */
    const char* STDCALL mwIDCARDQueryNation();

	/**
    * Function:	    mwIDCardQueryBirth
    * Description:	获得身份证出生日期		
    * Input:		无
    * Output:		无
    * Return:		出生日期
    * Others:		
    */
    const char* STDCALL mwIDCARDQueryBirth();

	/**
    * Function:	    mwIDCardQueryAddress
    * Description:	获得身份证地址		
    * Input:		无
    * Output:		无
    * Return:		地址
    * Others:		
    */
    const char* STDCALL mwIDCARDQueryAddress();

	/**
    * Function:	    mwIDCardQueryNumber
    * Description:	获得身份证号码		
    * Input:		无
    * Output:		无
    * Return:		身份证号码
    * Others:		
    */
    const char* STDCALL mwIDCARDQueryNumber();

	/**
    * Function:	    mwIDCardQueryDepartment
    * Description:	获得身份证签发机关		
    * Input:		无
    * Output:		无
    * Return:		签发机关
    * Others:		
    */
    const char* STDCALL mwIDCARDQueryDepartment();

	/**
    * Function:	    mwIDCardQueryExpireDay
    * Description:	获得身份证有效日期		
    * Input:		无
    * Output:		无
    * Return:		身份证有效日期
    * Others:		
    */
    const char* STDCALL mwIDCARDQueryExpireDay();

    /**
    * Function:	    mwIDCardQueryPhotoFile
    * Description:	获得指纹信息	
    * Input:		fileName:需要存放的文件路径及名称
    * Output:		无
    * Return:		=0	正确;	其它  错误	
    * Others:		
    */
    int STDCALL mwIDCARDQueryFingerprintFile(char* fileName);

	/**
    * Function:	    mwIDCardQueryPhotoFile
    * Description:	获得身份证照片		
    * Input:		fileName:需要存放的文件路径及名称
    * Output:		无
    * Return:		=0	正确;	其它  错误	
    * Others:		
    */
    int STDCALL mwIDCARDQueryPhotoFile(char* fileName);
    //=======================================X5身份证，R6/F1系列不支持此处的接口===============================/**
    /**
    * Function:	    mwIDCardOpen
    * Description:	打开身份证检测阅读器		
    * Input:		无
    * Output:		无
    * Return:		=0	正确;	其它  错误	
    * Others:		
    */
    int STDCALL mwIDCardOpen();

	/**
    * Function:	    mwIDCardClose
    * Description:	关闭身份证检测阅读器		
    * Input:		无
    * Output:		无
    * Return:		=0	正确;	其它  错误	
    * Others:		
    */
    int STDCALL mwIDCardClose();

	/**
    * Function:	    mwIDCardRead
    * Description:	读取身份证二代证		
    * Input:		无
    * Output:		无
    * Return:		=0	正确;	其它  错误	
    * Others:		
    */
    int STDCALL mwIDCardRead();

	/**
    * Function:	    mwIDCardQueryName
    * Description:	获得身份证姓名		
    * Input:		无
    * Output:		无
    * Return:		姓名
    * Others:		
    */
    const char* STDCALL mwIDCardQueryName();

	/**
    * Function:	    mwIDCardQuerySex
    * Description:	获得身份证性别		
    * Input:		无
    * Output:		无
    * Return:		性别
    * Others:		
    */
    const char* STDCALL mwIDCardQuerySex();

	/**
    * Function:	    mwIDCardQueryNation
    * Description:	获得身份证民族		
    * Input:		无
    * Output:		无
    * Return:		民族
    * Others:		
    */
    const char* STDCALL mwIDCardQueryNation();

	/**
    * Function:	    mwIDCardQueryBirth
    * Description:	获得身份证出生日期		
    * Input:		无
    * Output:		无
    * Return:		出生日期
    * Others:		
    */
    const char* STDCALL mwIDCardQueryBirth();

	/**
    * Function:	    mwIDCardQueryAddress
    * Description:	获得身份证地址		
    * Input:		无
    * Output:		无
    * Return:		地址
    * Others:		
    */
    const char* STDCALL mwIDCardQueryAddress();

	/**
    * Function:	    mwIDCardQueryNumber
    * Description:	获得身份证号码		
    * Input:		无
    * Output:		无
    * Return:		身份证号码
    * Others:		
    */
    const char* STDCALL mwIDCardQueryNumber();

	/**
    * Function:	    mwIDCardQueryDepartment
    * Description:	获得身份证签发机关		
    * Input:		无
    * Output:		无
    * Return:		签发机关
    * Others:		
    */
    const char* STDCALL mwIDCardQueryDepartment();

	/**
    * Function:	    mwIDCardQueryExpireDay
    * Description:	获得身份证有效日期		
    * Input:		无
    * Output:		无
    * Return:		身份证有效日期
    * Others:		
    */
    const char* STDCALL mwIDCardQueryExpireDay();

	/**
    * Function:	    mwIDCardQueryPhotoFile
    * Description:	获得身份证照片		
    * Input:		fileName:需要存放的文件路径及名称
    * Output:		无
    * Return:		身份证照片
    * Others:		
    */
    int STDCALL mwIDCardQueryPhotoFile(char* fileName);

	/**
    * Function:	    mwIDCardClearData
    * Description:	清除所读取的身份证数据		
    * Input:		无
    * Output:		无
    * Return:		=0	正确;	其它  错误
    * Others:		
    */
    int STDCALL mwIDCardClearData();

	/**
    * Function:	    mwIDCardGetErrorText
    * Description:	操作错误后，获取具体的错误描述。		
    * Input:		无
    * Output:		无
    * Return:		错误描述数据
    * Others:		
    */    
    const char * STDCALL mwIDCardGetErrorText();


    //=====================1608==================================
    /************************************************************************/
    /*读取用户区数据
    函数说明：本函数从当前用户工作区读取指定的数据。工作的数据区由选择工作区命令设置。
    参数说明：ByteAddr	操作数据的起始地址，对于AT88SC1608卡该参数的取值范围为：0----255。
    Length	要读取的数据长度，对于AT88SC1608卡该参数的取值范围为：1---256。另外ByteAddr和Length的和不能大于卡的实际容量，否则读写器会拒绝执行命令，并返回错误信息。
    Data_Buff	数据缓冲区。为读取的数据事先分配的缓冲区指针。在调用该函数以前必须确认已经为该指针指向的缓冲区分配了足够的内存空间。缓冲区的大小要不小于实际读取数据的长度（Length参数）。
    返回信息：返回0表示成功，Data_Buff指向的缓冲区存储读回的数据。返回其他信息表示在操作过程中有错误发生，具体的错误列表见本说明的第五部分。
    */
    /************************************************************************/
    int STDCALL mwReadUserZone1608(HANDLE icdev,  int ByteAddr, int Length,char *Data_Buff);

    /************************************************************************/
    /*写用户数据区
    函数说明：向当前用户区写入数据，用户工作区由选择用户工作区函数设置。
    参数说明：ByteAddr	操作数据的起始地址，对于AT88SC1608卡该参数的取值范围为：0---255。
    Length	要写入的数据长度，对于AT88SC1608卡该参数的取值范围为：1---256。另外ByteAddr和Length的和不能大于卡的实际容量，否则读写器会拒绝执行命令，并返回错误信息。
    Data_Buff	数据缓冲区。要写入数据的缓冲区指针。将要写入的数据放入该缓冲区。注意缓冲区的大小要不小于Length参数。如果小于则可能写入未知的数据，也可能引发其他的未知错误。
    返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生，具体的错误列表见本说明的第五部分。
    */
    /************************************************************************/
    int STDCALL mwWriteUserZone1608( HANDLE icdev, int ByteAddr, int Length,char *Data_Buff);

    /************************************************************************/
    /*读取配置区数据
    函数说明：本函数从卡功能配置区读取指定的数据。
    参数说明：ByteAddr	操作数据的起始地址，对于AT88SC1608卡该参数的取值范围为：0----127。
    Length	要读取的数据长度，对于AT88SC1608卡该参数的取值范围为：1---128。另外ByteAddr和Length的和不能大于卡的实际容量，否则读写器会拒绝执行命令，并返回错误信息。
    Data_Buff	数据缓冲区。为读取的数据事先分配的缓冲区指针。在调用该函数以前必须确认已经为该指针指向的缓冲区分配了足够的内存空间。缓冲区的大小要不小于实际读取数据的长度（Length参数）。
    返回信息：返回0表示成功，Data_Buff指向的缓冲区存储读回的数据。返回其他信息表示在操作过程中有错误发生，具体的错误列表见本说明的第五部分。
    */
    /************************************************************************/
    int STDCALL mwReadConfigZone1608( HANDLE icdev, int ByteAddr, int Length,char *Data_Buff);

    /************************************************************************/
    /*写卡功能配置区
    函数说明：本函数向卡功能配置区写入指定的数据。
    参数说明：ByteAddr	操作数据的起始地址，对于AT88SC1608卡该参数的取值范围为：0----127。
    Length	要写入的数据长度，对于AT88SC1608卡该参数的取值范围为：1---128。另外ByteAddr和Length的和不能大于卡的实际容量，否则读写器会拒绝执行命令，并返回错误信息。
    Data_Buff	数据缓冲区。为写入的数据事先分配的缓冲区指针。在调用该函数以前必须确认已经为该指针指向的缓冲区分配了足够的内存空间。缓冲区的大小要不小于实际读取数据的长度（Length参数）。
    返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生，具体的错误列表见本说明的第五部分。
    */
    /************************************************************************/
    int STDCALL mwWriteConfigZone1608( HANDLE icdev, int ByteAddr, int Length,char *Data_Buff);

    /************************************************************************/
    /*读AT88SC1608卡的熔断标记
    函数说明：该函数读取AT88SC1608卡的熔断标记。AT88SC1608卡具有三级熔断设置。
             分别是：FAB，CMA，PER卡片出厂的时候一般做了FAB级熔断。卡片生产厂商和卡片发行商可以做进一步的熔断。
             熔断标记由三个BIT表示，每做一级熔断标记中就有一位被置0。
    参数说明：Data_Buff	读出熔断标记的缓冲区指针。在调用该函数之前要事先给Data_Buff分配足够的内存空间，函数返回后Data_Buff中存放实际读出的熔断标记。标记的取值列表如下：
    07		卡片没有做任何熔断
    06		卡片做了FAB级熔断
    04		卡片做了CMA级熔断
    01卡片做了PER级熔断
    读出的熔断信息将作为调用写熔断函数的入口参数的条件使用。
    返回信息：返回0表示成功，Data_Buff中存放实际读出的熔断标记。返回其他信息表示在操作过程中有错误发生，具体的错误列表见本说明的第五部分。
    */
    /************************************************************************/
    int STDCALL mwReadFuse1608(HANDLE icdev, char *Data_Buff);

    /************************************************************************/
    /* 写AT88SC1608卡的熔丝
    函数说明：该函数更新AT88SC1608卡的熔断标记，执行该命令将自动将当前卡片进行下一级熔断。
    参数说明：无
    返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生，具体的错误列表见本说明的第五部分。
    */
    /************************************************************************/
    int STDCALL mwWriteFuse1608(HANDLE icdev );

    /************************************************************************/
    /*比较AT88SC1608卡的密码
    函数说明：AT88SC1608卡具有八组密码，每组密码有分为写密码和读密码，分别对卡的写和读操作进行保护。
             用户可以通过设置配置页中的ARx来为每个分区选择不同的密码组进行读写保护。对于系统功能配置区，固定使用第八套密码的写密码做安全保护。
             函数只执行密码比较操作不判断比较的正确与否。执行完本函数后要读取配置区中对应密码的错误记数器判断比较结果。
             如果比较正确则对应的错误记数器的值应该是“FF”。一个密码最多允许8次错误比较，如果8次连续的错误比较则该密码将被锁死。
    参数说明：	Pwd_Number			密码组的编号。
    “0”	第一组密码。
    “1”	第二组密码。
    “2”	第三组密码。
    “3”	第四组密码。
    “4”	第五组密码。
    “5”	第六组密码。
    “6”	第七组密码。
    “7”	第八组密码。
    Pwd_Flag			密码类型。
    0写密码。
    1读密码
    Pwd_Number	和Pwd_Flag共同确定要比较的密码。Pwd_Number=7，Pwd_Flag=0表示要比较的是第八组的写密码（卡片主密码）。
    Data_Buff	密码数据的缓冲区。调用函数前该缓冲区保存要比较的密码。
    返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生，具体的错误列表见本说明的第五部分。
    */
    /************************************************************************/
    int STDCALL mwCheckPwd1608( HANDLE icdev, int Pwd_Number, int Pwd_Flag,char *Data_Buff);

    /************************************************************************/
    /* 选择用户工作区
    函数说明：选择卡片当前的工作区号。AT88SC1608卡内部具有8个工作分区。
                同一时间只能有一个分区处于击活状态，对用户分区的读写都是在当前击活分区上进行的。
    参数说明：Zone_Num				用户工作区的编号
    0第一工作区
    1第二工作区
    2第三工作区
    3第四工作区
    4第五工作区
    5第六工作区
    6第七工作区
    7第八工作区
    返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生，具体的错误列表见本说明的第五部分。*/
    /************************************************************************/
    int STDCALL mwSelectZone1608(HANDLE icdev, char Zone_Num);

    /************************************************************************/
    /* 复位应答：
    u16 Card1608Reset(u8 *pValue)
    pValue  返回1608卡的应答信息，固定四字节  2C AA 55 A0*/
    /************************************************************************/
    int STDCALL mwReset1608(HANDLE icdev, unsigned char *pValue);  
    /************************************************************************/
    /* 密码错误计数读取：
    PwdNum   0-7 密码组的编号
    PwdFlag  0 写密码，1 读密码
    pValue  读取信息，1字节       */
    /************************************************************************/
    int STDCALL mwReadPAC1608(HANDLE icdev, unsigned char PwdNum, unsigned char PwdFlag, unsigned char *pValue);

    /************************************************************************/
    /* 用户区访问权限设置：
    u16  SI2C_WriteAccess1608(u8 ZoneNum,u8 *pValue )
    Zone    用户区 号，0-7
    *pValue  写信息，1字节*/
    /************************************************************************/
    int STDCALL mwWriteAccess1608(HANDLE icdev, unsigned char ZoneNum,unsigned char Value );

    /************************************************************************/
    /* 用户区访问权限读取：
    u16  SI2C_ReadAccess1608(u8 ZoneNum,u8 *pValue )
    Zone    用户区 号，0-7
    *pValue  读信息，1字节*/
    /************************************************************************/
    int STDCALL mwReadAccess1608(HANDLE icdev, unsigned char ZoneNum,unsigned char *pValue );


    /************************************************************************/
    /* 修改密码：
    u16 SI2C_ModifyPwd1608(u8 PwdNum,u8 PwdFlag,u8 *pValue)
    PwdNum    0 -7 密码组编号
    PwdFlag    0 写密码    1读密码
    *pValue    写密码  ，3字节*/
    /************************************************************************/
    int STDCALL mwModifyPwd1608(HANDLE icdev, unsigned char PwdNum, unsigned char PwdFlag, unsigned char *pValue );


/*
函数说明：读取AT88SC153卡分区数据（包括数据分区和配置分区）。每个分区有一个分区地址，其中0---2号分区为数据分区，3号分区为卡功能配置分区。
参数说明：PageAddr	分区地址。可以取值的范围是0---3，其中0---2号分区为数据分区，3号分区为卡功能配置分区。
ByteAddr	分区内数据偏移地址。要读取的数据的起始地址。对于AT88SC153卡该值的取值范围是0---63。另外ByteAddr和Length的和不能大于卡的存储分区实际容量，否则读写器会拒绝执行命令，并返回错误信息。
Length	要读取的数据长度，对AT88SC153卡该参数的取值范围为：1---64。另外ByteAddr和Length的和不能大于卡的存储页面实际容量，否则读写器会拒绝执行命令，并返回错误信息。
Data_Buff	数据缓冲区。为读出数据事先分配的缓冲区指针。在调用该函数以前必须确认已经为该指针指向的缓冲区分配了足够的内存空间。缓冲区的大小要不小于实际读取数据的长度（Length参数）。
返回信息：返回0表示成功，Data_Buff指向的缓冲区存储读回的数据。返回其他信息表示在操作过程中有错误发生.
*/
int STDCALL mwRead153(HANDLE icdev, int PageAddr, int ByteAddr, int Length, char *Data_Buff);

/*
函数说明：向AT88SC153卡的分区写入数据。
参数说明：PageAddr	分区地址。可以取值的范围是0---3，其中0---2号分区为数据分区，3号分区为卡功能配置分区。
ByteAddr	分区内数据偏移地址。要写入的数据的起始地址。对于AT88SC153卡该值的取值范围是0---63。另外ByteAddr和Length的和不能大于卡的存储分区实际容量，否则读写器会拒绝执行命令，并返回错误信息。
Length	要写入的数据长度，对AT88SC153卡该参数的取值范围为：1---64。另外ByteAddr和Length的和不能大于卡的存储页面实际容量，否则读写器会拒绝执行命令，并返回错误信息。
Data_Buff	数据缓冲区。为写入数据事先分配的缓冲区指针。在调用该函数以前必须确认已经为该指针指向的缓冲区分配了足够的内存空间。缓冲区的大小要不小于实际读取数据的长度（Length参数）。
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwWrite153(HANDLE icdev, int PageAddr, int ByteAddr, int Length, char *Data_Buff);

/*
函数说明：该函数读取AT88SC153卡的熔断标记。AT88SC153卡具有三级熔断设置。分别是：FAB，CMA，PER卡片出厂的时候一般做了FAB级熔断。卡片生产厂商和卡片发行商可以做进一步的熔断。熔断标记由三个BIT表示，每做一级熔断标记中就有一位被置0。
参数说明：Data_Buff	读出熔断标记的缓冲区指针。在调用该函数之前要事先给Data_Buff分配足够的内存空间，函数返回后Data_Buff中存放实际读出的熔断标记。标记的取值列表如下：
	07		卡片没有做任何熔断
	06		卡片做了FAB级熔断
	04		卡片做了CMA级熔断
00卡片做了PER级熔断
读出的熔断信息将作为调用写熔断函数的入口参数的条件使用。
返回信息：返回0表示成功，Data_Buff中存放实际读出的熔断标记。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwReadFuse153(HANDLE icdev, char *Data_Buff);

/*
函数说明：修改AT88SC153卡的熔断标记。AT88SC153卡的熔断是分级实现的。做了FAB级熔断后才可以做CMA级熔断，做了CMA级熔断后才可以做PRE级。做熔断之前要先读取AT88SC153卡的熔断标记，根据卡片以有的熔断级别确定实际要熔断的熔丝地址。
参数说明：Fuse_Addr			熔丝地址。熔丝地址列表如下：
						1：FAB级熔断。
						2：CMA级熔断。
		        4：PER级熔断。要根据事先读取的卡熔断标记来确定本次熔断的熔丝地址，熔断标记和熔丝地址的对应关系如下：
熔断标记    本级熔丝   下级熔丝（参数）
7           无         1
6           1          2
4           2          4
0           4          无
也就是说如果本次读出的熔断标记为“6”表示已经熔断了熔丝“1”，再要做熔断时的熔丝地址应该为“2”。
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwWriteFuse153(HANDLE icdev, char Fuse_Addr);

/*
函数说明：AT88SC153卡具有两组密码，每组密码有分为写密码和读密码，分别对卡的写和读操作进行保护。
         用户可以通过设置配置页中的ARx来为每个分区选择不同的密码组进行读写保护。对于系统功能配置区，固定使用第二套密码做安全保护。
         函数只执行密码比较操作不判断比较的正确与否。执行完本函数后要读取配置区中对应密码的错误记数器判断比较结果。
         如果比较正确则对应的错误记数器的值应该是“FF”。一个密码最多允许8次错误比较，如果8次连续的错误比较则该密码将被锁死。
参数说明：	Pwd_Number			密码组的编号。
0第一组密码。
1第二组密码。
						  	Pwd_Flag			密码类型。
0写密码。
1读密码
Pwd_Number	和Pwd_Flag共同确定要比较的密码。Pwd_Number=1，Pwd_Flag=0表示要比较的是第二组的写密码（卡片主密码）。
Data_Buff	密码数据的缓冲区。调用函数前该缓冲区保存要比较的密码。
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwCheckPwd153( HANDLE icdev, int Pwd_Number, int Pwd_Flag,char *Data_Buff);

/************************************************************************/
/* 复位应答：
pValue  返回153卡的应答信息，固定四字节  2C AA 55 A1*/
/************************************************************************/
int STDCALL mwReset153(HANDLE icdev, unsigned char *pValue);  


/************************************************************************/
/* 密码错误计数读取：
PwdNum   0-1 密码组的编号
PwdFlag  0 写密码，1 读密码
pValue  读取信息，1字节       */
/************************************************************************/
int STDCALL mwReadPAC153(HANDLE icdev, unsigned char PwdNum, unsigned char PwdFlag, unsigned char *pValue);

/************************************************************************/
/* 用户区访问权限设置：
Zone    用户区 号，0-2
*pValue  写信息，1字节*/
/************************************************************************/
int STDCALL mwWriteAccess153(HANDLE icdev, unsigned char ZoneNum,unsigned char Value );

/************************************************************************/
/* 用户区访问权限读取：
Zone    用户区 号，0-2
*pValue  读信息，1字节*/
/************************************************************************/
int STDCALL mwReadAccess153(HANDLE icdev, unsigned char ZoneNum,unsigned char *pValue );


/************************************************************************/
/* 修改密码：
PwdNum    0 -1 密码组编号
PwdFlag    0 写密码    1读密码
*pValue    写密码  ，3字节*/
/************************************************************************/
int STDCALL mwModifyPwd153(HANDLE icdev, unsigned char PwdNum, unsigned char PwdFlag, unsigned char *pValue );

/*
函数说明：通用读卡操作，从指定地址读取数据
参数说明：icdev: 通讯设备标识符
		  offset: 偏移地址
		  length：读取数据的长度
		  data：读出的数据
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwRead1604(HANDLE icdev, int offset, int length, unsigned char data[]);

/*
函数说明：通用写卡操作，向指定地址写数据，写之前需要先擦除
参数说明：icdev: 通讯设备标识符
          offset:偏移地址
          length：写入数据的长度
		  data：写入的数据
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwWrite1604(HANDLE icdev, int offset, int length, const unsigned char data[]);

/*
函数说明：擦除数据
参数说明：icdev: 通讯设备标识符	
		  offset:偏移地址
		  length：擦除数据的长度
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwErase1604(HANDLE icdev, int offset, int length);

/*
函数说明：读出卡密码
参数说明：icdev: 通讯设备标识符	
		  sector：0 主密码 
		          1 第一应用区
				  2 第二应用区
				  3 第三应用区
				  4 第四应用区
		  type：0 应用区密码，对于主密码，该参数无效
		        1 应用区擦除密码，对于主密码，该参数无效
		  password：读出的密码
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwReadPassword1604(HANDLE icdev, int sector, int type, unsigned char password[]);

/*
函数说明：验证卡密码
参数说明：icdev: 通讯设备标识符	
		  sector：0 主密码 
		          1 第一应用区
				  2 第二应用区
				  3 第三应用区
				  4 第四应用区
		  type：0 应用区密码，对于主密码，该参数无效
		        1 应用区擦除密码，对于主密码，该参数无效
		  password：验证的密码，所有密码都为两字节
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwVerifyPassword1604(HANDLE icdev, int sector, int type, const unsigned char password[]);

/*
函数说明：修改卡密码
参数说明：icdev: 通讯设备标识符	
		  sector：0 主密码 
		          1 第一应用区
				  2 第二应用区
				  3 第三应用区
				  4 第四应用区
		  type：0 应用区密码，对于主密码，该参数无效
		        1 应用区擦除密码，对于主密码，该参数无效
		  password：修改的密码         
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwChangePassword1604(HANDLE icdev, int sector, int type, const unsigned char password[]);

/*
函数说明：读出密码错误计数器值
参数说明：icdev: 通讯设备标识符	
		  sector：0 主密码 
		          1 第一应用区
				  2 第二应用区
				  3 第三应用区
				  4 第四应用区
		  type：0 应用区密码，对于主密码，该参数无效
		        1 应用区擦除密码，对于主密码，该参数无效
		  count：错误计数器值   
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwReadCount1604(HANDLE icdev, int sector, int type, int *count);

/*
函数说明：读取应用区数据
参数说明：icdev: 通讯设备标识符	
		  sector：1 第一应用区
				  2 第二应用区
				  3 第三应用区
				  4 第四应用区
		  offset：偏移地址
		  length：读取数据的长度
          data：读取的数据		  
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwReadPartition1604(HANDLE icdev, int sector, int offset, int length, unsigned char data[]);

/*
函数说明：向应用区写数据
参数说明：icdev: 通讯设备标识符	
		  sector：1 第一应用区
				  2 第二应用区
				  3 第三应用区
				  4 第四应用区
		  offset：偏移地址
		  length：写入数据的长度
          data：写入的数据		
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwWritePartition1604(HANDLE icdev, int sector, int offset, int length, const unsigned char data[]);

/*
函数说明：模拟个人化操作
参数说明：icdev: 通讯设备标识符	
          flag：0 取消模拟
                1 模拟个人化操作		  
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwSimulationPersonalization1604(HANDLE icdev, int flag);

/*
函数说明：个人化操作
参数说明：icdev: 通讯设备标识符	
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwPersonalization1604(HANDLE icdev);

/*
函数说明：读保护位清0
参数说明：icdev: 通讯设备标识符
		  sector：1 第一应用区
				  2 第二应用区
				  3 第三应用区
				  4 第四应用区
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwInitReadControl1604(HANDLE icdev, int sector);

/*
函数说明：写保护位清0
参数说明：icdev: 通讯设备标识符	
		  sector：1 第一应用区
				  2 第二应用区
				  3 第三应用区
				  4 第四应用区
返回信息：返回0表示成功。返回其他信息表示在操作过程中有错误发生
*/
int STDCALL mwInitWriteControl1604(HANDLE icdev, int sector);
#ifdef __cplusplus
};
#endif


#endif /* MWREADER_H_ */
