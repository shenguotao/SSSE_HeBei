// mwSICARDActX.cpp : CmwSICARDActXApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "mwSICARDActX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CmwSICARDActXApp theApp;

const GUID CDECL _tlid = { 0x9A2AAE9B, 0x4EBA, 0x4725, { 0xB6, 0xF6, 0x84, 0xCF, 0xF3, 0x15, 0xDB, 0x47 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CmwSICARDActXApp::InitInstance - DLL ��ʼ��

BOOL CmwSICARDActXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CmwSICARDActXApp::ExitInstance - DLL ��ֹ

int CmwSICARDActXApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
