// D:\Codes\D3DFrame\Tool\Code\View\EffectTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "../Tool/Code/View/EffectTab.h"
#include "../Tool/Code/View/MyFormView.h"
#include "afxdialogex.h"

// CEffectTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CEffectTab, CDialogEx)

CEffectTab::CEffectTab(CMyFormView* pParentForm, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EFFECT_DLG, pParent)
	, m_pParentForm(pParentForm)
{

}

CEffectTab::~CEffectTab()
{
	m_pParentForm = nullptr;
}

void CEffectTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffectTab, CDialogEx)
END_MESSAGE_MAP()


// CEffectTab �޽��� ó�����Դϴ�.
