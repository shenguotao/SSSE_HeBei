// mwSICARDActXPropPage.cpp : CmwSICARDActXPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "mwSICARDActX.h"
#include "mwSICARDActXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CmwSICARDActXPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CmwSICARDActXPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CmwSICARDActXPropPage, "MWSICARDACTX.mwSICARDActXPropPage.1",
	0xdf303b8f, 0x8352, 0x4007, 0xa9, 0xc, 0x20, 0x65, 0x69, 0x85, 0xca, 0x38)



// CmwSICARDActXPropPage::CmwSICARDActXPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CmwSICARDActXPropPage ��ϵͳע�����

BOOL CmwSICARDActXPropPage::CmwSICARDActXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MWSICARDACTX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CmwSICARDActXPropPage::CmwSICARDActXPropPage - ���캯��

CmwSICARDActXPropPage::CmwSICARDActXPropPage() :
	COlePropertyPage(IDD, IDS_MWSICARDACTX_PPG_CAPTION)
{
}



// CmwSICARDActXPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CmwSICARDActXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CmwSICARDActXPropPage ��Ϣ�������
