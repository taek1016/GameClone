#include "stdafx.h"
#include "SceneChanger.h"

#include "LoadingThread.h"

#include "Scene/FieldStage.h"

USING(Engine)

CSceneChanger::CSceneChanger(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev)
	, m_pTexture(nullptr)
	, m_pBuffer(nullptr)
{
}

CSceneChanger::~CSceneChanger(void)
{
}

HRESULT CSceneChanger::Initialize_Scene(void)
{
	m_pBuffer = CRcTex::Create(m_pGraphicDev);

	D3DVIEWPORT9 tViewport;
	m_pGraphicDev->GetViewport(&tViewport);
	_vec3 vScale(static_cast<_float>(tViewport.Width), static_cast<_float>(tViewport.Height), 1.f);

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixScaling(&m_matWorld, vScale.x, vScale.y, vScale.z);

	return S_OK;
}

Engine::_int CSceneChanger::Update_Scene(const Engine::_float & fTimeDelta)
{
	if (true == m_pLoading->Get_Finish())
	{
		switch (m_eLoadingID)
		{
		case LOADING_FIELD:
			DLL::pManagement->SetUp_Scene<CFieldStage>(m_pGraphicDev);
			break;

		case LOADING_DUNGEON:

			break;
		}

		DLL::pRenderer->Clear_RenderGroup();
		return -1;
	}

	return 0;
}

void CSceneChanger::Render_Scene(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);

	m_pTexture->Render_Texture();
	m_pBuffer->Render_Buffer();
}

void CSceneChanger::SetUp_Scene(LOADINGID eID, const Engine::_tchar* pName)
{
	m_pLoading = CLoading::Create(eID);
	m_eLoadingID = eID;

	if (nullptr != m_pTexture)
	{
		Safe_Release(m_pTexture);
	}

	m_pTexture = DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, pName);
}

CSceneChanger * CSceneChanger::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSceneChanger* pInstance = new CSceneChanger(pGraphicDev);

	if (FAILED(pInstance->Initialize_Scene()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSceneChanger::Free(void)
{
	CScene::Free();
}