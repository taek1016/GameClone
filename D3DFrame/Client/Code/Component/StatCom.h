#ifndef StatCom_h__
#define StatCom_h__

#include "Component.h"

class CStatCom : public Engine::CComponent
{
private:
	explicit			CStatCom(void);
	explicit			CStatCom(const CStatCom& rhs);
	virtual				~CStatCom(void);

public:
	const HP_INFO&			Get_HP(void) const;
	const Engine::_float	Get_HPPercent(void) const;

	const MP_INFO&			Get_MP(void) const;
	const Engine::_float	Get_MPPercent(void) const;

	const Engine::_bool&	Get_Dead(void) const;
	const Engine::_bool&	Get_Hit(void) const;
	const Engine::_bool&	Get_Dodge(void) const;

	const Engine::_int&		Get_Armor(void) const;
	const Engine::_int&		Get_Att(void) const;

	const Engine::_float	Get_Move(void) const;
	// true면 달리기, false면 걷기
	const Engine::_bool&	Get_Run(void) const;

	const Engine::_int&		Get_Level(void) const;

	const Engine::_bool		Get_Exp(const Engine::_int& iExp);

	void					Set_TotalStat(const UNIT_INFO& rhs);
	void					Set_Level(const Engine::_int & rhs);
	void					Set_Run(const Engine::_bool& bRun);

	void					Use_Mana(const Engine::_float& fMana);
	void					Revive(void);

	void					Set_Item(const UNIT_INFO& tInfo);

	// 타입 추가해야 함.
	void					Hit(const Engine::_int& iDamage, const Engine::_float& fDodgeDebuf = 0.f);

private:
	Engine::_bool		calculate_Dodge(const Engine::_float fAddPercent);

	void				level_Up(void);
	void				calculate_LevelStat(void);

	void				set_HP(const HP_INFO& rhs);
	void				set_MP(const MP_INFO& rhs);
	void				set_Move(const MOVE_INFO& rhs);
	void				set_AttArmor(const ATT_ARMOR_INFO& rhs);
	void				set_Percent(const PERCENT_INFO& rhs);
	void				set_Resist(const RESIST_INFO& rhs);

	Engine::_bool		m_bHit;
	Engine::_bool		m_bDead;
	Engine::_bool		m_bRun;
	Engine::_bool		m_bDodge;
	UNIT_INFO			m_tInfo;
	UNIT_INFO			m_tItemInfo;
	// 레벨업 할 때마다 사용할 정보
	UNIT_INFO			m_tLevelUpInfo;
	// 레벨 1 기준 정보.
	UNIT_INFO			m_tDefaultInfo;

	Engine::_int		m_iLevel;
	Engine::_int		m_iExp;
	Engine::_int		m_iLevelUpExp;

public:
	static CStatCom*			Create(void);
	static CStatCom*			Create(const UNIT_INFO& rhs);
	virtual Engine::CComponent*	Clone(void) override;

private:
	inline virtual void			Free(void);
};

#endif // StatCom_h__
