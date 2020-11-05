// D:\Codes\D3DFrame\Tool\Code\View\DyMeshTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"

#include "View\DyMeshTab.h"
#include "View\DynamicObjControlTool.h"
#include "View\PrefabDlg.h"

#include "afxdialogex.h"
#include "DyMeshTab.h"


// DyMeshTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDyMeshTab, CDialogEx)

CDyMeshTab::CDyMeshTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DYNAMIC_MESH_DLG, pParent)
	, m_bInitialized(false)
	, m_pMonsterMesh(nullptr)
	, m_pPrefabDlg(nullptr)
	, m_bActivated(false)
{

}

CDyMeshTab::~CDyMeshTab()
{
	Engine::Safe_Delete(m_pPrefabDlg);
	Engine::Safe_Delete(m_pMonsterMesh);
}

void CDyMeshTab::Initialize_DynamicMeshTab(void)
{
	DLL::pToolContainer->Add_Tool(L"DynamicMeshTool", this);
	DLL::pDataMgr->Initialize_DynamicMeshes();

	m_pPrefabDlg->Initialize_Prefab();
}

void CDyMeshTab::Initialize_DynamicMeshLoad(void)
{
	m_bInitialized = true;

	list<FILE_INFO*>* pList = DLL::pDataMgr->Get_DataList(L"DynamicMesh");

	for (auto iter : *pList)
	{
		DLL::pResourcesMgr->Initialize_Meshes(DLL::pGraphicDev->GetDevice(),
			0,
			iter->wStrName.c_str(),
			Engine::MESHTYPE::TYPE_DYNAMIC,
			iter->wStrFilePath.c_str(),
			iter->wStrFileName.c_str()
		);
	}
	m_pPrefabDlg->Initialize_Names();

	m_pMonsterMesh->Initialize_DynamicMeshTab();
}

Engine::_bool CDyMeshTab::Get_Initialized(void)
{
	return m_bInitialized;
}

void CDyMeshTab::DeActivate(void)
{
	m_pMonsterMesh->Deactivate();
	m_bActivated = false;
}

void CDyMeshTab::Activate(void)
{
	m_pMonsterMesh->Activate();
	m_bActivated = true;
}

void CDyMeshTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}


BEGIN_MESSAGE_MAP(CDyMeshTab, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDyMeshTab::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// DyMeshTab 메시지 처리기입니다.


BOOL CDyMeshTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	const Engine::_int iMaxStr = 256;
	TCHAR szTab[][iMaxStr] = { L"Prefab", L"DynamicObj" };
	const Engine::_int iSize = sizeof(szTab) / sizeof(szTab[0]);

	for (Engine::_int i = 0; i < iSize; ++i)
	{
		m_TabCtrl.InsertItem(i, szTab[i]);
	}
	m_TabCtrl.SetCurSel(0);

	const Engine::_int iWidth = 400;
	const Engine::_int iHeight = 600;
	const Engine::_int iStartX = 0;
	const Engine::_int iStartY = 25;

	m_pPrefabDlg = new CPrefabDlg;
	m_pPrefabDlg->Create(IDD_PREFAB_DLG, &m_TabCtrl);
	m_pPrefabDlg->MoveWindow(iStartX, iStartY, iWidth, iHeight);
	m_pPrefabDlg->ShowWindow(SW_SHOW);

	m_vecDialog.push_back(m_pPrefabDlg);

	m_pMonsterMesh = new CDynamicObjTool(this);
	m_pMonsterMesh->Create(IDD_DYNAMIC_MONSTER, &m_TabCtrl);
	m_pMonsterMesh->MoveWindow(iStartX, iStartY, iWidth, iHeight);
	m_pMonsterMesh->ShowWindow(SW_HIDE);

	m_vecDialog.push_back(m_pMonsterMesh);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDyMeshTab::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	for (auto iter : m_vecDialog)
	{
		iter->ShowWindow(SW_HIDE);
	}

	int iSel = m_TabCtrl.GetCurSel();

	switch (iSel)
	{
	case 0:
		
		break;

	case 1:
		m_pMonsterMesh->Activate();
		break;
	}
	m_vecDialog[iSel]->ShowWindow(SW_SHOW);

}
