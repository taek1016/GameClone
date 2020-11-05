// D:\Codes\D3DFrame\Tool\Code\View\MyFormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "../Code/View/MyFormView.h"

#include "../Code/View/TerrainTab.h"
#include "../Code/View/StaticMeshTab.h"
#include "../Code/View/CamDlg.h"
#include "../Code/View/EffectTab.h"
#include "../Code/View/DyMeshTab.h"
#include "../Code/View/DataTab.h"

#include "ToolView.h"
// CMyFormView

IMPLEMENT_DYNCREATE(CMyFormView, CFormView)

CMyFormView::CMyFormView()
	: CFormView(IDD_MYFORMVIEW)
{

}

CMyFormView::~CMyFormView()
{
	Engine::Safe_Delete(m_pTerrainTab);
	Engine::Safe_Delete(m_pStaticMeshTab);
	Engine::Safe_Delete(m_pDataTab);
	Engine::Safe_Delete(m_pEffectTab);
	Engine::Safe_Delete(m_pDynamicMeshTab);

	Engine::_int iSize = static_cast<Engine::_int>(m_vecDialog.size());

	for (Engine::_int i = 0; i < iSize; ++i)
	{
		m_vecDialog[i] = nullptr;
	}
}

void CMyFormView::Initialize_FormView(void)
{
	m_pTerrainTab->Initialize_FormView();
	m_pStaticMeshTab->Initialize_StaticMeshTab();
	m_pDynamicMeshTab->Initialize_DynamicMeshTab();
}

void CMyFormView::Set_ToolView(CToolView * pToolView)
{
	m_pToolView = pToolView;
}

void CMyFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CMyFormView, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMyFormView::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMyFormView 진단입니다.

#ifdef _DEBUG
void CMyFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyFormView 메시지 처리기입니다.


void CMyFormView::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

#pragma region DeactivateOtherItem
	for (auto iter : m_vecDialog)
	{
		iter->ShowWindow(SW_HIDE);
	}
	m_pTerrainTab->Deactivate_Tool();
	m_pDynamicMeshTab->DeActivate();
#pragma endregion

#pragma region ActivateSelectedItem
	int iSel = m_TabCtrl.GetCurSel();

	switch (iSel)
	{
	case CMyFormView::TAB_TERRAIN:
		m_pTerrainTab->Activate();
		break;

	case CMyFormView::TAB_STATIC_MESH:
		if (!m_pStaticMeshTab->Get_Initialized())
		{
			m_pStaticMeshTab->Initialize_StaticMeshLoad();
		}
		m_pStaticMeshTab->Initialize_StaticMeshTab();
		break;

	case CMyFormView::TAB_DYNAMIC_MESH:
		if (!m_pDynamicMeshTab->Get_Initialized())
		{
			m_pDynamicMeshTab->Initialize_DynamicMeshLoad();
		}
		m_pDynamicMeshTab->Activate();
		break;

	case CMyFormView::TAB_DATA:
		break;
	case CMyFormView::TAB_EFFECT:
		break;
	case CMyFormView::TAB_EVENT:
		break;
	}
	m_vecDialog[iSel]->ShowWindow(SW_SHOW);
#pragma endregion

}


void CMyFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Engine::_tchar szItemName[][256] = { L"Terrain", L"StaticMesh", L"DynamicMesh", L"Effect", L"Event" };
	m_iSize = sizeof(szItemName) / sizeof(szItemName[0]);

	for (int i = 0; i < m_iSize; ++i)
	{
		m_TabCtrl.InsertItem(i, szItemName[i]);
	}

	m_TabCtrl.SetCurSel(0);

	const int iWidth = 400;
	const int iHeight = 600;
	const int iStartX = 0;
	const int iStartY = 25;

	m_pTerrainTab = new CTerrainTab(this);
	m_pTerrainTab->Create(IDD_TERRAIN_DLG, &m_TabCtrl);
	m_pTerrainTab->MoveWindow(iStartX, iStartY, iWidth, iHeight);
	m_pTerrainTab->ShowWindow(SW_SHOW);

	m_vecDialog.push_back(m_pTerrainTab);

	m_pStaticMeshTab = new CStaticMeshTab(this);
	m_pStaticMeshTab->Create(IDD_MESH_DLG, &m_TabCtrl);
	m_pStaticMeshTab->MoveWindow(iStartX, iStartY, iWidth, iHeight);
	m_pStaticMeshTab->ShowWindow(SW_HIDE);

	m_vecDialog.push_back(m_pStaticMeshTab);

	m_pDynamicMeshTab = new CDyMeshTab(this);
	m_pDynamicMeshTab->Create(IDD_DYNAMIC_MESH_DLG, &m_TabCtrl);
	m_pDynamicMeshTab->MoveWindow(iStartX, iStartY, iWidth, iHeight);
	m_pDynamicMeshTab->ShowWindow(SW_HIDE);

	m_vecDialog.push_back(m_pDynamicMeshTab);

	m_pDataTab = new CDataTab(this);
	m_pDataTab->Create(IDD_DATA_TAB, &m_TabCtrl);
	m_pDataTab->MoveWindow(iStartX, iStartY, iWidth, iHeight);
	m_pDataTab->ShowWindow(SW_HIDE);

	m_vecDialog.push_back(m_pDataTab);

	m_pEffectTab = new CEffectTab(this);
	m_pEffectTab->Create(IDD_EFFECT_DLG, &m_TabCtrl);
	m_pEffectTab->MoveWindow(iStartX, iStartY, iWidth, iHeight);
	m_pEffectTab->ShowWindow(SW_HIDE);

	m_vecDialog.push_back(m_pEffectTab);

}
