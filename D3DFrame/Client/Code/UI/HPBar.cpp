#include "stdafx.h"
#include "HPBar.h"

USING(Engine)

CHPBar::CHPBar(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_vStartPos(0.f, 0.f, 0.f)
	, m_vMaxScale(0.f, 0.f, 0.f)
	, m_pTargetStat(nullptr)
{
	set_Name(L"HPBar");
}

CHPBar::~CHPBar(void)
{
}

HRESULT CHPBar::Set_Target(Engine::CGameObject * pObj)
{
	CUIBase::Set_Target(pObj);

	if (nullptr != m_pTargetStat)
	{
		Safe_Release(m_pTargetStat);
	}

	m_pTargetStat = m_pTarget->Get_Component<CStatCom>(L"Stat", ID_STATIC);
	if (nullptr != m_pTargetStat)
	{
		m_pTargetStat->AddRef();
	}
	return S_OK;
}

Engine::_int CHPBar::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (nullptr != m_pTarget)
	{
		ZeroMemory(m_szHP, sizeof(_tchar) * 32);
		auto pHPInfo = &m_pTargetStat->Get_HP();
		wsprintf(m_szHP, L"%d / %d", pHPInfo->iHP, pHPInfo->iMaxHP);

		_vec3 vPos = m_vStartPos;
		_vec3 vScale(10.f, m_vMaxScale.y - 5.f, 1.f);
		vPos.x -= lstrlen(m_szHP) * vScale.x * 0.5f;

		DLL::pFontMgr->Print_Font(&vPos, &vScale, 30, m_szHP);
	}
	DLL::pRenderer->Add_RenderGroup(RENDERID::RENDER_UI, this);

	return 0;
}

void CHPBar::Calculate_HPBar(void)
{
}

HRESULT CHPBar::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	_matrix			matWorld, matView, matProj;

	_matrix matScale, matTrans;
	auto pScale = m_pTransform->Get_Scale();
	auto pPos = m_pTransform->Get_Info(INFO_POS);

	_float fHPPercent = m_pTargetStat->Get_HPPercent();

	D3DXMatrixScaling(&matScale, pScale->x * (fHPPercent), pScale->y, pScale->z);
	D3DXMatrixTranslation(&matTrans, pPos->x - pScale->x * (1.f - fHPPercent) * 0.5f, pPos->y, pPos->z);

	matWorld = matScale * matTrans;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	m_pTexture->Set_Texture(pEffect, "g_BaseTexture", (_uint)0);

	return S_OK;
}

void CHPBar::set_DefaultData(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	m_vStartPos = *pPos;
	m_vMaxScale = *pScale;
}

CHPBar * CHPBar::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CHPBar* pInstance = new CHPBar(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->Get_Name())))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_InitializeUI(pPos, pScale)))
	{
		Safe_Release(pInstance);
	}

	pInstance->set_DefaultData(pPos, pScale);

	return pInstance;
}

Engine::CGameObject * CHPBar::Clone(void)
{
	return nullptr;
}

inline void CHPBar::Free(void)
{
	CUIBase::Free();
	Safe_Release(m_pTargetStat);
}
