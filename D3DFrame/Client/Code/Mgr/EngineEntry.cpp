#include "stdafx.h"
#include "EngineEntry.h"

#include "CollideFunc/CollideFunc.h"
#include "Shader.h"

USING(Engine)

CCameraMgr*			DLL::pCameraMgr			= nullptr;
CGraphicDev*		DLL::pGraphicDev		= nullptr;
CDirectInput*		DLL::pInputMgr			= nullptr;
CResourcesMgr*		DLL::pResourcesMgr		= nullptr;
CTimerMgr*			DLL::pTimerMgr			= nullptr;
CFrameMgr*			DLL::pFrameMgr			= nullptr;
CCalculateMgr*		DLL::pCalculate			= nullptr;
CManagement*		DLL::pManagement		= nullptr;
CRenderer*			DLL::pRenderer			= nullptr;
CFontMgr*			DLL::pFontMgr			= nullptr;
CObjectMgr*			DLL::pObjMgr			= nullptr;
COptimizationMgr*	DLL::pOptimizationMgr	= nullptr;
CRenderTargetMgr*	DLL::pRenderTarget		= nullptr;
CShaderMgr*			DLL::pShaderMgr			= nullptr;
CLightMgr*			DLL::pLightMgr			= nullptr;

// 클라이언트 매니저
CClientDataMgr*		DLL::pDataMgr		= nullptr;
CComponentMgr*		DLL::pComMgr		= nullptr;
CPickMgr*			DLL::pPickMgr		= nullptr;
CMouseManager*		DLL::pMouseMgr		= nullptr;
CUIMgr*				DLL::pUIMgr			= nullptr;

CSkillMgr*			DLL::pSkillMgr		= nullptr;
CInventoryMgr*		DLL::pInventory		= nullptr;
CItemMgr*			DLL::pItemMgr		= nullptr;
CQuestMgr*			DLL::pQuestMgr		= nullptr;
CEffectMgr*			DLL::pEffectMgr		= nullptr;

CSoundMgr*			DLL::pSoundMgr		= nullptr;

void DLL::Initialize_Quests(void)
{
	pQuestMgr->Add_HuntingQuest(L"Boar", 5, 2500);
	pQuestMgr->Add_HuntingQuest(L"KodoBeast", 1, 3000);
	pQuestMgr->Add_HuntingQuest(L"Nefarian", 1, 5000);
}

HRESULT DLL::Initialize_DLL(HWND hWnd, Engine::WINMODE eMode, const Engine::_uint& iSizeX, const Engine::_uint& iSizeY)
{
	FAILED_CHECK_RETURN(get_EngineInstances(), E_FAIL);
	FAILED_CHECK_RETURN(get_ClientInstances(), E_FAIL);

	//const Engine::_tchar* pCaption = L"DLL_Initialize_DLL";
	//HRESULT hr = pGraphicDev->Initialize_GraphicDev(hWnd, eMode, iSizeX, iSizeY);
	//if (FAILED(hr))
	//{
	//	MessageBox(hWnd, L"Initialize_GraphicDev is failed", pCaption, MB_OK);
	//	return E_FAIL;
	//}

	pResourcesMgr->Reserve_ContainerSize(RESOURCE_ID::RESOURCE_END);

	return S_OK;
}

void DLL::Destroy_DLL(void)
{
	Engine::Clear_Engine();
	destroy_ClientInstances();
}

void DLL::Initialize_Mouse(void)
{
	pMouseMgr = CMouseManager::GetInstance();
	pMouseMgr->Initialize_GameObject();
	pMouseMgr->Late_Initialize();
}

void DLL::Initialize_Renderer(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	get_RenderTarget(pGraphicDev);
	get_MultiRenderTarget(pGraphicDev);
	get_Shader(pGraphicDev);
}

HRESULT DLL::get_EngineInstances(void)
{
	pGraphicDev			= Ready_GraphicDev();
	pTimerMgr			= Ready_TimerMgr();
	pFrameMgr			= Ready_FrameMgr();
	pManagement			= Ready_Manager();
	pObjMgr				= Ready_ObjMgr();

	pInputMgr			= Ready_Input();
	pResourcesMgr		= Ready_ResourcesMgr();
	pCameraMgr			= Ready_Camera();
	pCalculate			= Ready_Calculator();
	pRenderer			= Ready_Renderer();

	pOptimizationMgr	= Ready_Optimization();
	pLightMgr			= Ready_Light();
	pShaderMgr			= Ready_Shader();
	pRenderTarget		= Ready_RenderTarget();

	return S_OK;
}

HRESULT DLL::get_ClientInstances(void)
{
	pDataMgr	= CClientDataMgr::GetInstance();
	pComMgr		= CComponentMgr::GetInstance();
	pPickMgr	= CPickMgr::GetInstance();
	pUIMgr		= CUIMgr::GetInstance();
	pSkillMgr	= CSkillMgr::GetInstance();

	pInventory	= CInventoryMgr::GetInstance();
	pItemMgr	= CItemMgr::GetInstance();
	pCameraMgr	= CCameraMgr::GetInstance();
	pFontMgr	= CFontMgr::GetInstance();
	pQuestMgr	= CQuestMgr::GetInstance();

	pEffectMgr	= CEffectMgr::GetInstance();
	pSoundMgr	= CSoundMgr::GetInstance();
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
	const _tchar* pShaderName[] = { L"Shader_Sample",  L"Shader_Terrain" , L"Shader_Mesh", L"Shader_Light", L"Shader_Blend", L"Shader_Effect", L"Shader_Liquid", L"Shader_Font" };

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

void DLL::destroy_ClientInstances(void)
{
	DESTROY_SINGLETON(pDataMgr);
	DESTROY_SINGLETON(pComMgr);
	DESTROY_SINGLETON(pPickMgr);
	DESTROY_SINGLETON(pMouseMgr);
	DESTROY_SINGLETON(pUIMgr);

	DESTROY_SINGLETON(pInventory);
	DESTROY_SINGLETON(pItemMgr);
	DESTROY_SINGLETON(pFontMgr);
	DESTROY_SINGLETON(pEffectMgr);
}
