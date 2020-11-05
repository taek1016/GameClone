#include "stdafx.h"
#include "GryphonSummon.h"

USING(Engine)

CGryphonSummon::CGryphonSummon(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSummonVehicleBase(pGraphicDev)
{
	set_Name(L"Gryphon");
}

CGryphonSummon::CGryphonSummon(const CGryphonSummon & rhs)
	: CSummonVehicleBase(rhs)
{
}

void CGryphonSummon::summon_Effect(const Engine::_vec3 * pPos)
{
}

CGryphonSummon * CGryphonSummon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGryphonSummon* pInstance = new CGryphonSummon(pGraphicDev);


	return pInstance;
}

Engine::CGameObject * CGryphonSummon::Clone(void)
{
	CGryphonSummon* pInstance = new CGryphonSummon(*this);



	return pInstance;
}
