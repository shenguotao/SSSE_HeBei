// mwSICARDActXCtrl.cpp : CmwSICARDActXCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "mwSICARDActX.h"
#include "mwSICARDActXCtrl.h"
#include "mwSICARDActXPropPage.h"
#include "afxdialogex.h"

#include "../mwSICARD/mwSICARD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(lib, "..\\Debug\\mwSICARD.lib")
#else
#pragma comment(lib, "..\\Release\\mwSICARD.lib")
#endif


#define ERR_INFO_LEN	128
#define READ_FILE_LEN	512
#define FINGER_FILE_LEN	3075


IMPLEMENT_DYNCREATE(CmwSICARDActXCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CmwSICARDActXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CmwSICARDActXCtrl, COleControl)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_iDOpenPort", dispidl_iDOpenPort, I_iDOpenPort, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_iDCloseReader", dispidI_iDCloseReader, I_iDCloseReader, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_iPInputPIN", dispidI_iPInputPIN, I_iPInputPIN, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_iPChangePIN", dispidI_iPChangePIN, I_iPChangePIN, VT_I4, VTS_I4 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_iPReloadPIN", dispidI_iPReloadPIN, I_iPReloadPIN, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_iWCardInfo", dispidI_iWCardInfo, I_iWCardInfo, VT_I4, VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_iRCardInfo", dispidI_iRCardInfo, I_iRCardInfo, VT_I4, VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_iRMFFingerPrintInfo", dispidI_iRMFFingerPrintInfo, I_iRMFFingerPrintInfo, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_iWMFFingerPrintInfo", dispidI_iWMFFingerPrintInfo, I_iWMFFingerPrintInfo, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_iRCardType", dispidI_iRCardType, I_iRCardType, VT_I4, VTS_I4)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_ICC_verify", dispidI_ICC_verify, I_ICC_verify, VT_I4, VTS_I4 VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_ICC_change_pin", dispidI_ICC_change_pin, I_ICC_change_pin, VT_I4, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_ICC_read_bin", dispidI_ICC_read_bin, I_ICC_read_bin, VT_I4, VTS_I4 VTS_I4 VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_ICC_write_bin", dispidI_ICC_write_bin, I_ICC_write_bin, VT_I4, VTS_I4 VTS_I4 VTS_I4 VTS_BSTR)
	
	
	DISP_PROPERTY_NOTIFY_ID(CmwSICARDActXCtrl, "iReaderhandle", dispidiReaderhandle, m_iReaderhandle, OniReaderhandleChanged, VT_I4)
	DISP_PROPERTY_NOTIFY_ID(CmwSICARDActXCtrl, "cardtype", dispidcardtype, m_cardtype, OncardtypeChanged, VT_BSTR)
    DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_getCardATR", dispidI_getCardATR, I_getCardATR, VT_I4, VTS_I4)
    DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_getCardNO", dispidI_getCardNO, I_getCardNO, VT_I4, VTS_I4)
    DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_AuthIRK", dispidI_AuthIRK, I_AuthIRK, VT_I4, VTS_I4)
    DISP_FUNCTION_ID(CmwSICARDActXCtrl, "I_iGetPSAMcode", dispidI_iGetPSAMcode, I_iGetPSAMcode, VT_I4, VTS_I4)
    DISP_PROPERTY_NOTIFY_ID(CmwSICARDActXCtrl, "ATR", dispidATR, m_ATR, OnATRChanged, VT_BSTR)
    DISP_PROPERTY_NOTIFY_ID(CmwSICARDActXCtrl, "szCardNo", dispidszCardNo, m_szCardNo, OnszCardNoChanged, VT_BSTR)
    DISP_PROPERTY_NOTIFY_ID(CmwSICARDActXCtrl, "iERRInfo", dispidiERRInfo, m_iERRInfo, OniERRInfoChanged, VT_BSTR)
    DISP_PROPERTY_NOTIFY_ID(CmwSICARDActXCtrl, "ipsamcode", dispidipsamcode, m_ipsamcode, OnipsamcodeChanged, VT_BSTR)
    DISP_PROPERTY_NOTIFY_ID(CmwSICARDActXCtrl, "idevicecode", dispididevicecode, m_idevicecode, OnidevicecodeChanged, VT_BSTR)
    DISP_PROPERTY_NOTIFY_ID(CmwSICARDActXCtrl, "iOutFileData", dispidiOutFileData, m_iOutFileData, OniOutFileDataChanged, VT_BSTR)
    DISP_PROPERTY_NOTIFY_ID(CmwSICARDActXCtrl, "bFingerPrint", dispidbFingerPrint, m_bFingerPrint, OnbFingerPrintChanged, VT_BSTR)
    DISP_PROPERTY_NOTIFY_ID(CmwSICARDActXCtrl, "data", dispiddata, m_data, OndataChanged, VT_BSTR)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CmwSICARDActXCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CmwSICARDActXCtrl, 1)
	PROPPAGEID(CmwSICARDActXPropPage::guid)
END_PROPPAGEIDS(CmwSICARDActXCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CmwSICARDActXCtrl, "MWSICARDACTX.mwSICARDActXCtrl.1",
	0xe2baca2a, 0x6abc, 0x4751, 0x81, 0xa3, 0xda, 0x19, 0xed, 0xf1, 0x81, 0x5)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CmwSICARDActXCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID IID_DmwSICARDActX = { 0x3FFE3C52, 0xF20E, 0x4E61, { 0x90, 0x25, 0x2E, 0x3C, 0x7B, 0x5D, 0x89, 0xBA } };
const IID IID_DmwSICARDActXEvents = { 0x192ECAEA, 0xD223, 0x465E, { 0xB3, 0x79, 0x39, 0xC0, 0x8A, 0x90, 0xFA, 0xD3 } };


// �ؼ�������Ϣ

static const DWORD _dwmwSICARDActXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CmwSICARDActXCtrl, IDS_MWSICARDACTX, _dwmwSICARDActXOleMisc)



// CmwSICARDActXCtrl::CmwSICARDActXCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CmwSICARDActXCtrl ��ϵͳע�����

BOOL CmwSICARDActXCtrl::CmwSICARDActXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MWSICARDACTX,
			IDB_MWSICARDACTX,
			afxRegApartmentThreading,
			_dwmwSICARDActXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CmwSICARDActXCtrl::CmwSICARDActXCtrl - ���캯��

CmwSICARDActXCtrl::CmwSICARDActXCtrl()
{
	InitializeIIDs(&IID_DmwSICARDActX, &IID_DmwSICARDActXEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}



// CmwSICARDActXCtrl::~CmwSICARDActXCtrl - ��������

CmwSICARDActXCtrl::~CmwSICARDActXCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// CmwSICARDActXCtrl::OnDraw - ��ͼ����

void CmwSICARDActXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CmwSICARDActXCtrl::DoPropExchange - �־���֧��

void CmwSICARDActXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CmwSICARDActXCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CmwSICARDActXCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CmwSICARDActXCtrl::AboutBox - ���û���ʾ�����ڡ���

void CmwSICARDActXCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_MWSICARDACTX);
	dlgAbout.DoModal();
}



// CmwSICARDActXCtrl ��Ϣ�������


LONG CmwSICARDActXCtrl::I_iDOpenPort(LONG iReaderPort)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	char szErrInfo[ERR_INFO_LEN];
	int iRet = 0;
	int iHandle = 0;

	memset(szErrInfo, 0, sizeof(szErrInfo));
	iRet = iDOpenPort((int)iReaderPort, &iHandle, szErrInfo);
	if(iRet)
	{
		m_iERRInfo.Format("%s", szErrInfo);
		return iRet;
	}

	m_iERRInfo.Format("NULL");
	m_iReaderhandle = iHandle;	

	return 0;
}

//
//LONG CmwSICARDActXCtrl::I_iDCloseReader(LONG glngFd)
//{
//	return 0;
//}


LONG CmwSICARDActXCtrl::I_iDCloseReader(LONG glngFd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	int iRet = 0;
	char szErrInfo[ERR_INFO_LEN];
	
	memset(szErrInfo, 0, sizeof(szErrInfo));
	iRet = iDCloseReader((int)glngFd, szErrInfo);
	if(iRet)
	{
		m_iERRInfo.Format("%s", szErrInfo);
		return iRet;
	}
	
	m_iERRInfo.Format("NULL");
	return 0;
}


LONG CmwSICARDActXCtrl::I_iPInputPIN(LONG gLngFD, LPCTSTR szPasswd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

	return 0;
}


LONG CmwSICARDActXCtrl::I_iPChangePIN(LONG glngFd, LPCTSTR szOldPasswd, LPCTSTR szNewPasswd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������	
	int iRet = 0;
	char szErrInfo[ERR_INFO_LEN];
	
	memset(szErrInfo, 0, sizeof(szErrInfo));
	iRet = iPChangePIN((int)glngFd, (char*)szOldPasswd, (char*)szNewPasswd, szErrInfo);
	if(iRet)
	{
		m_iERRInfo.Format("%s", szErrInfo);
		return iRet;
	}
	
	m_iERRInfo.Format("NULL");

	return 0;
}


LONG CmwSICARDActXCtrl::I_iPReloadPIN(LONG glngFd, LPCTSTR szCardPasswd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	int iRet = 0;
	char szErrInfo[ERR_INFO_LEN];
	
	memset(szErrInfo, 0, sizeof(szErrInfo));
	iRet = iPReloadPIN((int)glngFd, (char*)szCardPasswd, szErrInfo);
	if(iRet)
	{
		m_iERRInfo.Format("%s", szErrInfo);
		return iRet;
	}
	
	m_iERRInfo.Format("NULL");

	return 0;
}


LONG CmwSICARDActXCtrl::I_iWCardInfo(LONG glngFd, LPCTSTR strVerInfo, LPCTSTR striPassword, LPCTSTR striInputFileAddr, LPCTSTR striOutFileData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	int iRet = 0;
	char szErrInfo[ERR_INFO_LEN];
	
	memset(szErrInfo, 0, sizeof(szErrInfo));
	iRet = iWCardInfo((int)glngFd, (char*)strVerInfo, (char*)striPassword, (char*) striInputFileAddr, (char*)striOutFileData, szErrInfo);
	if(iRet)
	{
		m_iERRInfo.Format("%s", szErrInfo);
		return iRet;
	}
	
	m_iERRInfo.Format("NULL");

	return 0;
}


LONG CmwSICARDActXCtrl::I_iRCardInfo(LONG glngFd, LPCTSTR strVerInfo, LPCTSTR striPassword, LPCTSTR striInputFileAddr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	int iRet = 0;
	char szErrInfo[ERR_INFO_LEN];
	char szFileData[READ_FILE_LEN];
	
	memset(szErrInfo, 0, sizeof(szErrInfo));
	memset(szFileData, 0, sizeof(szFileData));
	iRet = iRCardInfo((int)glngFd, (char*)strVerInfo, (char*)striPassword, (char*)striInputFileAddr, szFileData, szErrInfo);
	if(iRet)
	{
		m_iERRInfo.Format("%s", szErrInfo);
		m_iOutFileData.Empty();
		return iRet;
	}
	
	m_iERRInfo.Format("NULL");
	m_iOutFileData.Format("%s", szFileData);
	return 0;
}


LONG CmwSICARDActXCtrl::I_iRMFFingerPrintInfo(LONG glngFd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	int iRet = 0;
	char szErrInfo[ERR_INFO_LEN];
	char szFingerFileData[FINGER_FILE_LEN];//3K
	
	memset(szErrInfo, 0, sizeof(szErrInfo));
	memset(szFingerFileData, 0, sizeof(szFingerFileData));
	iRet = iRMFFingerPrintInfo((int)glngFd, szFingerFileData, szErrInfo);
	if(iRet)
	{
		m_iERRInfo.Format("%s", szErrInfo);
		m_data.Empty();
		return iRet;
	}
	
	m_iERRInfo.Format("NULL");
	m_data.Format("%s", szFingerFileData);
	return 0;
}


LONG CmwSICARDActXCtrl::I_iWMFFingerPrintInfo(LONG glngFd, LPCTSTR strbFingerPrint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	int iRet = 0;
	char szErrInfo[ERR_INFO_LEN];
	
	memset(szErrInfo, 0, sizeof(szErrInfo));
	iRet = iWMFFingerPrintInfo((int)glngFd, (char*)strbFingerPrint, szErrInfo);
	if(iRet)
	{
		m_iERRInfo.Format("%s", szErrInfo);
		return iRet;
	}
	
	m_iERRInfo.Format("NULL");
	return 0;
}


LONG CmwSICARDActXCtrl::I_iRCardType(LONG glngFd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	int iRet = 0;
	char szErrInfo[ERR_INFO_LEN];
	char szCardType[10];
	
	memset(szErrInfo, 0, sizeof(szErrInfo));
	memset(szCardType, 0, sizeof(szCardType));
	iRet = iRCardType(glngFd, szCardType, szErrInfo);
	if(iRet)
	{
		m_iERRInfo.Format("%s", szErrInfo);
		return iRet;
	}
	
	m_iERRInfo.Format("NULL");
	return 0;
}


LONG CmwSICARDActXCtrl::I_ICC_verify(LONG glngFD, LONG pin_len, LPCTSTR strPIN)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	int iRet = 0;

	iRet = ICC_verify(glngFD, (char)pin_len, (char*)strPIN);
	if(iRet)
	{
		return iRet;
	}
	
	return 0;
}


LONG CmwSICARDActXCtrl::I_ICC_change_pin(LONG glngFd, LONG pin_len, LPCTSTR strOldPin, LPCTSTR strNewPIN)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	int iRet = 0;

	iRet = ICC_change_pin(glngFd, (char)pin_len, (char*)strOldPin, (char*)strNewPIN);
	if(iRet)
	{
		return iRet;
	}

	return 0;
}


LONG CmwSICARDActXCtrl::I_ICC_read_bin(LONG glngFd, LONG offset, LONG rlen)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	int iRet = 0;
	char szReadData[READ_FILE_LEN];

	memset(szReadData, 0, sizeof(szReadData));
	iRet = ICC_read_bin(glngFd, (int)offset, (int)rlen, szReadData);
	if(iRet)
	{
		m_data.Empty();
		return iRet;
	}

	m_data.Format("%s", szReadData);
	return 0;
}


LONG CmwSICARDActXCtrl::I_ICC_write_bin(LONG glngFd, LONG offset, LONG wlen, LPCTSTR strData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	return ICC_write_bin(glngFd, (int)offset, (int)wlen, (char*)strData);
}


void CmwSICARDActXCtrl::OniReaderhandleChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ�������Դ���������

	SetModifiedFlag();
}


void CmwSICARDActXCtrl::OncardtypeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ�������Դ���������

	SetModifiedFlag();
}


BOOL CmwSICARDActXCtrl::IsInvokeAllowed(DISPID /*dispid*/)
{
    // TODO: �ڴ����ר�ô����/����û���

    return TRUE;
}


LONG CmwSICARDActXCtrl::I_getCardATR(LONG glngFd)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ���ӵ��ȴ���������

    return 0;
}


LONG CmwSICARDActXCtrl::I_getCardNO(LONG glngFd)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ���ӵ��ȴ���������

    return 0;
}


LONG CmwSICARDActXCtrl::I_AuthIRK(LONG glngFd)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ���ӵ��ȴ���������

    return 0;
}


LONG CmwSICARDActXCtrl::I_iGetPSAMcode(LONG glngFd)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ���ӵ��ȴ���������

    return 0;
}


void CmwSICARDActXCtrl::OnATRChanged(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ�������Դ���������

    SetModifiedFlag();
}


void CmwSICARDActXCtrl::OnszCardNoChanged(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ�������Դ���������

    SetModifiedFlag();
}


void CmwSICARDActXCtrl::OniERRInfoChanged(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ�������Դ���������

    SetModifiedFlag();
}


void CmwSICARDActXCtrl::OnipsamcodeChanged(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ�������Դ���������

    SetModifiedFlag();
}


void CmwSICARDActXCtrl::OnidevicecodeChanged(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ�������Դ���������

    SetModifiedFlag();
}


void CmwSICARDActXCtrl::OniOutFileDataChanged(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ�������Դ���������

    SetModifiedFlag();
}


void CmwSICARDActXCtrl::OnbFingerPrintChanged(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ�������Դ���������

    SetModifiedFlag();
}


void CmwSICARDActXCtrl::OndataChanged(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: �ڴ�������Դ���������

    SetModifiedFlag();
}
