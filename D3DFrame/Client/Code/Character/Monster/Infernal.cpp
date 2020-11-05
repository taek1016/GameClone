#include "stdafx.h"
#include "Infernal.h"

#include "Item/WeaponBase.h"
#include "Item/Monster/InfernalHand.h"

USING(Engine)

CInfernal::CInfernal(LPDIRECT3DDEVICE9 pGraphicDev)
	: CAttackFirstMonster(pGraphicDev)
	, m_iCurPattern(INFERNAL_STAND)
{
	set_Name(L"Infernal");

}

CInfernal::CInfernal(const CInfernal & rhs)
	: CAttackFirstMonster(rhs)
{
}

void CInfernal::print_Name(void)
{
	_vec4 vPos(*m_pTransform->Get_Info(INFO_POS), 1.f);

	_vec3 vScale(30.f, 20.f, 1.f);
	make_PosToView(&vPos, vScale.x * 2.f, m_fHeight);

	DLL::pFontMgr->Print_Font(&_vec3(vPos), &vScale, 20, L"인페르날", D3DXCOLOR(0.f, 0.f, 1.f, 1.f));
}

void CInfernal::make_Weapon(Engine::CGameObject * pTarget)
{
	m_pWeapon = CInfernalHand::Create(m_pGraphicDev, dynamic_cast<CCharacterBase*>(pTarget));
	m_pWeaponMatrix = &m_pMesh->Get_FrameByName("infernal_Bone57")->CombinedTransformationMatrix;
	m_pWeapon->Set_ColliderMat(m_pTransform->Get_World(), m_pWeaponMatrix);
}

void CInfernal::initialize_ActionCols(void)
{
	Add_Action(L"MeleeCol", 0.f, 5.f);
	Add_Action(L"FollowCol", 0.f, 25.f);

	m_iCurPattern = CInfernal::INFERNAL_ATTACK;
}

void CInfernal::act_Determine(const Engine::_float & fTimeDelta)
{
	Set_AnimationSet(L"Stand");

	if (m_bAfterAct)
	{
		can_NextAct(fTimeDelta);
		return;
	}
	else if (m_bHit)
	{
		Set_AnimationSet(L"Hit");
		if (m_pMesh->Is_AnimationSetEnd())
		{
			Set_AnimationSet(L"Stand");
			m_bHit = false;
		}
		return;
	}

	CGameObject* pPlayer = DLL::pObjMgr->Get_ObjList(L"Player")->front();

	switch (m_iCurPattern)
	{
	case CInfernal::INFERNAL_ATTACK:
		attack_Target(pPlayer, fTimeDelta);
		break;

	case CInfernal::INFERNAL_HIT:
		hit_Action(pPlayer, fTimeDelta);
		break;
	}
}

void CInfernal::attack_Target(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
{
	if (can_Act(L"MeleeCol", pPlayer))
	{
		look_Target(pPlayer);
		Set_AnimationSet(L"Attack");

		if (m_pWeapon && false == m_bMeleeAtt)
		{
			m_pWeapon->AttackAct();
			m_bMeleeAtt = true;
		}
		m_fCurPatternTime += fTimeDelta;

		const _float fActTime = (252.f - 207.f) / 30.f * 0.95f;
		if (m_fCurPatternTime >= fActTime)
		{
			set_ActTime(2.f);
			m_fCurPatternTime = 0.f;
			m_iCurPattern = INFERNAL_ATTACK;
		}
	}
	else
	{
		move_Pattern(pPlayer, fTimeDelta);
	}
}

void CInfernal::hit_Action(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
{
	look_Target(pPlayer);
	Set_AnimationSet(L"Hit");

	m_fCurPatternTime += fTimeDelta;
	const _float fHitTime = (342.f - 312.f) / 30.f * 0.95f;
	if (m_fCurPatternTime >= fHitTime)
	{
		set_ActTime(2.f);
		m_fCurPatternTime = 0.f;
		m_iCurPattern = CInfernal::INFERNAL_ATTACK;
	}
}

void CInfernal::move_Pattern(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
{
	if (can_Act(L"FollowCol", pPlayer))
	{
		if (!CollideFunc::MainSphereCol(this, pPlayer))
		{
			look_Target(pPlayer);
			move_ToPlayer(fTimeDelta);
			Set_AnimationSet(L"Run");
		}
	}
}

CInfernal * CInfernal::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CInfernal* pInstance = new CInfernal(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}

	pInstance->initialize_ActionCols();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CInfernal::Clone(void)
{
	CInfernal* pInstance = new CInfernal(*this);

	pInstance->Late_Initialize();
	pInstance->initialize_ActionCols();
	pInstance->Add_MainCollider(pInstance->m_fMainColSize);
	pInstance->make_Weapon(DLL::pObjMgr->Get_ObjList(L"Player")->front());

	return pInstance;
}
