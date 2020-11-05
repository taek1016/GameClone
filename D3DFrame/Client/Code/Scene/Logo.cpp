#include "stdafx.h"
#include "Logo.h"

#include "LoadingThread.h"

#include "Scene\Menu.h"

#include "UI\Background.h"
#include "UI\LoadingBar.h"

USING(Engine)

CLogo::CLogo(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev)
	, m_pLoading(nullptr)
	, m_pBackground(nullptr)
{
}

CLogo::~CLogo(void)
{
}

HRESULT CLogo::Initialize_Scene(void)
{
	DLL::pDataMgr->Load_SceneChanger();

	m_pLoading = CLoading::Create(LOADING_DATA);

	m_pBackground = CBackground::Create(m_pGraphicDev, L"BlackRockCaven");
	m_pLoadingBar = CLoadingBar::Create(m_pGraphicDev, m_pLoading);

	return S_OK;
}

_int CLogo::Update_Scene(const _float & fTimeDelta)
{
	if (true == m_pLoading->Get_Finish())
	{
		DLL::pManagement->SetUp_Scene<CMenu>(m_pGraphicDev);

		return -1;
	}

	m_pBackground->Update_GameObject(fTimeDelta);
	m_pLoadingBar->Update_GameObject(fTimeDelta);

	return 0;
}

void CLogo::Render_Scene(void)
{
	//DLL::pFontMgr->Render_Font(L"Font_Default", m_pLoading->Get_LoadString(), &_vec2(10.f, 10.f), D3DXCOLOR(1.f, 0.f, 0.f, 1.f));
}

CLogo* CLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLogo* pInstance = new CLogo(pGraphicDev);

	if (FAILED(pInstance->Initialize_Scene()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLogo::Free(void)
{
	CScene::Free();
	Safe_Release(m_pBackground);
}
