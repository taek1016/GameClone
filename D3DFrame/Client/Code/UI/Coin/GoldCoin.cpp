#include "stdafx.h"
#include "GoldCoin.h"

USING(Engine)

CGoldCoin::CGoldCoin(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCoinBase(pGraphicDev)
{
	set_Name(L"GoldCoin");
}

void CGoldCoin::Set_Coins(Engine::_int& iRemainCoin)
{
	const _int iRemainder = 10000;

	m_iCoinNum = iRemainCoin / iRemainder;
	iRemainCoin = iRemainCoin % iRemainder;
}

CGoldCoin * CGoldCoin::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_int & iFontWidth, const Engine::_int & iFontHeight)
{
	CGoldCoin* pInstance = new CGoldCoin(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->Get_Name())))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_InitializeUI(pPos, pScale)))
	{
		Safe_Release(pInstance);
	}

	pInstance->set_FontSize(iFontWidth, iFontHeight);

	return pInstance;
}
