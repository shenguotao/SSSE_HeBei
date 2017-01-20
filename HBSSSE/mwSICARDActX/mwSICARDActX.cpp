// mwSICARDActX.cpp : CmwSICARDActXApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "mwSICARDActX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CmwSICARDActXApp theApp;

const GUID CDECL _tlid = { 0x9A2AAE9B, 0x4EBA, 0x4725, { 0xB6, 0xF6, 0x84, 0xCF, 0xF3, 0x15, 0xDB, 0x47 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CmwSICARDActXApp::InitInstance - DLL 初始化

BOOL CmwSICARDActXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CmwSICARDActXApp::ExitInstance - DLL 终止

int CmwSICARDActXApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
