#include "stdafx.h"
#include "Nefarian.h"

#include "Item/Monster/NefarianFLFoot.h"

USING(Engine)

CNefarian::CNefarian(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonsterBase(pGraphicDev)
	, m_iHoverCount(0)
{
	set_Name(L"Nefarian");
}

CNefarian::CNefarian(const CNefarian & rhs)
	: CMonsterBase(rhs)
	, m_iHoverCount(0)
{
}

void CNefarian::print_Name(void)
{
	_vec4 vPos(*m_pTransform->Get_Info(INFO_POS), 1.f);

	_vec3 vScale(30.f, 20.f, 1.f);
	make_PosToView(&vPos, vScale.x * 2.f, m_fHeight);

	DLL::pFontMgr->Print_Font(&_vec3(vPos), &vScale, 20, L"네파리안", D3DXCOLOR(0.f, 0.f, 1.f, 1.f));
}

void CNefarian::make_Weapon(Engine::CGameObject * pTarget)
{
	m_pWeapon = CNefarianFLFoot::Create(m_pGraphicDev, dynamic_cast<CCharacterBase*>(DLL::pObjMgr->Get_ObjList(L"Player")->front()));
	m_pWeaponMatrix = &m_pMesh->Get_FrameByName("Nefarian_Bone142")->CombinedTransformationMatrix;
	m_pWeapon->Set_ColliderMat(m_pTransform->Get_World(), m_pWeaponMatrix);

	m_iCurPattern = NEF_ATTACK;
}

void CNefarian::act_Determine(const Engine::_float & fTimeDelta)
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
	case CNefarian::NEF_ATTACK:
		melee_Attack(pPlayer, fTimeDelta);
		break;

	case CNefarian::NEF_BREATH_CAST:
		breath_Cast(pPlayer, fTimeDelta);
		break;

	case CNefarian::NEF_BREATH:
		breath_Shot(pPlayer, fTimeDelta);
		break;

	case CNefarian::NEF_STOMP:
		stomp_Around(pPlayer, fTimeDelta);
		break;

	case CNefarian::NEF_LIFT:
		lift_Off(pPlayer, fTimeDelta);
		break;

	case CNefarian::NEF_HOVER:
		hover(pPlayer, fTimeDelta);
		break;

	case CNefarian::NEF_LAND:
		landing(pPlayer, fTimeDelta);
		break;
	}
}

void CNefarian::initialize_ActionCols(void)
{
	const _float fMoveRadius = 54.f;

	Add_Action(L"BreathCol", 0.f, fMoveRadius);
	Add_Action(L"MeleeCol", 0.f, 16.f);
	Add_Action(L"Larva", 0.f, fMoveRadius);
	Add_Action(L"Stomp", 0.f, fMoveRadius);
	Add_Action(L"FollowCol", 0.f, fMoveRadius);
}

void CNefarian::move_Pattern(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
{
	if (can_Act(L"FollowCol", pPlayer))
	{
		if (!CollideFunc::MainSphereCol(this, pPlayer))
		{
			look_Target(pPlayer);
			move_ToPlayer(fTimeDelta);
			Set_AnimationSet(L"Walk");
		}
	}
}

void CNefarian::melee_Attack(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
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

		const _float fMeleeTime = (1093.f - 1033.f) / 30.f * 0.95f;
		if (m_fCurPatternTime >= fMeleeTime)
		{
			set_ActTime(3.f);
			m_fCurPatternTime = 0.f;
			m_iCurPattern = NEF_BREATH_CAST;
		}
	}
	else
	{
		move_Pattern(pPlayer, fTimeDelta);
	}
}

void CNefarian::breath_Cast(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
{
	if (can_Act(L"BreathCol", pPlayer))
	{
		if (m_fCurPatternTime <= FLT_EPSILON)
		{
			DLL::pSoundMgr->PlaySound(L"NefarianPreBreath.wav", CSoundMgr::MONSTER);
			DLL::pSoundMgr->SetVolume(CSoundMgr::MONSTER, 0.3f);
		}
		//look_Target(pPlayer);
		Set_AnimationSet(L"CastStart");

		m_fCurPatternTime += fTimeDelta;
		const _float fCastingTime = (2322.f - 2019.f) / 30.f * 0.95f;

		if (m_fCurPatternTime <= fCastingTime * 0.7f)
		{
			look_Target(pPlayer);
		}

		if (m_fCurPatternTime >= fCastingTime)
		{

			m_fCurPatternTime = 0.f;
			m_iCurPattern = NEF_BREATH;
		}
	}
	else
	{
		move_Pattern(pPlayer, fTimeDelta);
	}
}

void CNefarian::breath_Shot(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
{
	if (can_Act(L"BreathCol", pPlayer))
	{
		if (m_fCurPatternTime <= FLT_EPSILON)
		{
			DLL::pSoundMgr->PlaySound(L"NefarianBreath.wav", CSoundMgr::MONSTER);
			DLL::pSoundMgr->SetVolume(CSoundMgr::MONSTER, 0.3f);
		}
		Set_AnimationSet(L"Cast");

		m_fCurPatternTime += fTimeDelta;
		const _float fBreathTime = (1243.f - 1153.f) / 30.f * 0.9f;
		if (m_fCurPatternTime >= fBreathTime)
		{
			set_ActTime(3.f);
			m_fCurPatternTime = 0.f;
			m_iCurPattern = NEF_STOMP;
			return;
		}

		_vec3 vPos, vScale, vDir;
		_vec3 vHeadPos, vJawPos;
		memcpy(&vHeadPos, (m_pMesh->Get_FrameByName("Nefarian_Bone73_Jaw")->CombinedTransformationMatrix * *m_pTransform->Get_World()).m[3], sizeof(_vec3));
		memcpy(&vJawPos, (m_pMesh->Get_FrameByName("Nefarian_Bone138_Breath")->CombinedTransformationMatrix * *m_pTransform->Get_World()).m[3], sizeof(_vec3));

		vPos = vJawPos;
		D3DXVec3Normalize(&vDir, &(vJawPos - vHeadPos));

		vScale = { 2.f, 1.f, 2.f };

		CSkillBase* pSkill = DLL::pSkillMgr->Get_MonsterSkill(L"DragonBreath", &vPos, &vDir);
		pSkill->SetUp_Index();
		DLL::pObjMgr->Add_GameObject(L"Skill", pSkill);
	}
	else
	{
		move_Pattern(pPlayer, fTimeDelta);
	}
}

void CNefarian::stomp_Around(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
{
	if (can_Act(L"Stomp", pPlayer))
	{
		look_Target(pPlayer);
		Set_AnimationSet(L"DragonStomp");

		m_fCurPatternTime += fTimeDelta;
		const _float fStompTime = (973.f - 913.f) / 30.f * 0.95f;
		if (m_fCurPatternTime >= fStompTime)
		{
			// 스킬 생성
			_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
			vPos.y += 10.f;

			_vec3 vDir = *pPlayer->Get_Pos() - vPos;
			D3DXVec3Normalize(&vDir, &vDir);

			DLL::pObjMgr->Add_GameObject(L"Skill", DLL::pSkillMgr->Get_MonsterSkill(L"InfernalBall", &vPos, &vDir));

			set_ActTime(3.f);
			m_fCurPatternTime = 0.f;
			m_iCurPattern = NEF_LIFT;
			return;
		}
	}
	else
	{
		move_Pattern(pPlayer, fTimeDelta);
	}
}

void CNefarian::lift_Off(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
{
	if (can_Act(L"Larva", pPlayer))
	{
		look_Target(pPlayer);
		Set_AnimationSet(L"LiftOff");

		m_fCurPatternTime += fTimeDelta;
		const _float fLiftTime = (1513.f - 1423.f) / 30.f * 0.8f;
		if (m_fCurPatternTime >= fLiftTime)
		{
			DLL::pSoundMgr->PlaySound(L"NefarianHellFire.wav", CSoundMgr::MONSTER);
			DLL::pSoundMgr->SetVolume(CSoundMgr::MONSTER, 0.3f);

			_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
			vPos.y += 10.f;

			DLL::pObjMgr->Add_GameObject(L"Skill", DLL::pSkillMgr->Get_MonsterSkill(L"SummonMeteor", &vPos));
			m_fCurPatternTime = 0.f;
			m_iCurPattern = NEF_HOVER;
		}
	}
	else
	{
		move_Pattern(pPlayer, fTimeDelta);
	}
}

void CNefarian::hover(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
{
	if (can_Act(L"Larva", pPlayer))
	{
		look_Target(pPlayer);
		Set_AnimationSet(L"Hover");

		m_fCurPatternTime += fTimeDelta;
		const _float fHoverTime = (1363.f - 1303.f) / 30.f * 0.55f;
		if (m_fCurPatternTime >= fHoverTime)
		{
			m_fCurPatternTime = 0.f;
			m_iCurPattern = NEF_LAND;
		}
	}
	else
	{
		move_Pattern(pPlayer, fTimeDelta);
	}
}

void CNefarian::landing(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
{
	if (can_Act(L"Larva", pPlayer))
	{
		look_Target(pPlayer);
		Set_AnimationSet(L"Land");

		m_fCurPatternTime += fTimeDelta;
		const _float fLandingTime = (1663.f - 1573.f) / 30.f * 0.8f;
		if (m_fCurPatternTime >= fLandingTime)
		{
			set_ActTime(3.f);
			m_fCurPatternTime = 0.f;
			m_iCurPattern = NEF_ATTACK;
		}
	}
	else
	{
		move_Pattern(pPlayer, fTimeDelta);
	}
}

CNefarian * CNefarian::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNefarian* pInstance = new CNefarian(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->initialize_ActionCols();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CNefarian::Clone(void)
{
	CNefarian* pInstance = new CNefarian(*this);

	pInstance->Late_Initialize();
	pInstance->make_Weapon(DLL::pObjMgr->Get_ObjList(L"Player")->front());
	pInstance->initialize_ActionCols();
	pInstance->Add_MainCollider(pInstance->m_fMainColSize);

	return pInstance;
}
