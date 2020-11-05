#include "stdafx.h"
#include "Chicken.h"

#include "Character/Player.h"

USING(Engine)

CChicken::CChicken(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWalkVehicle(pGraphicDev)
{
	set_Name(L"Chicken");
	set_SeatBoneName("chickenmount_Bone34");
}

CChicken::CChicken(const CChicken & rhs)
	: CWalkVehicle(rhs)
{
}

CChicken * CChicken::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CChicken* pInstance = new CChicken(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CChicken::Clone(void)
{
	CChicken* pInstance = new CChicken(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
