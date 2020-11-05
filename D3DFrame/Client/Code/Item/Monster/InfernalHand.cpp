#include "stdafx.h"
#include "InfernalHand.h"

USING(Engine)

CInfernalHand::CInfernalHand(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWeaponBase(pGraphicDev)
{
	Set_Damage(10);
}

CInfernalHand::CInfernalHand(const CInfernalHand & rhs)
	: CWeaponBase(rhs)
{
}

HRESULT CInfernalHand::Late_Initialize(void)
{
	CWeaponBase::Late_Initialize();

	initialize_Colliders(4.f, 4.f);

	return S_OK;
}

void CInfernalHand::attack(void)
{
	CWeaponBase::attack();

	DLL::pSoundMgr->PlaySound(L"InfernalAttack.wav", CSoundMgr::MONSTER);
	DLL::pSoundMgr->SetVolume(CSoundMgr::MONSTER, 0.3f);
}


CInfernalHand * CInfernalHand::Create(LPDIRECT3DDEVICE9 pGraphicDev, CCharacterBase * pTarget)
{
	CInfernalHand* pInstance = new CInfernalHand(pGraphicDev);

	pInstance->Set_Target(pTarget);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	pInstance->Late_Initialize();
	return pInstance;
}

Engine::CGameObject * CInfernalHand::Clone(void)
{
	CInfernalHand* pInstance = new CInfernalHand(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
