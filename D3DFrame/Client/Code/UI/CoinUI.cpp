#include "stdafx.h"
#include "CoinUI.h"

#include "Coin/CoinBase.h"
#include "Coin/GoldCoin.h"
#include "Coin/SilverCoin.h"
#include "Coin/CooperCoin.h"

USING(Engine)

CCoinUI::CCoinUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_pCoins{ nullptr }
{
}

Engine::_int CCoinUI::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	for (_int i = 0; i < COIN_END; ++i)
	{
		m_pCoins[i]->Update_GameObject(fTimeDelta);
	}

	return iExit;
}

void CCoinUI::Set_Coins(Engine::_int & iMoney)
{
	for (_int i = 0; i < COIN_END; ++i)
	{
		m_pCoins[i]->Set_Coins(iMoney);
	}
}

void CCoinUI::make_Coins(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	_vec3 vPos, vScale;
	vPos = *pPos;
	vScale = *pScale;

	// 전체 코인 너비는 150, 높이는 10 픽셀

	const _float fHalf = 0.5f;
	const _float fTotalWidth = 150.f;
	const _float fTotalHeight = 10.f;

	vScale.x = 15.f / fTotalWidth * pScale->x;
	vPos.x -= pScale->x;
	m_pCoins[CCoinUI::COIN_ENUM::COIN_GOLD] = CGoldCoin::Create(m_pGraphicDev, &vPos, &vScale, m_iFontWidth, m_iFontHeight);

	vPos.x += 50.f / fTotalWidth * pScale->x;
	m_pCoins[CCoinUI::COIN_ENUM::COIN_SILVER] = CSilverCoin::Create(m_pGraphicDev, &vPos, &vScale, m_iFontWidth, m_iFontHeight);

	vPos.x += 50.f / fTotalWidth * pScale->x;
	m_pCoins[CCoinUI::COIN_ENUM::COIN_COOPER] = CCooperCoin::Create(m_pGraphicDev, &vPos, &vScale, m_iFontWidth, m_iFontHeight);
}

CCoinUI * CCoinUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CCoinUI* pInstance = new CCoinUI(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->Get_Name())))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_InitializeUI(pPos, pScale)))
	{
		Safe_Release(pInstance);
	}

	// make coins
	pInstance->make_Coins(pPos, pScale);

	return pInstance;
}

inline void CCoinUI::Free(void)
{
	CUIBase::Free();

	for (_int i = 0; i < COIN_END; ++i)
	{
		Safe_Release(m_pCoins[i]);
	}
}
