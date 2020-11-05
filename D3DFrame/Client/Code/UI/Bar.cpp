#include "stdafx.h"
#include "Bar.h"

USING(Engine)

CCoolTimeBar::CCoolTimeBar(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_fPercent(0.f)
{
	set_Name(L"Casting");
}

Engine::_int CCoolTimeBar::Update_GameObject(const Engine::_float & fTimeDelta)
{
	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return 0;
}

void CCoolTimeBar::Set_Percent(const Engine::_float & fPercent)
{
	m_fPercent = fPercent;
}

HRESULT CCoolTimeBar::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	_matrix			matWorld, matView, matProj;

	_matrix matScale, matTrans;
	auto pScale = m_pTransform->Get_Scale();
	auto pPos = m_pTransform->Get_Info(INFO_POS);

	D3DXMatrixScaling(&matScale, pScale->x * (m_fPercent), pScale->y, pScale->z);
	D3DXMatrixTranslation(&matTrans, pPos->x - pScale->x * (1.f - m_fPercent) * 0.5f, pPos->y, pPos->z);

	matWorld = matScale * matTrans;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	m_pTexture->Set_Texture(pEffect, "g_BaseTexture", (_uint)0);

	return S_OK;
}

void CCoolTimeBar::set_Vector(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	m_pTransform->Set_Info(INFO_POS, pPos);
	m_pTransform->Set_Scale(pScale);
}

CCoolTimeBar * CCoolTimeBar::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CCoolTimeBar* pInstance = new CCoolTimeBar(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->m_wStrName.c_str())))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_InitializeUI(pPos, pScale);

	return pInstance;
}
