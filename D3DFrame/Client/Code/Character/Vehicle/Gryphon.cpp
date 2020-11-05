#include "stdafx.h"
#include "Gryphon.h"

USING(Engine)

CGryphon::CGryphon(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFlyVehicle(pGraphicDev)
{
	set_Name(L"Gryphon");
	set_SeatBoneName("gryphon_armoredmount_Bone59");
}

CGryphon::CGryphon(const CGryphon & rhs)
	: CFlyVehicle(rhs)
{
}

CGryphon * CGryphon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGryphon* pInstance = new CGryphon(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CGryphon::Clone(void)
{
	CGryphon* pInstance = new CGryphon(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
