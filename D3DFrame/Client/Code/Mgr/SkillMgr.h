#ifndef SkillMgr_h__
#define SkillMgr_h__

#include "Base.h"

#include "Skill/SkillBase.h"

class CSkillMgr : public CBase
{
	DECLARE_SINGLETON(CSkillMgr)

private:
	explicit					CSkillMgr(void) = default;
	virtual						~CSkillMgr(void);

public:
	void						Initialize_Skills(LPDIRECT3DDEVICE9 pGraphicDev);

	Engine::_bool				Casting_Skill(const Engine::_tchar* pName);
	void						Use_Skill(void);
	const SKILL_INFO*			Get_ShotSkill(void);
	Engine::_bool				Is_ShotSkill(void);
	Engine::_bool				Is_PlayerSkill(const Engine::_tchar* pName);

	Engine::_bool				Is_SkillUsing(void) const;
	Engine::_bool				Is_CoolTime(void);

	Engine::_float				Get_CastingTime(void) const;
	Engine::_float				Get_CoolTime(void) const;

	const SKILL_INFO*			Get_CurrentSkillInfo(void) const;
	CSkillBase*					Get_MonsterSkill(const Engine::_tchar* pKey, const Engine::_vec3* pPos, const Engine::_vec3* pDir = &Engine::_vec3(0.f, 0.f, 0.f));

private:
	template <typename T>
	void						make_MonsterSkill(LPDIRECT3DDEVICE9 pGraphicDev)
	{
		T* pSkill = T::Create(pGraphicDev);

		const _tchar* pName = pSkill->Get_Name();
		auto iter = m_mapMonsterSkills.find(pName);

		if (m_mapMonsterSkills.end() != iter)
		{
			Engine::Safe_Release(pSkill);
			return;
		}

		m_mapMonsterSkills.emplace(pName, pSkill);
	}

	void						initialize_PlayerSkills(LPDIRECT3DDEVICE9 pGraphicDev);
	void						initialize_MonsterSkills(LPDIRECT3DDEVICE9 pGraphicDev);

	map<wstring, SKILL_INFO*>	m_mapPlayerSkills;
	map<wstring, CSkillBase*>	m_mapMonsterSkills;

	Engine::_float				m_fCurSkillCasting;
	SKILL_INFO*					m_pCurrentSkill = nullptr;

	Engine::_bool				m_bSkillUsed = false;

private:
	inline virtual void			Free(void) override;
};

#endif // SkillMgr_h__
