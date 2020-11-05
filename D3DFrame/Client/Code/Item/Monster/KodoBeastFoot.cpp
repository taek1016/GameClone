#include "stdafx.h"
#include "KodoBeastFoot.h"

USING(Engine)

CKodoBeastNose::CKodoBeastNose(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWeaponBase(pGraphicDev)
{
	Set_Damage(8);
}

CKodoBeastNose::CKodoBeastNose(const CKodoBeastNose & rhs)
	: CWeaponBase(rhs)
{
}

HRESULT CKodoBeastNose::Late_Initialize(void)
{
	CWeaponBase::Late_Initialize();

	initialize_Colliders(4.f, 4.f);

	return S_OK;
}

Engine::_bool CKodoBeastNose::check_Collide(void)
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

void CKodoBeastNose::attack(void)
{
	CWeaponBase::attack();

	DLL::pSoundMgr->PlaySound(L"KodoBeastAttack.wav", CSoundMgr::MONSTER);
	DLL::pSoundMgr->SetVolume(CSoundMgr::MONSTER, 0.3f);

}

CKodoBeastNose * CKodoBeastNose::Create(LPDIRECT3DDEVICE9 pGraphicDev, CCharacterBase * pTarget)
{
	CKodoBeastNose* pInstance = new CKodoBeastNose(pGraphicDev);

	pInstance->Set_Target(pTarget);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	pInstance->Late_Initialize();
	return pInstance;
}

Engine::CGameObject * CKodoBeastNose::Clone(void)
{
	CKodoBeastNose* pInstance = new CKodoBeastNose(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
