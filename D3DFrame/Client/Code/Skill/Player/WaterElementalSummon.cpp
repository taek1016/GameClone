#include "stdafx.h"
#include "WaterElementalSummon.h"

USING(Engine)

CWaterElementalSummon::CWaterElementalSummon(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSummonSkillBase(pGraphicDev)
{
	set_Name(L"");
}

CWaterElementalSummon::CWaterElementalSummon(const CWaterElementalSummon & rhs)
	: CSummonSkillBase(rhs)
{
}

Engine::_int CWaterElementalSummon::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	//m_pMesh->Play_Animation(fTimeDelta);

	return iExit;
}

CWaterElementalSummon * CWaterElementalSummon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWaterElementalSummon* pInstance = new CWaterElementalSummon(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CWaterElementalSummon::Clone(void)
{
	CWaterElementalSummon* pInstance = new CWaterElementalSummon(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
