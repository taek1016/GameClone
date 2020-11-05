#include "stdafx.h"
#include "EngineEntry.h"

#include "Shader.h"

USING(Engine)

CCameraMgr*			DLL::pCameraMgr = nullptr;
CToolObjMgr*		DLL::pObjMgr = nullptr;
CManagement*		DLL::pManagementMgr = nullptr;
CGraphicDev*		DLL::pGraphicDev = nullptr;
CDirectInput*		DLL::pInputMgr = nullptr;
CResourcesMgr*		DLL::pResourcesMgr = nullptr;
CTimerMgr*			DLL::pTimerMgr = nullptr;
CFrameMgr*			DLL::pFrameMgr = nullptr;
CCalculateMgr*		DLL::pCalculate = nullptr;
CToolContainer*		DLL::pToolContainer = nullptr;
CToolRenderer*		DLL::pToolRenderer = nullptr;
CDataMgr*			DLL::pDataMgr = nullptr;
CRenderTargetMgr*	DLL::pRenderTarget = nullptr;
CShaderMgr*			DLL::pShaderMgr = nullptr;
CLightMgr*			DLL::pLightMgr = nullptr;

HRESULT DLL::Initialize_DLL(HWND hWnd, Engine::WINMODE eMode, const Engine::_uint& iSizeX, const Engine::_uint& iSizeY)
{
	FAILED_CHECK_RETURN(Get_Instances(), E_FAIL);

	const Engine::_tchar* pCaption = L"DLL_Initialize_DLL";
	HRESULT hr = pGraphicDev->Initialize_GraphicDev(hWnd, eMode, iSizeX, iSizeY);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"Initialize_GraphicDev is failed", pCaption, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void DLL::Destroy_DLL(void)
{
	Engine::Clear_Engine();

	pToolContainer->DestroyInstance();
	pToolContainer = nullptr;

	pObjMgr->DestroyInstance();
	pObjMgr = nullptr;

	pToolRenderer->DestroyInstance();
	pToolRenderer = nullptr;

	pDataMgr->DestroyInstance();
	pDataMgr = nullptr;

}

void DLL::Intialize_Renderer(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	get_Shader(pGraphicDev);
	get_RenderTarget(pGraphicDev);
	get_MultiRenderTarget(pGraphicDev);
}

HRESULT DLL::Get_Instances(void)
{
	pManagementMgr	= Ready_Manager();
	pGraphicDev		= Ready_GraphicDev();
	pInputMgr		= Ready_Input();
	pResourcesMgr	= Ready_ResourcesMgr();
	pTimerMgr		= Ready_TimerMgr();
	pFrameMgr		= Ready_FrameMgr();
	pCameraMgr		= Ready_Camera();
	pCalculate		= Ready_Calculator();
	pShaderMgr		= Ready_Shader();
	pRenderTarget	= Ready_RenderTarget();
	pLightMgr		= Ready_Light();

	pObjMgr			= CToolObjMgr::GetInstance();
	pToolContainer	= CToolContainer::GetInstance();
	pToolRenderer	= CToolRenderer::GetInstance();
	pDataMgr		= CDataMgr::GetInstance();

	return S_OK;
}
HRESULT DLL::get_RenderTarget(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	D3DVIEWPORT9		ViewPort;
	pGraphicDev->GetViewport(&ViewPort);

	FAILED_CHECK_RETURN(pRenderTarget->Intiailize_RenderTarget(pGraphicDev, L"Target_Albedo", ViewPort.Width, ViewPort.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f)), E_FAIL);
	FAILED_CHECK_RETURN(pRenderTarget->Initialize_DebugBuffer(L"Target_Albedo", 0.f, 0.f, 200.f, 200.f), E_FAIL);

	FAILED_CHECK_RETURN(pRenderTarget->Intiailize_RenderTarget(pGraphicDev, L"Target_Normal", ViewPort.Width, ViewPort.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 1.f)), E_FAIL);
	FAILED_CHECK_RETURN(pRenderTarget->Initialize_DebugBuffer(L"Target_Normal", 0.f, 200.f, 200.f, 200.f), E_FAIL);

	FAILED_CHECK_RETURN(pRenderTarget->Intiailize_RenderTarget(pGraphicDev, L"Target_Light", ViewPort.Width, ViewPort.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 1.f)), E_FAIL);
	FAILED_CHECK_RETURN(pRenderTarget->Initialize_DebugBuffer(L"Target_Light", 200.f, 0.f, 200.f, 200.f), E_FAIL);

	FAILED_CHECK_RETURN(pRenderTarget->Intiailize_RenderTarget(pGraphicDev, L"Target_Specular", ViewPort.Width, ViewPort.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0.f, 0.f, 0.f, 0.f)), E_FAIL);
	FAILED_CHECK_RETURN(pRenderTarget->Initialize_DebugBuffer(L"Target_Specular", 200.f, 200.f, 200.f, 200.f), E_FAIL);

	FAILED_CHECK_RETURN(pRenderTarget->Intiailize_RenderTarget(pGraphicDev, L"Target_Depth", ViewPort.Width, ViewPort.Height, D3DFMT_A32B32G32R32F, D3DXCOLOR(1.f, 1.f, 1.f, 1.f)), E_FAIL);
	FAILED_CHECK_RETURN(pRenderTarget->Initialize_DebugBuffer(L"Target_Depth", 0.f, 400.f, 200.f, 200.f), E_FAIL);

	return S_OK;
}

HRESULT DLL::get_MultiRenderTarget(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	FAILED_CHECK_RETURN(pRenderTarget->Initialize_MRT(L"MRT_Defferd", L"Target_Albedo"), E_FAIL);
	FAILED_CHECK_RETURN(pRenderTarget->Initialize_MRT(L"MRT_Defferd", L"Target_Normal"), E_FAIL);
	FAILED_CHECK_RETURN(pRenderTarget->Initialize_MRT(L"MRT_Defferd", L"Target_Depth"), E_FAIL);

	FAILED_CHECK_RETURN(pRenderTarget->Initialize_MRT(L"MRT_LightAcc", L"Target_Light"), E_FAIL);
	FAILED_CHECK_RETURN(pRenderTarget->Initialize_MRT(L"MRT_LightAcc", L"Target_Specular"), E_FAIL);

	return S_OK;
}

HRESULT DLL::get_Shader(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	CShader*		pShader = nullptr;

	const _tchar* pDefaultShaderPath = L"../../Shaders/";
	const _tchar* pShaderName[] = { L"Shader_Sample",  L"Shader_Terrain" , L"Shader_Mesh", L"Shader_Light", L"Shader_Blend", L"Shader_Effect" };

	const _int iMaxStr = 256;
	_tchar szFileName[iMaxStr];

	const _int iSize = sizeof(pShaderName) / sizeof(pShaderName[0]);
	for (_int i = 0; i < iSize; ++i)
	{
		ZeroMemory(szFileName, sizeof(_tchar) * iMaxStr);
		lstrcpy(szFileName, pDefaultShaderPath);
		lstrcat(szFileName, pShaderName[i]);
		lstrcat(szFileName, L".hpp");

		pShader = CShader::Create(pGraphicDev, szFileName);
		NULL_CHECK_RETURN(pShader, E_FAIL);
		FAILED_CHECK_RETURN(pShaderMgr->Initialize_Shaders(pShaderName[i], pShader), E_FAIL);
	}

	return S_OK;

}