#include "stdafx.h"
#include "DoomGuard.h"

#include "Item/Monster/DoomguardSword.h"

USING(Engine)

CDoomGuard::CDoomGuard(LPDIRECT3DDEVICE9 pGraphicDev)
	: CAttackFirstMonster(pGraphicDev)
{
	set_Name(L"Doomguard");
}

CDoomGuard::CDoomGuard(const CDoomGuard & rhs)
	: CAttackFirstMonster(rhs)
{
}

CDoomGuard::~CDoomGuard(void)
{
}

HRESULT CDoomGuard::Initialize_GameObject()
{
	CMonsterBase::Initialize_GameObject();


	return S_OK;
}

void CDoomGuard::make_Weapon(Engine::CGameObject * pTarget)
{
	m_pWeapon = CDoomguardSword::Create(m_pGraphicDev, dynamic_cast<CCharacterBase*>(pTarget));
	m_pWeaponMatrix = &m_pMesh->Get_FrameByName("Doomguard_Bone77_CHD")->CombinedTransformationMatrix;
	m_pWeapon->Set_ColliderMat(m_pTransform->Get_World(), m_pWeaponMatrix);

	m_iCurPattern = DOOM_STOMP;
}

void CDoomGuard::initialize_ActionCol(void)
{
	Add_Action(L"SkillCol", 0.f, 8.f);
	Add_Action(L"MeleeCol", 0.f, 5.f);
	Add_Action(L"FollowCol", 0.f, 30.f);
}

void CDoomGuard::print_Name(void)
{
	_vec4 vPos(*m_pTransform->Get_Info(INFO_POS), 1.f);

	_vec3 vScale(30.f, 20.f, 1.f);
	make_PosToView(&vPos, vScale.x * 1.5f, m_fHeight);

	DLL::pFontMgr->Print_Font(&_vec3(vPos), &vScale, 20, L"µÒ°¡µå", D3DXCOLOR(0.f, 0.f, 1.f, 1.f));
}

void CDoomGuard::initialize_Bones(void)
{
}

void CDoomGuard::act_Determine(const Engine::_float & fTimeDelta)
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
	case CDoomGuard::DOOM_ATTACK:
		melee_Attack(pPlayer, fTimeDelta);
		break;
	case CDoomGuard::DOOM_STOMP:
		stomp_Attack(pPlayer, fTimeDelta);
		break;
	}
}

Engine::_bool CDoomGuard::skill_Act(void)
{
	return true;
}

Engine::_bool CDoomGuard::attack_Act(void)
{
	return true;
}

CDoomGuard * CDoomGuard::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDoomGuard* pInstance = new CDoomGuard(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CDoomGuard::Clone(void)
{
	CDoomGuard* pInstance = new CDoomGuard(*this);

	pInstance->Late_Initialize();
	pInstance->Add_MainCollider(pInstance->m_fMainColSize);
	pInstance->make_Weapon(DLL::pObjMgr->Get_ObjList(L"Player")->front());
	pInstance->initialize_ActionCol();

	return pInstance;
}

void CDoomGuard::set_AttackAnimation(void)
{
}

void CDoomGuard::melee_Attack(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
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

		const _float fMeleeTime = (372.f - 342.f) / 30.f * 0.95f;
		if (m_fCurPatternTime >= fMeleeTime)
		{
			set_ActTime(3.f);
			m_fCurPatternTime = 0.f;
			m_iCurPattern = DOOM_ATTACK;
		}
	}
	else
	{
		move_Pattern(pPlayer, fTimeDelta);
	}
}

void CDoomGuard::stomp_Attack(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
{
	if (can_Act(L"SkillCol", pPlayer))
	{
		look_Target(pPlayer);
		Set_AnimationSet(L"Stomp");

		m_fCurPatternTime += fTimeDelta;
		const _float fStompTime = (921.f - 891.f) / 30.f * 0.95f;

		if (m_fCurPatternTime >= fStompTime)
		{
			DLL::pSoundMgr->PlaySound(L"DoomguardSpell.wav", CSoundMgr::MONSTER);
			DLL::pSoundMgr->SetVolume(CSoundMgr::MONSTER, 0.3f);

			// ½ºÅèÇÁ ½ºÅ³ ½ÇÇà
			_matrix matSkill = m_pMesh->Get_FrameByName("Doomguard_Bone58")->CombinedTransformationMatrix * *m_pTransform->Get_World();
			_vec3 vPos;
			memcpy(&vPos, matSkill.m[3], sizeof(_vec3));
			DLL::pObjMgr->Add_GameObject(L"Skill", DLL::pSkillMgr->Get_MonsterSkill(L"Stomp", &vPos));

			set_ActTime(4.f);
			m_fCurPatternTime = 0.f;
			m_iCurPattern = DOOM_ATTACK;
		}
	}
	else
	{
		move_Pattern(pPlayer, fTimeDelta);
	}
}

void CDoomGuard::move_Pattern(Engine::CGameObject * pPlayer, const Engine::_float & fTimeDelta)
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
