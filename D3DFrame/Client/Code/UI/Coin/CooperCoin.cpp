#include "stdafx.h"
#include "CooperCoin.h"

USING(Engine)

CCooperCoin::CCooperCoin(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCoinBase(pGraphicDev)
{
	set_Name(L"CooperCoin");
}

void CCooperCoin::Set_Coins(Engine::_int& iRemainCoin)
{
	m_iCoinNum = iRemainCoin;
}

CCooperCoin * CCooperCoin::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_int & iFontWidth, const Engine::_int & iFontHeight)
{
	CCooperCoin* pInstance = new CCooperCoin(pGraphicDev);

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
