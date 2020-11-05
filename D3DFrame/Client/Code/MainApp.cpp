#include "stdafx.h"
#include "MainApp.h"

#include "Scene/Logo.h"


USING(Engine)

CMainApp::CMainApp(void)
{
	initialize_DefaultSetting();
}

CMainApp::~CMainApp(void)
{
}

HRESULT CMainApp::Initialize_MainApp(void)
{

	DLL::pCameraMgr->Initialize_CameraMgr(CAMERA_ENUM::CAMERA_END);
	DLL::pInputMgr->Initialize_InputDev(g_hInst, g_hWnd);

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	DLL::pOptimizationMgr->Set_GraphicDev(m_pGraphicDev);

	DLL::pRenderer->Initialize_Renderer(DLL::pRenderTarget, DLL::pLightMgr, DLL::pShaderMgr, m_pGraphicDev);
	DLL::pRenderer->Set_Window(WINCX, WINCY);

	DLL::Initialize_Renderer(m_pGraphicDev);
	DLL::Initialize_Quests();
	DLL::pFontMgr->Create_Font(m_pGraphicDev, L"KOverwatch");

	FAILED_CHECK_RETURN(initialize_Scene(), E_FAIL);

	return S_OK;
}

Engine::_int CMainApp::Update_MainApp(const Engine::_float& fTimeDelta)
{
	DLL::pInputMgr->Set_InputDev();
	DLL::pPickMgr->Update_Debug();

	if (nullptr != DLL::pMouseMgr)
	{
		DLL::pMouseMgr->Update_GameObject(fTimeDelta);
	}

	if (nullptr != DLL::pManagement)
	{
		m_iExit = DLL::pManagement->Update_Scene(fTimeDelta);
	}

	if (nullptr != DLL::pUIMgr)
	{
		DLL::pUIMgr->Update_UI(fTimeDelta);
	}

	if (nullptr != DLL::pInventory)
	{
		DLL::pInventory->Update_Inventory(fTimeDelta);
	}

	if (nullptr != DLL::pQuestMgr)
	{
		DLL::pQuestMgr->Update_Quest();
	}

	if (nullptr != DLL::pFontMgr)
	{
		DLL::pFontMgr->Update_Font(fTimeDelta);
	}

	if (nullptr != DLL::pMouseMgr)
	{
		DLL::pMouseMgr->Late_Update();
	}

	if (nullptr != DLL::pSoundMgr)
	{
		DLL::pSoundMgr->UpdateSound();
	}

	return 0;
}

void CMainApp::Render_MainApp(void)
{
	if (m_iExit == -1)
	{
		return;
	}

	D3DXCOLOR tBackBuffer(80 / 255.f, 188 / 255.f, 223 / 255.f, 1.f);

	DLL::pGraphicDev->Render_Begin(tBackBuffer);

	DLL::pManagement->Render_Scene();
	DLL::pRenderer->Render_GameObject(g_bRenderDebug, m_pGraphicDev);

	DLL::pGraphicDev->Render_End();
}

HRESULT CMainApp::initialize_DefaultSetting(void)
{
	// 그래픽 장치 셋팅
	FAILED_CHECK_RETURN
	(
		DLL::pGraphicDev->Initialize_GraphicDev(
			g_hWnd, Engine::WINMODE::MODE_WIN,
			WINCX, WINCY
		),
		E_FAIL
	);

	m_pGraphicDev = DLL::pGraphicDev->GetDevice();
	m_pGraphicDev->AddRef();

	return S_OK;
}

HRESULT CMainApp::initialize_Scene(void)
{
	DLL::pManagement->SetUp_Scene<CLogo>(m_pGraphicDev);

	return S_OK;
}

CMainApp* CMainApp::Create(void)
{
	CMainApp* pInstance = new CMainApp();

	if (FAILED(pInstance->Initialize_MainApp()))
	{
		Engine::Safe_Release(pInstance);
	}

	return pInstance;
}

void CMainApp::Free(void)
{
	Engine::Safe_Release(m_pGraphicDev);
}
