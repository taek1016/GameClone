// TerrainTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "TerrainTab.h"
#include "../Tool/Code/View/MyFormView.h"
#include "afxdialogex.h"

#include "../Tool/Code/Tool/TerrainTool.h"
#include "../Tool/Code/Tool/TerrainMeshTool.h"

// CTerrainTab 대화 상자입니다.


IMPLEMENT_DYNAMIC(CTerrainTab, CDialogEx)

CTerrainTab::CTerrainTab(CMyFormView* pParentForm, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TERRAIN_DLG, pParent)
	, m_pParentForm(pParentForm)
	, m_bInitialized(false)
	, m_pTerrainMeshTool(nullptr)
{

}

CTerrainTab::~CTerrainTab()
{
	Engine::Safe_Delete(m_pTerrainMeshTool);
	Engine::Safe_Delete(m_pTerrainTool);

	int iSize = static_cast<int>(m_vecDlg.size());
	for (int i = 0; i < iSize; ++i)
	{
		m_vecDlg[i] = nullptr;
	}

	m_pParentForm = nullptr;
}

void CTerrainTab::Initialize_FormView(void)
{
	DLL::pToolContainer->Add_Tool(L"TerrainTool", m_pTerrainTool);
	m_pTerrainTool->Activate();
}

const Engine::_bool CTerrainTab::Get_Initialized(void) const
{
	return m_bInitialized;
}

void CTerrainTab::Initialize_MapMeshes(void)
{
	m_bInitialized = true;

	m_pTerrainTool->Initialize_MapMeshes();
}

void CTerrainTab::Deactivate_Tool()
{
	m_pTerrainTool->DeActivate();
}

void CTerrainTab::Activate(void)
{
	m_pTerrainTool->Activate();
}

void CTerrainTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}


BEGIN_MESSAGE_MAP(CTerrainTab, CDialogEx)
	ON_BN_CLICKED(IDC_WIREFRAME, &CTerrainTab::OnBnClickedWireframe)
	ON_BN_CLICKED(IDC_SOLID, &CTerrainTab::OnBnClickedSolid)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTerrainTab::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CTerrainTab 메시지 처리기입니다.


BOOL CTerrainTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	const Engine::_tchar* szStr[] = { L"NavigationMesh", L"MapMesh" };
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

	m_pTerrainTool = new CTerrainTool(this);
	m_pTerrainTool->Create(IDD_TERRAIN_TOOL, &m_TabCtrl);
	m_pTerrainTool->MoveWindow(iStartX, iStartY, iWidth, iHeight);
	m_pTerrainTool->ShowWindow(SW_SHOW);

	m_vecDlg.push_back(m_pTerrainTool);

	m_pTerrainMeshTool = new CTerrainMeshTool(this);
	m_pTerrainMeshTool->Create(IDD_TERRAIN_MESH_DLG, &m_TabCtrl);
	m_pTerrainMeshTool->MoveWindow(iStartX, iStartY, iWidth, iHeight);
	m_pTerrainMeshTool->ShowWindow(SW_HIDE);

	m_vecDlg.push_back(m_pTerrainMeshTool);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTerrainTab::OnBnClickedWireframe()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}


void CTerrainTab::OnBnClickedSolid()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}


void CTerrainTab::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

#pragma region CancelItems
	int iSize = static_cast<int>(m_vecDlg.size());
	for (int i = 0; i < iSize; ++i)
	{
		if (nullptr != m_vecDlg[i])
		{
			m_vecDlg[i]->ShowWindow(SW_HIDE);
		}
	}
	Deactivate_Tool();
#pragma endregion

#pragma region SelectItem
	int iSel = m_TabCtrl.GetCurSel();

	m_vecDlg[iSel]->ShowWindow(SW_SHOW);

	switch (iSel)
	{
		// 네비 툴 활성화
		// 지형 툴 활성화
	case 0:
		m_pTerrainTool->Activate();
		break;

	case 1:
		break;
	}
#pragma endregion


}
