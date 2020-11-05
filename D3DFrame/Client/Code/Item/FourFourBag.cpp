#include "stdafx.h"
#include "FourFourBag.h"

USING(Engine)

CFourFourBag::CFourFourBag(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBagBase(pGraphicDev)
{
	set_Name(L"BagFourFour");
}

CFourFourBag * CFourFourBag::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CFourFourBag* pInstance = new CFourFourBag(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}

	pInstance->set_ItemSlots(4, 4);
	pInstance->make_ItemSlot(pPos, pScale, 187.f, 216.f);

	return pInstance;
}
