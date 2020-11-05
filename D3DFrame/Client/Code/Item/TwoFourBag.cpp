#include "stdafx.h"
#include "TwoFourBag.h"

USING(Engine)

CTwoFourBag::CTwoFourBag(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBagBase(pGraphicDev)
{
	set_Name(L"BagTwoFour");
}

CTwoFourBag * CTwoFourBag::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CTwoFourBag* pInstance = new CTwoFourBag(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}

	pInstance->set_ItemSlots(2, 4);
	pInstance->make_ItemSlot(pPos, pScale, 186.f, 134.f);

	return pInstance;
}
