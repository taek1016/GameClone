#include "stdafx.h"
#include "FinalStaff.h"

USING(Engine)

CFinalStaff::CFinalStaff(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWeaponBase(pGraphicDev)
{
	set_Name(L"FinalStaff");
}

CFinalStaff::CFinalStaff(const CFinalStaff & rhs)
	: CWeaponBase(rhs)
{
}

CFinalStaff * CFinalStaff::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFinalStaff* pInstance = new CFinalStaff(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

Engine::CGameObject * CFinalStaff::Clone(void)
{
	CFinalStaff* pInstance = new CFinalStaff(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
