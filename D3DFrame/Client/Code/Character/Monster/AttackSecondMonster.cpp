#include "stdafx.h"
#include "AttackSecondMonster.h"

#include "Item/WeaponBase.h"

USING(Engine)

CAttackSecondMonster::CAttackSecondMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonsterBase(pGraphicDev)
{
}

CAttackSecondMonster::CAttackSecondMonster(const CAttackSecondMonster & rhs)
	: CMonsterBase(rhs)
{
}

void CAttackSecondMonster::act_Determine(const Engine::_float & fTimeDelta)
{
	Set_AnimationSet(L"Stand");

	if (m_pMesh->Is_AnimationSetEnd())
	{
		if (m_bMeleeAtt && m_pWeapon)
		{
			m_pWeapon->Cancel_Attack();
			m_bMeleeAtt = false;
		}
	}

	if (m_pStatCom->Get_Hit())
	{
		act_AfterHit(fTimeDelta);
	}
	m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), &_vec3(0.f, 0.f, 0.f)));
}
