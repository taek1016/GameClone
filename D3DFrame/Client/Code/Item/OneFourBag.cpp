#include "stdafx.h"
#include "OneFourBag.h"

USING(Engine)
COneFourBag::COneFourBag(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBagBase(pGraphicDev)
{
	set_Name(L"BagOneFour");
}

COneFourBag * COneFourBag::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	COneFourBag* pInstance = new COneFourBag(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}

	pInstance->set_ItemSlots(1, 4);
	pInstance->make_ItemSlot(pPos, pScale, 186.f, 93.f);

	return pInstance;
}
