#include "stdafx.h"
#include "DefaultStaff.h"

USING(Engine)

CDefaultStaff::CDefaultStaff(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWeaponBase(pGraphicDev)
{
	set_Name(L"DefaultStaff");
}

CDefaultStaff::CDefaultStaff(const CDefaultStaff & rhs)
	: CWeaponBase(rhs)
{
}

CDefaultStaff * CDefaultStaff::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDefaultStaff* pInstance = new CDefaultStaff(pGraphicDev);

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

Engine::CGameObject * CDefaultStaff::Clone(void)
{
	CDefaultStaff* pInstance = new CDefaultStaff(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
