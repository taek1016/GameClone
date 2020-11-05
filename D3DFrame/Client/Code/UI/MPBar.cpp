#include "stdafx.h"
#include "MPBar.h"

USING(Engine)

CMPBar::CMPBar(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_vMaxScale(0.f, 0.f, 0.f)
	, m_vStartPos(0.f, 0.f, 0.f)
	, m_pTargetStat(nullptr)
{
	set_Name(L"MPBar");
}

CMPBar::~CMPBar(void)
{
}

HRESULT CMPBar::Set_Target(Engine::CGameObject * pObj)
{
	CUIBase::Set_Target(pObj);

	if (nullptr != m_pTargetStat)
	{
		Safe_Release(m_pTargetStat);
	}

	m_pTargetStat = m_pTarget->Get_Component<CStatCom>(L"Stat", ID_STATIC);
	m_pTargetStat->AddRef();

	return S_OK;
}

Engine::_int CMPBar::Update_GameObject(const Engine::_float & fTimeDelta)
{
	ZeroMemory(m_szMP, sizeof(_tchar) * 32);
	auto pHPInfo = &m_pTargetStat->Get_MP();
	wsprintf(m_szMP, L"%d / %d", pHPInfo->iMP, pHPInfo->iMaxMP);

	_vec3 vPos = m_vStartPos;
	_vec3 vScale(10.f, m_vMaxScale.y - 5.f, 1.f);
	vPos.x -= lstrlen(m_szMP) * vScale.x * 0.5f;

	DLL::pFontMgr->Print_Font(&vPos, &vScale, 30, m_szMP);

	DLL::pRenderer->Add_RenderGroup(RENDERID::RENDER_UI, this);

	return 0;
}

void CMPBar::Calculate_MPBar(void)
{
}

HRESULT CMPBar::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	_matrix			matWorld, matView, matProj;

	_matrix matScale, matTrans;
	auto pScale = m_pTransform->Get_Scale();
	auto pPos = m_pTransform->Get_Info(INFO_POS);

	_float fMPPercent = m_pTargetStat->Get_MPPercent();

	D3DXMatrixScaling(&matScale, pScale->x * (fMPPercent), pScale->y, pScale->z);
	D3DXMatrixTranslation(&matTrans, pPos->x - pScale->x * (1.f - fMPPercent) * 0.5f, pPos->y, pPos->z);

	matWorld = matScale * matTrans;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	m_pTexture->Set_Texture(pEffect, "g_BaseTexture", (_uint)0);

	return S_OK;
}

void CMPBar::set_DefaultData(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	m_vStartPos = *pPos;
	m_vMaxScale = *pScale;
}

CMPBar * CMPBar::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CMPBar* pInstance = new CMPBar(pGraphicDev);

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

Engine::CGameObject * CMPBar::Clone(void)
{
	return nullptr;
}

inline void CMPBar::Free(void)
{
	CUIBase::Free();
	Safe_Release(m_pTargetStat);
}
