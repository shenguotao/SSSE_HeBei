/**
 * Created by mw on 2016/8/25.
 * Modify by mw on 2017/01/20.
 */

//卡类型识别
function RCardType()
{
	try
	{
		if(READER.iReaderhandle <= 0)
		{
			I_iDOpenPort(1);
		}
		var ret = READER.I_iRCardType(READER.iReaderhandle);
		if(ret != 0)
			msg.value = msg.value +"获取卡片类型失败!" + READER.iERRInfo + "\n";
		else
		{
			txtCardType.value = READER.cardtype;
		}
	}
	catch (e)
	{
        msg.value = msg.value + e.message + "\n";
	}
    msg.scrollTop = msg.scrollHeight;
}

// 读指纹信息
function readFingerPrint() {
    try {
        var dateBegin = new Date();  //开始时间
		if(READER.iReaderhandle <= 0)
		{
			I_iDOpenPort(1);
		}
        var ret = READER.I_iRMFFingerPrintInfo(READER.iReaderhandle);
        if (ret != 0) {
            msg.value = msg.value + "读指纹信息失败!" + READER.iERRInfo +"\n";
        }
        else {
            var dateEnd = new Date();  //结束时间
            var date3=dateEnd.getTime()-dateBegin.getTime()  //时间差的毫秒数
            txtFingerPrintInfo.value = READER.bFingerPrint;
   
            msg.value = msg.value + "耗时(ms):" + date3.toString() +"读指纹信息成功!" + "\n";
        }
        
    }
    catch (e){
        msg.value = msg.value + e.message + "\n";
    }
    msg.scrollTop = msg.scrollHeight;
}

// 写入指纹信息
function writeFingerPrint() {
    try {
        var dateBegin = new Date();  //开始时间
		if(READER.iReaderhandle <= 0)
		{
			I_iDOpenPort(1);
		}
		if(txtFingerPrintInfo.value == "")
		{
            msg.value = msg.value + "请输入指纹信息!" + "\n";
			return;
		}


        var ret = READER.I_iWMFFingerPrintInfo(READER.iReaderhandle, txtFingerPrintInfo.value);
        if (ret != 0) {
            msg.value = msg.value + "写入指纹信息失败!" + READER.iERRInfo +"\n";
        }
        else {
            var dateEnd = new Date();  //结束时间
            var date3=dateEnd.getTime()-dateBegin.getTime()  //时间差的毫秒数
                
            msg.value = msg.value + "耗时(ms):" + date3.toString() +"写入指纹信息成功!" + "\n";
        }
        
    }
    catch (e){
        msg.value = msg.value + e.message + "\n";
    }
    msg.scrollTop = msg.scrollHeight;
}
// 通用读卡
function readCard() {
    try{
        var dateBegin = new Date();  //开始时间
		if(READER.iReaderhandle <= 0)
		{
			I_iDOpenPort(1);
		}
		
		if(txtVerInfo.value == "" || txtPassword.value == "" || txtInputFileAddr.value == "")
		{
            msg.value = msg.value + "请输入版本/密码/读数据地址等信息!" + "\n";
			return;
		}
        var ret = READER.I_iRCardInfo(READER.iReaderhandle, txtVerInfo.value,txtPassword.value,txtInputFileAddr.value);
        if (ret != 0) {
            msg.value = msg.value + "通用读卡信息失败!" + READER.iERRInfo +"\n";
        }
        else {
            var dateEnd = new Date();  //结束时间
            var date3=dateEnd.getTime()-dateBegin.getTime()  //时间差的毫秒数
            msg.value = msg.value + "耗时(ms):" + date3.toString() + "通用读卡信息成功!" + "\n";
            txtOutFileData.value = READER.iOutFileData;
        }  
    }
    catch (e){
        msg.value = msg.value + e.message + "\n";
    }
    msg.scrollTop = msg.scrollHeight;
}

// 通用写卡
function writeCard() {
    try{
		if(READER.iReaderhandle <= 0)
		{
			I_iDOpenPort(1);
		}
		if(txtVerInfo.value == "" || txtPassword.value == "" || txtInputFileAddr.value == "" ||txtWriteCard.value =="")
		{
            msg.value = msg.value + "请输入版本/密码/卡数据地址/写卡数据等信息!" + "\n";
			return;
		}
        var ret = READER.iWriteCard(READER.iReaderhandle, txtVerInfo.value,txtPassword.value,txtInputFileAddr.value, txtWriteCard.value);
        if (ret != 0) {
            msg.value = msg.value + "通用写卡信息失败!" + READER.iERRInfo +"\n";
        }
        else {
            msg.value = msg.value + "通用写卡信息成功!" + "\n";
        }
        //txtWriteCard.value = READER.iERRInfo;
    }
    catch (e){
        msg.value = msg.value + e.message + "\n";
    }
    msg.scrollTop = msg.scrollHeight;
}

// PIN校验
function VerifyPIN() {
    try{		
		if(READER.iReaderhandle <= 0)
		{
			I_iDOpenPort(1);
		}
        var ret = READER.I_iPInputPIN(READER.iReaderHanldle, txtVerifyPIN.value);
        if (ret != 0) {
            msg.value = msg.value + "PIN校验失败!" + READER.iERRInfo +"\n";
        }
        else {
            msg.value = msg.value + "PIN校验成功!" + "\n";
        }
        //txtVerifyPIN.value = READER.iERRInfo;
    }
    catch (e){
        msg.value = msg.value + e.message + "\n";
    }
    msg.scrollTop = msg.scrollHeight;
}

// PIN修改
function ChangePIN() {
    try{
		
		if(READER.iReaderhandle <= 0)
		{
			I_iDOpenPort(1);
		}
        var ret = READER.I_iPChangePIN(READER.iReaderhandle, txtOldPIN.value, txtChangePIN.value);
        if (ret != 0) {
            msg.value = msg.value + "PIN修改失败!" + READER.iERRInfo +"\n";
        }
        else {
            msg.value = msg.value + "PIN修改成功!" + "\n";
        }
        //txtChangePIN.value = READER.iERRInfo;
    }
    catch (e){
        msg.value = msg.value + e.message + "\n";
    }
    msg.scrollTop = msg.scrollHeight;
}

// PIN重置
function ReloadPIN() {
    try{
		if(READER.iReaderhandle <= 0)
		{
			I_iDOpenPort(1);
		}
        var ret = READER.I_iPReloadPIN(READER.iReaderhandle, txtReloadPIN.value);
        if (ret != 0) {
            msg.value = msg.value + "PIN重置失败!" + READER.iERRInfo +"\n";
        }
        else {
            msg.value = msg.value + "PIN重置成功!" + "\n";
        }
        //txtReloadPIN.value = READER.iERRInfo;
    }
    catch (e){
        msg.value = msg.value + e.message + "\n";
    }
    msg.scrollTop = msg.scrollHeight;
}
