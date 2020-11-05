#include "stdafx.h"
#include "SkillMgr.h"

#include "Skill/SkillBase.h"
#include "Skill/AttackSkillBase.h"

#include "Skill/Player/FrostBolt.h"
#include "Skill/Player/FrostNova.h"
#include "Skill/Player/ChickenSummon.h"
#include "Skill/Player/GryphonSummon.h"

#include "Skill/Monster/DragonBreath.h"
#include "Skill/Monster/InfernalDown.h"
#include "Skill/Monster/InfernalSummon.h"
#include "Skill/Monster/SummonMeteor.h"
#include "Skill/Monster/Meteor.h"
#include "Skill/Monster/Stomp.h"

#include "Character/Player.h"

USING(Engine)
IMPLEMENT_SINGLETON(CSkillMgr)

CSkillMgr::~CSkillMgr(void)
{
	Free();
}

void CSkillMgr::Initialize_Skills(LPDIRECT3DDEVICE9 pGraphicDev)
{
	initialize_PlayerSkills(pGraphicDev);
	initialize_MonsterSkills(pGraphicDev);
}

_bool CSkillMgr::Casting_Skill(const Engine::_tchar * pName)
{
	auto iter = m_mapPlayerSkills.find(pName);

	if (m_mapPlayerSkills.end() == iter)
	{
		return false;
	}

	auto pPlayer = dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front());

	if (pPlayer->Has_EnoughMana(iter->second->fNeedMana))
	{
		iter->second->bUsing = true;
		m_pCurrentSkill = iter->second;
	}
	else
	{
		DLL::pSoundMgr->PlaySound(L"OutOfMana.wav", CSoundMgr::PLAYER);
		DLL::pSoundMgr->SetVolume(CSoundMgr::PLAYER, 0.3f);
	}
	return true;
}

void CSkillMgr::Use_Skill(void)
{
	DLL::pObjMgr->Add_GameObject(L"Skill", m_pCurrentSkill->pSkill->Clone());
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front());

	pPlayer->Play_AnimationForce(m_pCurrentSkill->wStrCastingAnimationKey.c_str());

	m_pCurrentSkill = nullptr;

	for (auto iter : m_mapPlayerSkills)
	{
		if (true == iter.second->bUsing)
		{
			iter.second->bUsing = false;
		}
	}
	m_bSkillUsed = true;
}

const SKILL_INFO * CSkillMgr::Get_ShotSkill(void)
{
	return m_pCurrentSkill;
}

Engine::_bool CSkillMgr::Is_ShotSkill(void)
{
	return m_bSkillUsed;
}

Engine::_bool CSkillMgr::Is_PlayerSkill(const Engine::_tchar * pName)
{
	auto iter = m_mapPlayerSkills.find(pName);

	if (m_mapPlayerSkills.end() == iter)
	{
		return false;
	}

	return true;
}

Engine::_bool CSkillMgr::Is_SkillUsing(void) const
{
	if (nullptr != m_pCurrentSkill)
	{
		return m_pCurrentSkill->bUsing;
	}
	else
	{
		return false;
	}
}

Engine::_bool CSkillMgr::Is_CoolTime(void)
{
	_bool bCoolTime = m_bSkillUsed;
	m_bSkillUsed = false;
	return bCoolTime;
}

Engine::_float CSkillMgr::Get_CastingTime(void) const
{
	if (nullptr != m_pCurrentSkill)
	{
		return m_pCurrentSkill->fCastingTime;
	}
	else
	{
		return 0.f;
	}
}

Engine::_float CSkillMgr::Get_CoolTime(void) const
{
	if (nullptr != m_pCurrentSkill)
	{
		return m_pCurrentSkill->fCoolTime;
	}
	else
	{
		return 0.f;
	}
}

const SKILL_INFO * CSkillMgr::Get_CurrentSkillInfo(void) const
{
	if (nullptr == m_pCurrentSkill)
	{
		return nullptr;
	}

	return m_pCurrentSkill;
}

CSkillBase * CSkillMgr::Get_MonsterSkill(const Engine::_tchar * pKey, const Engine::_vec3 * pPos, const Engine::_vec3 * pDir)
{
	auto iter = m_mapMonsterSkills.find(pKey);

	if (m_mapMonsterSkills.end() == iter)
	{
		return nullptr;
	}

	CSkillBase* pSkill = dynamic_cast<CSkillBase*>(iter->second->Clone());
	pSkill->Set_Pos(pPos);
	pSkill->Set_Dir(pDir);

	return pSkill;
}

void CSkillMgr::initialize_PlayerSkills(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSkillBase* pSkill = CFrostBolt::Create(pGraphicDev, 0.5f);
	SKILL_INFO* pInfo = new SKILL_INFO(pSkill, L"ReadySpellDirected", L"SpellCastDirected", 3.f, 10.f, 5.f);
	m_mapPlayerSkills.emplace(pSkill->Get_Name(), pInfo);

	pSkill = CFrostNova::Create(pGraphicDev, 10.f);
	pInfo = new SKILL_INFO(pSkill, L"ReadySpellOmni", L"SpellCastOmni", 0.f, 0.f, 105.f);
	m_mapPlayerSkills.emplace(pSkill->Get_Name(), pInfo);

	pSkill = CChickenSummon::Create(pGraphicDev);
	pInfo = new SKILL_INFO(pSkill, L"ReadySpellDirected", L"SpellCastDirected", 3.f, 10.f);
	m_mapPlayerSkills.emplace(pSkill->Get_Name(), pInfo);

	pSkill = CGryphonSummon::Create(pGraphicDev);
	pInfo = new SKILL_INFO(pSkill, L"ReadySpellDirected", L"SpellCastDirected", 3.f, 10.f);
	m_mapPlayerSkills.emplace(pSkill->Get_Name(), pInfo);
}

void CSkillMgr::initialize_MonsterSkills(LPDIRECT3DDEVICE9 pGraphicDev)
{
	make_MonsterSkill<CDragonBreath>(pGraphicDev);
	make_MonsterSkill<CInfernalDown>(pGraphicDev);
	make_MonsterSkill<CInfernalSummon>(pGraphicDev);
	make_MonsterSkill<CSummonMeteor>(pGraphicDev);
	make_MonsterSkill<CMeteor>(pGraphicDev);
	make_MonsterSkill<CStomp>(pGraphicDev);
}

inline void CSkillMgr::Free(void)
{
	for (auto iter : m_mapPlayerSkills)
	{
		Safe_Release(iter.second->pSkill);
		Safe_Delete(iter.second);
	}

	for (auto iter : m_mapMonsterSkills)
	{
		Safe_Release(iter.second);
	}
	m_mapMonsterSkills.clear();
}
