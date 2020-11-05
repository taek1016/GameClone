#include "stdafx.h"
#include "DoomguardSword.h"

USING(Engine)

CDoomguardSword::CDoomguardSword(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWeaponBase(pGraphicDev)
{
	set_Name(L"DoomguardSword");
	Set_Damage(8);
}

CDoomguardSword::CDoomguardSword(const CDoomguardSword & rhs)
	: CWeaponBase(rhs)
{
}

HRESULT CDoomguardSword::Late_Initialize(void)
{
	CWeaponBase::Late_Initialize();

	initialize_Colliders(2.f, 2.f);

	m_pTransform->Set_Angle(&_vec3(D3DXToRadian(180.f), 0.f, 0.f));
	const _float fScaleValue = 1.5f;
	m_pTransform->Set_Scale(&_vec3(fScaleValue, fScaleValue, fScaleValue));
	return S_OK;
}

Engine::_bool CDoomguardSword::check_Collide(void)
{
	_bool bIsCollided = false;

	for (auto iter : m_listCollider)
	{
		if (CollideFunc::ActionColToPlayer(iter, DLL::pObjMgr->Get_ObjList(L"Player")->front()))
		{
			bIsCollided = true;
			break;
		}
	}

	return bIsCollided;
}

void CDoomguardSword::attack(void)
{
	CWeaponBase::attack();

	DLL::pSoundMgr->PlaySound(L"DoomguardAttack.wav", CSoundMgr::MONSTER);
	DLL::pSoundMgr->SetVolume(CSoundMgr::MONSTER, 0.3f);

}

CDoomguardSword * CDoomguardSword::Create(LPDIRECT3DDEVICE9 pGraphicDev, CCharacterBase * pTarget)
{
	CDoomguardSword* pInstance = new CDoomguardSword(pGraphicDev);

	pInstance->Set_Target(pTarget);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	pInstance->Late_Initialize();
	return pInstance;
}

Engine::CGameObject * CDoomguardSword::Clone(void)
{
	CDoomguardSword* pInstance = new CDoomguardSword(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
