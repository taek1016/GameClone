#include "stdafx.h"
#include "NefarianFLFoot.h"

USING(Engine)

CNefarianFLFoot::CNefarianFLFoot(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWeaponBase(pGraphicDev)
{
	Set_Damage(20);
}

CNefarianFLFoot::CNefarianFLFoot(const CNefarianFLFoot & rhs)
	: CWeaponBase(rhs)
{
}

HRESULT CNefarianFLFoot::Late_Initialize(void)
{
	CWeaponBase::Late_Initialize();

	initialize_Colliders(3.f, 3.f);

	return S_OK;
}

void CNefarianFLFoot::attack(void)
{
	CWeaponBase::attack();

	DLL::pSoundMgr->PlaySound(L"NefarianAttack.wav", CSoundMgr::MONSTER);
	DLL::pSoundMgr->SetVolume(CSoundMgr::MONSTER, 0.3f);

}

CNefarianFLFoot * CNefarianFLFoot::Create(LPDIRECT3DDEVICE9 pGraphicDev, CCharacterBase* pTarget)
{
	CNefarianFLFoot* pInstance = new CNefarianFLFoot(pGraphicDev);

	pInstance->Set_Target(pTarget);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	pInstance->Late_Initialize();
	return pInstance;
}

Engine::CGameObject * CNefarianFLFoot::Clone(void)
{
	CNefarianFLFoot* pInstance = new CNefarianFLFoot(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
