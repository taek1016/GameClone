#include "stdafx.h"
#include "InfernalDeath.h"

USING(Engine)

CInfernalDeathEffect::CInfernalDeathEffect(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMeshEffectBase(pGraphicDev)
{
	set_Name(L"InfernalDeath");
}

CInfernalDeathEffect::CInfernalDeathEffect(const CInfernalDeathEffect & rhs)
	: CMeshEffectBase(rhs)
{
}

void CInfernalDeathEffect::Ready_ToGo(void)
{
	m_bDead = false;
}

void CInfernalDeathEffect::act_Determine(const Engine::_float & fTimeDelta)
{

}

CInfernalDeathEffect * CInfernalDeathEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CInfernalDeathEffect* pInstance = new CInfernalDeathEffect(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	
	pInstance->Late_Initialize();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CInfernalDeathEffect::Clone(void)
{
	CInfernalDeathEffect* pInstance = new CInfernalDeathEffect(*this);

	pInstance->Late_Initialize();

	return pInstance;
}