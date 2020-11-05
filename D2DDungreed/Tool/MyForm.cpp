// MyForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_MAP_BUTTON, &CMyForm::OnBnClickedMapButton)
	ON_BN_CLICKED(IDC_PATHTOOL_BUTTON, &CMyForm::OnBnClickedPathtoolButton)
	ON_BN_CLICKED(IDC_OBJECT_BUTTON, &CMyForm::OnBnClickedObjectButton)
END_MESSAGE_MAP()


// CMyForm �����Դϴ�.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm �޽��� ó�����Դϴ�.

void CMyForm::OnBnClickedMapButton()
{
	assert(nullptr != m_MapTool.GetSafeHwnd());
	NULL_CHECK(m_MapTool.GetSafeHwnd());
	m_MapTool.ShowWindow(SW_SHOW); // SW_SHOW: â������� ���.
}


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_Font.CreatePointFont(200, L"consolas");

	// ID���� ���ؼ� ���� ���̾�α׿� ��ġ�� ����� ���� �� �ִ�.
	GetDlgItem(IDC_MAP_BUTTON)->SetFont(&m_Font); // ��ư�� ��Ʈ �����ϱ�
	GetDlgItem(IDC_PATHTOOL_BUTTON)->SetFont(&m_Font);
	GetDlgItem(IDC_OBJECT_BUTTON)->SetFont(&m_Font);

	m_MapTool.Create(IDD_MAP_TOOL);
	m_PathTool.Create(IDD_PATHTOOL);
	m_ObjectTool.Create(IDD_OBJECTTOOL);
}


void CMyForm::OnBnClickedPathtoolButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	assert(nullptr != m_PathTool.GetSafeHwnd());
	NULL_CHECK(m_PathTool.GetSafeHwnd());
	m_PathTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedObjectButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	assert(nullptr != m_PathTool.GetSafeHwnd());
	NULL_CHECK(m_ObjectTool.GetSafeHwnd());
	m_ObjectTool.ShowWindow(SW_SHOW);
}
