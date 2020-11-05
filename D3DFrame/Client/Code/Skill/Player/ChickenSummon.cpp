#include "stdafx.h"
#include "ChickenSummon.h"

USING(Engine)

CChickenSummon::CChickenSummon(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSummonVehicleBase(pGraphicDev)
{
	set_Name(L"Chicken");
}

CChickenSummon::CChickenSummon(const CChickenSummon & rhs)
	: CSummonVehicleBase(rhs)
{
}

void CChickenSummon::summon_Effect(const Engine::_vec3 * pPos)
{
}

CChickenSummon * CChickenSummon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CChickenSummon* pInstance = new CChickenSummon(pGraphicDev);



	return pInstance;
}

Engine::CGameObject * CChickenSummon::Clone(void)
{
	CChickenSummon* pInstance = new CChickenSummon(*this);



	return pInstance;
}
