
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "MainFrm.h"
#include "ToolDoc.h"
#include "ToolView.h"

#include "Object/ToolTerrain.h"
#include "Object/ToolCamera.h"
#include "Object/NaviObject.h"
#include "Object/ToolStaticObject.h"
#include "Object/GuideLine.h"
#include "Tool/StaticMeshTool.h"
#include "View/DynamicObjControlTool.h"

#include "View/PrefabDlg.h"
#include "View/MyFormView.h"

HWND		g_hWnd;

// CToolView
USING(Engine)

IMPLEMENT_DYNCREATE(CToolView, CView)

BEGIN_MESSAGE_MAP(CToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
	: m_pTerrainTool(nullptr)
	, m_pStaticMeshTool(nullptr)
	, m_pDynamicObjTool(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
	DLL::Destroy_DLL();
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


}


// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


void CToolView::Deactivate_Tool(void)
{
	m_pTerrainTool->DeActivate();
	m_pStaticMeshTool->DeActivate();
	m_pDynamicObjTool->Deactivate();
}

void CToolView::OnInitialUpdate()
{
	const Engine::_tchar* pCaption = L"ToolView_OnInitializeUpdate";
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	g_hWnd = m_hWnd;

	CMainFrame*	pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	if (nullptr == pFrameWnd)
	{
		MessageBox(L"pFrameWnd in ToolView OnInitializeUpdate function is null", pCaption);
	}

#pragma region SetupWindowSize
	RECT rcFrame{};

	pFrameWnd->GetWindowRect(&rcFrame);
	::SetRect(&rcFrame, 0, 0, rcFrame.right - rcFrame.left, rcFrame.bottom - rcFrame.top);

	RECT rcView = {};

	// �������� Ŭ���̾�Ʈ ����(�׵θ��� �������� ����) ũ�� ������ �Լ�. (Ŭ���̾�Ʈ ��ǥ ����)
	GetClientRect(&rcView);

	// ���� ������������� View ������ ������ ���Ѵ�.
	int iGapX = rcFrame.right - rcView.right;
	int iGapY = rcFrame.bottom - rcView.bottom;

	// �������������� ũ�⸦ ���� ����.
	const int iWinCX = 800;
	const int iWinCY = 600;
	pFrameWnd->SetWindowPos(nullptr, 0, 0, iWinCX + iGapX, iWinCY + iGapY, SWP_NOZORDER | SWP_NOMOVE);
#pragma endregion

#pragma region CallDLLInitialize
	HRESULT hr = DLL::Initialize_DLL(g_hWnd, Engine::MODE_WIN, iWinCX, iWinCY);
	if (FAILED(hr))
	{
		MessageBox(L"Initialize_DLL is failed", pCaption);
	}
#pragma endregion

#pragma region Initialize_Mgrs
	DLL::pTimerMgr->Initialize_Timer(TIMER_ENUM::TIMER_END);
	DLL::pFrameMgr->Initialize_Frame(FRAME_ENUM::FPS_END);

	DLL::pTimerMgr->Ready_Timer(TIMER_ENUM::TIMER_IMMEDIATE);
	DLL::pTimerMgr->Ready_Timer(TIMER_ENUM::TIMER_60FPS);
	DLL::pFrameMgr->Ready_Frame(FRAME_ENUM::FRAME_60, 60.f);

	DLL::pCameraMgr->Initialize_CameraMgr(1);
	DLL::pCameraMgr->Add_Camera<CToolCamera>(0, D3DXToRadian(90.f), 800.f / 600.f, 0.01f, 1000.f);
	DLL::pCameraMgr->Set_CurCamera(0);

	Engine::_vec3	vEye(0.f, 3.f, -3.f);
	Engine::_vec3	vAt(0.f, 0.f, 0.f);
	Engine::_vec3	vUp(0.f, 1.f, 0.f);

	DLL::pCameraMgr->Late_Initialize(&vEye, &vAt, &vUp);

	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	DLL::pInputMgr->Initialize_InputDev(::AfxGetInstanceHandle(), g_hWnd);
	DLL::pCalculate->Initialize_Calculate(pGraphicDev, g_hWnd, 800, 600);
	DLL::Intialize_Renderer(pGraphicDev);
#pragma endregion

#pragma region InitializeResourcesMgr
	DLL::pResourcesMgr->Reserve_ContainerSize(1);
#pragma endregion

#pragma region FindPath
	DLL::pDataMgr->Load_Mesh_Path();
	DLL::pDataMgr->Load_Texture_Path();
#pragma endregion

#pragma region InitializeToolContainer
	CMyFormView*	pFormView = dynamic_cast<CMyFormView*>(pFrameWnd->Get_Main()->GetPane(0, 0));
	pFormView->Initialize_FormView();

	m_pTerrainTool = DLL::pToolContainer->Get_Tool<CTerrainTool>(L"TerrainTool");
	m_pStaticMeshTool = DLL::pToolContainer->Get_Tool<CStaticMeshTool>(L"StaticMeshTool");
#pragma endregion

#pragma region Add_Default_Objects
	CToolTerrain* pTerrain = CToolTerrain::Create();
	pTerrain->Set_TerrainTool(m_pTerrainTool);
	DLL::pObjMgr->Add_ObjList(L"Terrain", L"Terrain", pTerrain);
#pragma endregion

	pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	DLL::pObjMgr->Add_ObjList(L"GuideLine", L"GuideLine", CGuideLine::Create(pGraphicDev, DLL::pGraphicDev->GetLine(), 10.f));

	m_pTerrainTool->Initialize_MapMeshes();
	m_pTerrainTool->Activate();

#pragma region Initialize_Light
	D3DLIGHT9			tLightInfo;
	ZeroMemory(&tLightInfo, sizeof(D3DLIGHT9));

	tLightInfo.Type = D3DLIGHT_DIRECTIONAL;

	tLightInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f);
	tLightInfo.Direction = _vec3(1.f, -1.f, 1.f);

	DLL::pLightMgr->Initialize_Light(pGraphicDev, &tLightInfo, 0);


	tLightInfo.Type = D3DLIGHT_POINT;

	tLightInfo.Diffuse = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	tLightInfo.Specular = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	tLightInfo.Ambient = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	tLightInfo.Position = _vec3(10.f, 2.f, 10.f);
	tLightInfo.Range = 3.f;

	DLL::pLightMgr->Initialize_Light(pGraphicDev, &tLightInfo, 1);


	tLightInfo.Type = D3DLIGHT_POINT;

	tLightInfo.Diffuse = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	tLightInfo.Specular = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	tLightInfo.Ambient = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	tLightInfo.Position = _vec3(30.f, 5.f, 10.f);
	tLightInfo.Range = 3.f;

	DLL::pLightMgr->Initialize_Light(pGraphicDev, &tLightInfo, 2);
#pragma endregion

}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_pTerrainTool->GetActivate())
	{
		m_pTerrainTool->Act();
	}

	if (nullptr == m_pStaticMeshTool)
	{
		m_pStaticMeshTool = DLL::pToolContainer->Get_Tool<CStaticMeshTool>(L"StaticMeshTool");
	}
	else if (m_pStaticMeshTool->GetActivated())
	{
		m_pStaticMeshTool->KeyInput();
	}

	if (nullptr == m_pDynamicObjTool)
	{
		m_pDynamicObjTool = DLL::pToolContainer->Get_Tool<CDynamicObjTool>(L"MonsterTool");
	}
	else if (m_pDynamicObjTool->Get_Activated())
	{
		m_pDynamicObjTool->KeyInput();
	}


	CView::OnLButtonDown(nFlags, point);
}
