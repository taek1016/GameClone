// D:\Codes\D3DFrame\Tool\Code\View\DataTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "../Tool/Code/View/DataTab.h"
#include "../Tool/Code/View/MyFormView.h"
#include "afxdialogex.h"

#include "Tool/PathTool.h"

// CDataTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDataTab, CDialogEx)

CDataTab::CDataTab(CMyFormView* pParentForm, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DATA_TAB, pParent)
	, m_pParentForm(pParentForm)
	, m_pPathTool(nullptr)
{

}

CDataTab::~CDataTab()
{
	m_pParentForm = nullptr;

	Engine::Safe_Delete(m_pPathTool);
}

void CDataTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATA_TAB, m_TabCtrl);
}


BEGIN_MESSAGE_MAP(CDataTab, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_DATA_TAB, &CDataTab::OnTcnSelchangeDataTab)
END_MESSAGE_MAP()


// CDataTab 메시지 처리기입니다.


void CDataTab::OnTcnSelchangeDataTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	for (auto iter : m_vecDlg)
	{
		iter->ShowWindow(SW_HIDE);
	}

	int iSel = m_TabCtrl.GetCurSel();
	switch (iSel)
	{
	case DATA_PATH:
		m_pPathTool->Renew_Data();
		break;
	}

	m_vecDlg[iSel]->ShowWindow(SW_SHOW);
}


BOOL CDataTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	const Engine::_tchar* szStr[] = { L"Path" };
	const Engine::_int iSize = sizeof(szStr) / sizeof(szStr[0]);

	for (Engine::_int i = 0; i < iSize; ++i)
	{
		m_TabCtrl.InsertItem(i, szStr[i]);
	}

	m_vecDlg.reserve(iSize);

	int iStartX = 0;
	int iStartY = 25;
	int iWidth = 400;
	int iHeight = 600;

	m_pPathTool = new CPathTool(this);
	m_pPathTool->Create(IDD_PATH_DLG, &m_TabCtrl);
	m_pPathTool->MoveWindow(iStartX, iStartY, iWidth, iHeight);
	m_pPathTool->ShowWindow(SW_SHOW);

	m_vecDlg.push_back(m_pPathTool);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
