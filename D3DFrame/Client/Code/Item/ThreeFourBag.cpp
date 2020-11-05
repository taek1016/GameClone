#include "stdafx.h"
#include "ThreeFourBag.h"

USING(Engine)

CThreeFourBag::CThreeFourBag(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBagBase(pGraphicDev)
{
	set_Name(L"BagThreeFour");
}

CThreeFourBag * CThreeFourBag::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CThreeFourBag* pInstance = new CThreeFourBag(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}

	pInstance->set_ItemSlots(3, 4);
	pInstance->make_ItemSlot(pPos, pScale, 188.f, 176.f);

	return pInstance;
}
