// MyForm.cpp : 구현 파일입니다.
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


// CMyForm 진단입니다.

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


// CMyForm 메시지 처리기입니다.

void CMyForm::OnBnClickedMapButton()
{
	assert(nullptr != m_MapTool.GetSafeHwnd());
	NULL_CHECK(m_MapTool.GetSafeHwnd());
	m_MapTool.ShowWindow(SW_SHOW); // SW_SHOW: 창모양으로 출력.
}


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_Font.CreatePointFont(200, L"consolas");

	// ID값을 통해서 현재 다이얼로그에 배치된 대상을 얻어올 수 있다.
	GetDlgItem(IDC_MAP_BUTTON)->SetFont(&m_Font); // 버튼에 폰트 적용하기
	GetDlgItem(IDC_PATHTOOL_BUTTON)->SetFont(&m_Font);
	GetDlgItem(IDC_OBJECT_BUTTON)->SetFont(&m_Font);

	m_MapTool.Create(IDD_MAP_TOOL);
	m_PathTool.Create(IDD_PATHTOOL);
	m_ObjectTool.Create(IDD_OBJECTTOOL);
}


void CMyForm::OnBnClickedPathtoolButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	assert(nullptr != m_PathTool.GetSafeHwnd());
	NULL_CHECK(m_PathTool.GetSafeHwnd());
	m_PathTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedObjectButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	assert(nullptr != m_PathTool.GetSafeHwnd());
	NULL_CHECK(m_ObjectTool.GetSafeHwnd());
	m_ObjectTool.ShowWindow(SW_SHOW);
}
