#pragma once

// mwSICARDActXPropPage.h : CmwSICARDActXPropPage 属性页类的声明。


// CmwSICARDActXPropPage : 有关实现的信息，请参阅 mwSICARDActXPropPage.cpp。

class CmwSICARDActXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CmwSICARDActXPropPage)
	DECLARE_OLECREATE_EX(CmwSICARDActXPropPage)

// 构造函数
public:
	CmwSICARDActXPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_MWSICARDACTX };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

