#pragma once

// mwSICARDActXPropPage.h : CmwSICARDActXPropPage ����ҳ���������


// CmwSICARDActXPropPage : �й�ʵ�ֵ���Ϣ������� mwSICARDActXPropPage.cpp��

class CmwSICARDActXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CmwSICARDActXPropPage)
	DECLARE_OLECREATE_EX(CmwSICARDActXPropPage)

// ���캯��
public:
	CmwSICARDActXPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_MWSICARDACTX };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

