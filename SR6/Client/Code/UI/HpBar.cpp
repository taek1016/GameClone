#include "stdafx.h"
#include "HpBar.h"

USING(Engine)

CHpBar::CHpBar()
	: CUIBase()
{
}

CHpBar::~CHpBar()
{
}

Engine::_int CHpBar::Update_GameObject(const Engine::_float & fTimeDelta)
{
	Engine::_int iExit = CGameObject::Update_GameObject(fTimeDelta);			//컴포넌트 를 담고 잇는 벡터를 순회 하는 코드이다

	// 290만큼 왔다갔다하게.
	_float fMaxScaleX = 290.f;
	if (m_fData > 0.f)
	{
		m_vScale.x = fMaxScaleX * m_fData;
	}
	else if (m_fData >= 1.f)
	{
		m_vScale.x = fMaxScaleX;
	}
	else
	{
		m_vScale.x = 0.f;
	}

	m_vPos.x = -225.f - (1 - m_fData) * fMaxScaleX * 0.5f;
	D3DXMatrixScaling(&m_matBarScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixTranslation(&m_matBarTranslate, m_vPos.x, m_vPos.y, m_vPos.z);

	DLL::pRenderer->Add_RenderGroup(Engine::RENDERID::RENDER_UI, this);

	return 0;
}

HRESULT CHpBar::Late_Initialize()
{
	D3DXMatrixIdentity(&m_matBarTranslate);
	D3DXMatrixIdentity(&m_matBarScale);
	
	m_vPos = { -225.f, 275.f, 0.f };
	D3DXMatrixTranslation(&m_matBarTranslate, m_vPos.x, m_vPos.y, m_vPos.z);

	_matrix matBaseScale, matBaseTranslate;

	D3DXMatrixIdentity(&matBaseScale);
	D3DXMatrixIdentity(&matBaseTranslate);

	D3DXMatrixScaling(&matBaseScale, 320.f, 28.f, 1.f);
	D3DXMatrixTranslation(&matBaseTranslate, -235.f, 275.f, 0.f);

	m_matBaseWorld = matBaseScale * matBaseTranslate;

	// x값만 조정하면 되도록.
	m_vScale = _vec3(1.f, 10.f, 1.f);

	return S_OK;
}

void CHpBar::Render_GameObject()
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	pGraphicDev->SetTransform(D3DTS_WORLD, &m_matBaseWorld);

	DLL::pResourceMgr->Render_Texture(RESOURCE_STAGE, L"HP1");
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");

	pGraphicDev->SetTransform(D3DTS_WORLD, &(m_matBarScale * m_matBarTranslate));
	DLL::pResourceMgr->Render_Texture(RESOURCE_STAGE, L"HP2");
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

CHpBar * CHpBar::Create(void)
{
	return new CHpBar;
}

void CHpBar::LoadData(HANDLE hFile)
{
}

CGameObject * CHpBar::Clone(const _vec3 * pPos)
{
	return nullptr;
}