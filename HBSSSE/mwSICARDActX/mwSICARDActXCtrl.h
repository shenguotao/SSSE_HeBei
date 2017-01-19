#pragma once

// mwSICARDActXCtrl.h : CmwSICARDActXCtrl ActiveX 控件类的声明。


// CmwSICARDActXCtrl : 有关实现的信息，请参阅 mwSICARDActXCtrl.cpp。

class CmwSICARDActXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CmwSICARDActXCtrl)

// 构造函数
public:
	CmwSICARDActXCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CmwSICARDActXCtrl();

	DECLARE_OLECREATE_EX(CmwSICARDActXCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CmwSICARDActXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CmwSICARDActXCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CmwSICARDActXCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidcardtype = 25,
		dispidiReaderHandle = 24,
		dispidstrReadBin = 23,
		dispidstrFingerPrint = 22,
		dispidstrOutFileData = 21,
		dispidstrERRInfo = 20,
		dispidI_ICC_write_bin = 14L,
		dispidI_ICC_read_bin = 13L,
		dispidI_ICC_change_pin = 12L,
		dispidI_ICC_verify = 11L,
		dispidI_iRCardType = 10L,
		dispidI_iWMFFingerPrintInfo = 9L,
		dispidI_iRMFFingerPrintInfo = 8L,
		dispidI_iRCardInfo = 7L,
		dispidI_iWCardInfo = 6L,
		dispidI_iPReloadPIN = 5L,
		dispidI_iPChangePIN = 4L,
		dispidI_iPInputPIN = 3L,
		dispidI_iDCloseReader = 2L,
		dispidl_iDOpenPort = 1L
	};
protected:


public:

protected:
	LONG I_iDOpenPort(LONG iReaderPort);
	LONG I_iDCloseReader(LONG gLngFd);
	LONG I_iPInputPIN(LONG gLngFD, LPCTSTR szPasswd);
	LONG I_iPChangePIN(LONG gLngFD, LPCTSTR szOldPasswd, LPCTSTR szNewPasswd);
	LONG I_iPReloadPIN(LONG glngFd, LPCTSTR szCardPasswd);
	LONG I_iWCardInfo(LONG glngFd, LPCTSTR strVerInfo, LPCTSTR striPassword, LPCTSTR striInputFileAddr, LPCTSTR striOutFileData);
	LONG I_iRCardInfo(LONG glngFd, LPCTSTR strVerInfo, LPCTSTR striPassword, LPCTSTR striInputFileAddr);
	LONG I_iRMFFingerPrintInfo(LONG glngFd);
	LONG I_iWMFFingerPrintInfo(LONG glngFd, LPCTSTR strbFingerPrint);
	LONG I_iRCardType(LONG glngFd);
	LONG I_ICC_verify(LONG glngFD, LONG pin_len, LPCTSTR strPIN);
	LONG I_ICC_change_pin(LONG glngFd, LONG pin_len, LPCTSTR strOldPin, LPCTSTR strNewPIN);
	LONG I_ICC_read_bin(LONG glngFd, LONG offset, LONG rlen);
	LONG I_ICC_write_bin(LONG glngFd, LONG offset, LONG wlen, LPCTSTR strData);
	void OnstrERRInfoChanged(void);
	CString m_strERRInfo;
	void OnstrOutFileDataChanged(void);
	CString m_strOutFileData;
	void OnstrFingerPrintChanged(void);
	CString m_strFingerPrint;
	void OnstrReadBinChanged(void);
	CString m_strReadBin;
	void OniReaderHandleChanged(void);
	LONG m_iReaderHandle;
	void OncardtypeChanged(void);
	CString m_cardtype;
};

