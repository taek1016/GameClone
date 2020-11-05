#include "stdafx.h"
#include "SilverCoin.h"

USING(Engine)

CSilverCoin::CSilverCoin(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCoinBase(pGraphicDev)
{
	set_Name(L"SilverCoin");
}

void CSilverCoin::Set_Coins(Engine::_int& iRemainCoin)
{
	const _int iRemainder = 100;

	m_iCoinNum = iRemainCoin / iRemainder;
	iRemainCoin = iRemainCoin % iRemainder;
}

CSilverCoin * CSilverCoin::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_int & iFontWidth, const Engine::_int & iFontHeight)
{
	CSilverCoin* pInstance = new CSilverCoin(pGraphicDev);

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
