#include "stdafx.h"
#include "CraftingUI.h"

USING(Engine)

CCraftingUI::CCraftingUI(void)
	: CGameObject()
{
	D3DXMatrixIdentity(&m_matBase);
	D3DXMatrixIdentity(&m_matBar);

	m_vPos = { 0.f, 0.f, 0.f };
	_matrix matBaseTrans, matBaseScale;
	D3DXMatrixTranslation(&matBaseTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	D3DXMatrixScaling(&matBaseScale, 320.f, 28.f, 1.f);
	D3DXMatrixTranslation(&matBaseTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	m_matBase = matBaseScale * matBaseTrans;
}

CCraftingUI::~CCraftingUI(void)
{
}

Engine::_int CCraftingUI::Update_GameObject(const _float & fTimeDelta)
{
	if (!m_bActivate)
	{
		return 0;
	}
	m_fCurPercent += fTimeDelta;

	_float fMaxScaleX = 290.f;

	if (m_fCurPercent >= 2.f)
	{
		m_vScale.x = fMaxScaleX;
		m_bFinished = true;
	}
	else if (m_fCurPercent > 0.f)
	{
		m_vScale.x = fMaxScaleX * m_fCurPercent;
	}
	else
	{
		m_vScale.x = 0.f;
	}

	_matrix matScale, matTrans;
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);

	m_vPos.x = 0.f + (1.f - m_fCurPercent * 0.5f) * fMaxScaleX * 0.5f;

	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	m_matBar = matScale * matTrans;
	DLL::pRenderer->Add_RenderGroup(RENDERID::RENDER_UI, this);

	return 0;
}

void CCraftingUI::Render_GameObject()
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	pGraphicDev->SetTransform(D3DTS_WORLD, &m_matBase);

	// 나중에 프로그래스 바로 바꾸기.
	m_pTexture->Render_Texture(0);
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");

	pGraphicDev->SetTransform(D3DTS_WORLD, &m_matBar);
	m_pTexture->Render_Texture(1);
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

void CCraftingUI::Set_Init()
{
	m_fCurPercent = 0.f;
	m_vScale = { 0.f, 10.f, 1.f };
	m_vPos = { 0.f, 0.f, 0.f };

	m_bFinished = false;
}

HRESULT CCraftingUI::Initialize_GameObject()
{
	Set_Init();
	m_pTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"Craft"));

	return S_OK;
}

CCraftingUI * CCraftingUI::Create(void)
{
	CCraftingUI* pInstance = new CCraftingUI;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CCraftingUI::Clone(const _vec3 * pPos)
{
	return nullptr;
}
