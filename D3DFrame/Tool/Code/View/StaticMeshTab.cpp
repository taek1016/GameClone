// TabDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "StaticMeshTab.h"
#include "../Tool/Code/View/MyFormView.h"
#include "afxdialogex.h"

#include "../Tool/Code/Tool/StaticMeshTool.h"
#include "Object/ToolStaticObjectCtrl.h"
#include "Object/ToolStaticObject.h"

// CTabDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CStaticMeshTab, CDialogEx)

CStaticMeshTab::CStaticMeshTab(CMyFormView* pParentForm, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYFORMVIEW, pParent)
	, m_pParentForm(pParentForm)
	
	, m_pMeshTool(nullptr)

	, m_bMeshLoaded(false)
{

}

CStaticMeshTab::~CStaticMeshTab()
{
	m_pParentForm = nullptr;

	Engine::Safe_Delete(m_pMeshTool);
}

const Engine::_bool & CStaticMeshTab::Get_Initialized(void) const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_bMeshLoaded;
}

void CStaticMeshTab::Initialize_StaticMeshTab(void)
{
	m_pMeshTool->Activate();
	DLL::pToolContainer->Add_Tool(L"StaticMeshTool", m_pMeshTool);
}

void CStaticMeshTab::Key_Input(void)
{
	m_pMeshTool->KeyInput();
}

void CStaticMeshTab::Initialize_StaticMeshLoad(void)
{
	m_bMeshLoaded = true;
	// 메쉬 로드.
	DLL::pDataMgr->Initialize_StaticMeshes();
	DLL::pToolContainer->Add_Tool(L"StaticMeshTool", m_pMeshTool);

	auto pList = DLL::pDataMgr->Get_DataList(L"StaticMesh");
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	for (auto iter : *pList)
	{
		DLL::pObjMgr->Add_Prefab(iter->wStrName.c_str(), CToolStaticObject::Create(pGraphicDev, iter->wStrName.c_str()));
	}
}

void CStaticMeshTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}


BEGIN_MESSAGE_MAP(CStaticMeshTab, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CStaticMeshTab::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CTabDlg 메시지 처리기입니다.


void CStaticMeshTab::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#pragma region Deactivate
	m_pMeshTool->DeActivate();
#pragma endregion

	for (auto iter : m_vecDlg)
	{
		iter->ShowWindow(SW_HIDE);
	}

	int iSel = m_TabCtrl.GetCurSel();

	m_vecDlg[iSel]->ShowWindow(SW_SHOW);
	switch (iSel)
	{
	case 0:
		m_pMeshTool->Activate();
		break;

	case 1:
		//m_pDynamicMeshTool->Activate();
		break;
	}
}


BOOL CStaticMeshTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	const Engine::_tchar* szStr[] = { L"StaticMesh" };
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

	m_pMeshTool = new CStaticMeshTool(this);
	m_pMeshTool->Create(IDD_STATIC_MESH_DLG, &m_TabCtrl);
	m_pMeshTool->MoveWindow(iStartX, iStartY, iWidth, iHeight);
	m_pMeshTool->ShowWindow(SW_SHOW);

	m_vecDlg.push_back(m_pMeshTool);


	//m_pDynamicMeshTool = new CStaticMeshTool(this);
	//m_pDynamicMeshTool->Create(IDD_STATIC_MESH_DLG, &m_TabCtrl);
	//m_pDynamicMeshTool->MoveWindow(iStartX, iStartY, iWidth, iHeight);
	//m_pDynamicMeshTool->ShowWindow(SW_SHOW);

	//m_vecDlg.push_back(m_pDynamicMeshTool);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
