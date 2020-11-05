#include "stdafx.h"
#include "WaterElementalFist.h"

#include "Character/Character.h"

USING(Engine)

CWaterElementalFist::CWaterElementalFist(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWeaponBase(pGraphicDev)
{
	Set_Damage(20);
}

CWaterElementalFist::CWaterElementalFist(const CWaterElementalFist & rhs)
	: CWeaponBase(rhs)
{
}

HRESULT CWaterElementalFist::Late_Initialize(void)
{
	CWeaponBase::Late_Initialize();

	initialize_Colliders(3.f, 3.f);

	return S_OK;
}

Engine::_bool CWaterElementalFist::check_Collide(void)
{
	for (auto iter : m_listCollider)
	{
		if (CollideFunc::SphereToSphere(iter, m_pTarget->Get_Component<CSphereCollider>(L"MainSphereCol", ID_STATIC)))
		{
			return true;
		}
	}
	return false;
}

CWaterElementalFist * CWaterElementalFist::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWaterElementalFist* pInstance = new CWaterElementalFist(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	return pInstance;
}

Engine::CGameObject * CWaterElementalFist::Clone(void)
{
	CWaterElementalFist* pInstance = new CWaterElementalFist(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
