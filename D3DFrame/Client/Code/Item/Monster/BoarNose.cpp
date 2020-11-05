#include "stdafx.h"
#include "BoarNose.h"

USING(Engine)

CBoarNose::CBoarNose(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWeaponBase(pGraphicDev)
{
	Set_Damage(3);
}

CBoarNose::CBoarNose(const CBoarNose& rhs)
	: CWeaponBase(rhs)
{
}

CBoarNose::~CBoarNose(void)
{
}

HRESULT CBoarNose::Late_Initialize(void)
{
	CWeaponBase::Late_Initialize();

	initialize_Colliders(3.f, 3.f);

	return S_OK;
}

Engine::_bool CBoarNose::check_Collide(void)
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

void CBoarNose::attack(void)
{
	CWeaponBase::attack();

	DLL::pSoundMgr->PlaySound(L"BoarAttack.wav", CSoundMgr::MONSTER);
	DLL::pSoundMgr->SetVolume(CSoundMgr::MONSTER, 0.3f);
}

CBoarNose * CBoarNose::Create(LPDIRECT3DDEVICE9 pGraphicDev, CCharacterBase* pTarget)
{
	CBoarNose* pInstance = new CBoarNose(pGraphicDev);

	pInstance->Set_Target(pTarget);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	pInstance->Late_Initialize();
	return pInstance;
}

Engine::CGameObject * CBoarNose::Clone(void)
{
	CBoarNose* pInstance = new CBoarNose(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
