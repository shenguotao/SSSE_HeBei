// mwSICARDActXPropPage.cpp : CmwSICARDActXPropPage 属性页类的实现。

#include "stdafx.h"
#include "mwSICARDActX.h"
#include "mwSICARDActXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CmwSICARDActXPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CmwSICARDActXPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CmwSICARDActXPropPage, "MWSICARDACTX.mwSICARDActXPropPage.1",
	0xdf303b8f, 0x8352, 0x4007, 0xa9, 0xc, 0x20, 0x65, 0x69, 0x85, 0xca, 0x38)



// CmwSICARDActXPropPage::CmwSICARDActXPropPageFactory::UpdateRegistry -
// 添加或移除 CmwSICARDActXPropPage 的系统注册表项

BOOL CmwSICARDActXPropPage::CmwSICARDActXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MWSICARDACTX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CmwSICARDActXPropPage::CmwSICARDActXPropPage - 构造函数

CmwSICARDActXPropPage::CmwSICARDActXPropPage() :
	COlePropertyPage(IDD, IDS_MWSICARDACTX_PPG_CAPTION)
{
}



// CmwSICARDActXPropPage::DoDataExchange - 在页和属性间移动数据

void CmwSICARDActXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CmwSICARDActXPropPage 消息处理程序
