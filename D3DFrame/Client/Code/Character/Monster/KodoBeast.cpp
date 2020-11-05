#include "stdafx.h"
#include "KodoBeast.h"

#include "Item/WeaponBase.h"
#include "Item/Monster/KodoBeastFoot.h"

USING(Engine)

CKodoBeast::CKodoBeast(LPDIRECT3DDEVICE9 pGraphicDev)
	: CAttackFirstMonster(pGraphicDev)
{
	set_Name(L"KodoBeast");
}

CKodoBeast::CKodoBeast(const CKodoBeast & rhs)
	: CAttackFirstMonster(rhs)
{
}

void CKodoBeast::print_Name(void)
{
	_vec4 vPos(*m_pTransform->Get_Info(INFO_POS), 1.f);

	_vec3 vScale(30.f, 20.f, 1.f);
	make_PosToView(&vPos, vScale.x * 2.5f, m_fHeight);

	DLL::pFontMgr->Print_Font(&_vec3(vPos), &vScale, 20, L"코도비스트", D3DXCOLOR(0.f, 0.f, 1.f, 1.f));
}

void CKodoBeast::make_Weapon(Engine::CGameObject * pTarget)
{
	m_pWeapon = CKodoBeastNose::Create(m_pGraphicDev, dynamic_cast<CCharacterBase*>(pTarget));
	m_pWeaponMatrix = &m_pMesh->Get_FrameByName("kodobeast_Bone45_CHD")->CombinedTransformationMatrix;
	m_pWeapon->Set_ColliderMat(m_pTransform->Get_World(), m_pWeaponMatrix);
}

void CKodoBeast::initialize_ActionCols(void)
{
	Add_Action(L"MeleeCol", 0.f, 7.f);
	Add_Action(L"FollowCol", 0.f, 30.f);

	m_iCurPattern = KODO_ATTACK;
}

void CKodoBeast::act_Determine(const Engine::_float & fTimeDelta)
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

	auto pPlayer = DLL::pObjMgr->Get_ObjList(L"Player")->front();

	switch (m_iCurPattern)
	{
	case CKodoBeast::KODO_ATTACK:
		attack_Target(pPlayer, fTimeDelta);
		break;

	case CKodoBeast::KODO_HIT:
		hit_Action(pPlayer, fTimeDelta);
		break;
	}
}

void CKodoBeast::attack_Target(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
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
		const _float fMeleeTime = (474.f - 429.f) / 30.f * 0.9f;
		if (m_fCurPatternTime >= fMeleeTime)
		{
			set_ActTime(3.f);
			m_fCurPatternTime = 0.f;
		}
	}
	else
	{
		move_Pattern(pPlayer, fTimeDelta);
	}
}

void CKodoBeast::hit_Action(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
{
	look_Target(pPlayer);
	Set_AnimationSet(L"Hit");
	set_ActTime(4.f);

	m_fCurPatternTime += fTimeDelta;
	const _float fHitTime = (342.f - 312.f) / 30.f * 0.95f;
	if (m_fCurPatternTime >= fHitTime)
	{
		m_iCurPattern = CKodoBeast::KODO_ATTACK;
	}
}

void CKodoBeast::move_Pattern(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
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

CKodoBeast * CKodoBeast::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CKodoBeast* pInstance = new CKodoBeast(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->initialize_ActionCols();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CKodoBeast::Clone(void)
{
	CKodoBeast* pInstance = new CKodoBeast(*this);

	pInstance->Late_Initialize();
	pInstance->initialize_ActionCols();
	pInstance->make_Weapon(DLL::pObjMgr->Get_ObjList(L"Player")->front());
	pInstance->Add_MainCollider(pInstance->m_fMainColSize);

	return pInstance;
}
