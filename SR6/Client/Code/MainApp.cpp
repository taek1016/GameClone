#include "stdafx.h"
#include "MainApp.h"

#include "Scene/Logo.h"

CMainApp::CMainApp(void)
{
}

CMainApp::~CMainApp(void)
{
}

HRESULT CMainApp::Ready_MainApp(void)
{
	DLL::pCameraMgr->Initialize_CameraMgr(CAMERA_ENUM::CAMERA_END);
	DLL::pDirectInput->Initialize_InputDev(g_hInst, g_hWnd);
	DLL::pMouseMgr->Initialize_MouseMgr(MOUSE_ENUM::MOUSE_END, g_hWnd);

	FAILED_CHECK_RETURN(Initialize_DefaultSetting(), E_FAIL);
	FAILED_CHECK_RETURN(Initialize_Scene(), E_FAIL);

	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	DLL::pRenderer->Set_GraphicDev(DLL::pGraphicDev->GetDevice());
	DLL::pRenderer->Set_Window(WINCX, WINCY);
	return S_OK;
}

Engine::_int CMainApp::Update_MainApp(const Engine::_float fTimeDelta)
{
	DLL::pDirectInput->Set_InputDev();

	if (nullptr != DLL::pManagement)
	{
		DLL::pManagement->Update_Scene(fTimeDelta);
	}

	return 0;
}

void CMainApp::Render_MainApp(void)
{
	if (m_iExit == -1)
	{
		return;
	}

	DLL::pGraphicDev->Render_Begin(BACK_BUFFER_BLUE_L);

	DLL::pManagement->Render_Scene();
	DLL::pRenderer->Render_GameObject();

	DLL::pGraphicDev->Render_End();
}

HRESULT CMainApp::Initialize_DefaultSetting(void)
{
	FAILED_CHECK_RETURN
	(
		DLL::pGraphicDev->Ready_GraphicDev
		(
			g_hWnd, Engine::WINMODE::MODE_WIN, 
			WINCX, WINCY
		), 
		E_FAIL
	);
	
	return S_OK;
}

HRESULT CMainApp::Initialize_Scene(void)
{
	DLL::pManagement->SetUp_Scene<CLogo>();
	
	return S_OK;
}

CMainApp* CMainApp::Create(void)
{
	CMainApp* pInstance = new CMainApp();

	if (FAILED(pInstance->Ready_MainApp()))
	{
		Engine::Safe_Release(pInstance);
	}

	return pInstance;
}

void CMainApp::freeMem(void)
{

}
