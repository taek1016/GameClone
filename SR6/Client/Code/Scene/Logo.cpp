#include "stdafx.h"
#include "Logo.h"

#include "SceneObject/Player.h"
#include "Stage.h"
#include "LoadingThread.h"
#include "Title.h"
#include "LogoObject/BackGround.h"
#include "LogoObject/LoadingBar.h"

USING(Engine)

CLogo::CLogo(void)
{
}

CLogo::~CLogo(void)
{
}

HRESULT CLogo::Initialize_Scene(void)
{
	DLL::pCameraMgr->Initialize_CameraMgr(CAMERA_ENUM::CAMERA_END);
	DLL::pObjContainer->Initialize_Managers(LOGO_MAP::LOGO_END, LOGO_OBJ::LOGO_OBJ_END);

	FAILED_CHECK_RETURN(Initialize_GameObject(), E_FAIL);
	FAILED_CHECK_RETURN(Initialize_Resource(RESOURCE_END), E_FAIL);

	m_pLoading = CLoading::Create(LOADING_STAGE);
	NULL_CHECK_RETURN(m_pLoading, E_FAIL);

	m_pLoadBar = CLoadBar::Create(m_pLoading);
	m_pLoadBar->Late_Initialize();
	m_pBackGround = CBackGround::Create(L"BackLoading");

	return S_OK;
}

_int CLogo::Update_Scene(const Engine::_float& fTimeDelta)
{
	_int iExit = DLL::pObjMgr->Update_Objects(fTimeDelta);

	m_pBackGround->Update_GameObject(fTimeDelta);
	m_pLoadBar->Update_GameObject(fTimeDelta);

	if (true == m_pLoading->Get_Finish() )
	{
		FAILED_CHECK_RETURN(DLL::pManagement->SetUp_Scene<CTitle>(), E_FAIL);
		return -1;
	}

	return iExit;
}

void CLogo::Render_Scene(void)
{
}

HRESULT CLogo::Initialize_Resource(RESOURCEID eMAX)
{
	DLL::pResourceMgr->Reserve_ContainerSize(eMAX);

	DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_LOGO,
		L"BackLoading",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/Title/BackGround/LoadingThread.png"
	);

	DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_LOGO,
		L"LoadBar",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/Title/LoadingThreadBar/%d.png", 2
	);

	DLL::pResourceMgr->Initialize_Buffer(RESOURCE_STATIC,
		L"Buffer_RcTex",
		Engine::BUFFER_RCTEX);
	return S_OK;
}

HRESULT CLogo::Initialize_GameObject()
{
	DLL::pObjContainer->Initialize_Managers(LOGO_MAP::LOGO_END, LOGO_OBJ::LOGO_OBJ_END);

	return S_OK;
}

CLogo* CLogo::Create(void)
{
	CLogo* pInstance = new CLogo;

	if (FAILED(pInstance->Initialize_Scene()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLogo::freeMem(void)
{
	Engine::Safe_Release(m_pLoading);
	Safe_Release(m_pBackGround);
	Safe_Release(m_pLoadBar);
}
