#include "stdafx.h"
#include "LoadingBar.h"

#include "LoadingThread.h"

USING(Engine)

CLoadBar::CLoadBar()
	: CUIBase()
{
}

CLoadBar::~CLoadBar()
{
}

Engine::_int CLoadBar::Update_GameObject(const Engine::_float& fTimeDelta)
{
	Engine::_int iExit = CGameObject::Update_GameObject(fTimeDelta);			//컴포넌트 를 담고 잇는 벡터를 순회 하는 코드이다

	// 290만큼 왔다갔다하게.
	m_fData = m_pLoading->Get_Percent();
	_float fMaxScaleX = 600.f;
	if (m_fData > 0.f)
	{
		m_vScale.x = fMaxScaleX * (m_fData);
	}
	else if (m_fData >= 1.f)
	{
		m_vScale.x = fMaxScaleX;
	}
	else
	{
		m_vScale.x = 0.f;
	}
	D3DXMatrixScaling(&m_matBarScale, m_vScale.x, m_vScale.y, m_vScale.z);

	fMaxScaleX *= 0.5f;
	m_vPos.x = -fMaxScaleX + m_fData * fMaxScaleX;
	D3DXMatrixTranslation(&m_matBarTranslate, m_vPos.x, m_vPos.y, m_vPos.z);

	DLL::pRenderer->Add_RenderGroup(Engine::RENDERID::RENDER_UI, this);

	return 0;
}

HRESULT CLoadBar::Late_Initialize()
{
	D3DXMatrixIdentity(&m_matBarTranslate);
	D3DXMatrixIdentity(&m_matBarScale);
	
	m_vPos = { -225.f, 275.f, 0.f };
	D3DXMatrixTranslation(&m_matBarTranslate, m_vPos.x, m_vPos.y, m_vPos.z);

	_matrix matBaseScale, matBaseTranslate;

	D3DXMatrixIdentity(&matBaseScale);
	D3DXMatrixIdentity(&matBaseTranslate);

	D3DXMatrixScaling(&matBaseScale, 600.f, 20.f, 1.f);
	D3DXMatrixTranslation(&matBaseTranslate, 0.f, -250.f, 0.f);

	m_matBaseWorld = matBaseScale * matBaseTranslate;

	// x값만 조정하면 되도록.
	m_vScale = _vec3(1.f, 20.f, 1.f);
	m_vPos = _vec3(-300.f, -250.f, 0.f);
	m_pTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_LOGO, L"LoadBar"));

	return S_OK;
}

void CLoadBar::Render_GameObject()
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	pGraphicDev->SetTransform(D3DTS_WORLD, &m_matBaseWorld);

	m_pTexture->Render_Texture(0);
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");

	pGraphicDev->SetTransform(D3DTS_WORLD, &(m_matBarScale * m_matBarTranslate));
	m_pTexture->Render_Texture(1);
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

CLoadBar * CLoadBar::Create(CLoading* pLoading)
{
	CLoadBar* pInstance = new CLoadBar;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	pInstance->m_pLoading = pLoading;

	return pInstance;
}

void CLoadBar::LoadData(HANDLE hFile)
{
}

CGameObject * CLoadBar::Clone(const _vec3 * pPos)
{
	return nullptr;
}