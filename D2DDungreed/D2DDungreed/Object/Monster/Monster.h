#ifndef __MONSTER_H__

#include "../MoveObject.h"
#include "Rect.h"
#include "../UI/MonsterHPUI.h"

class CPlayer;
class CRect;

class CMonster : public CMoveObject
{
protected:
	bool			m_bAction;
	bool			m_bFlashed;
	CCoolTime		m_fAttackCool;
	CCoolTime		m_fSkillCool;

	float			m_fCheckDistance;
	float			m_fXWay;
	float			m_fDamage;

	CPlayer*		m_pPlayer;
	CRect*			m_pAttackRect;
	CRect*			m_pSkillRect;
	CRect*			m_pMoveRect;

	CMonsterHPUI*	m_pHPUI;

protected:
	CMonster				();

	void SetAttackCool		(float fAttackCool)
	{
		m_fAttackCool.SetCool(fAttackCool);
	}
	void SetSkillCool		(float fSkillCool)
	{
		m_fAttackCool.SetCool(fSkillCool);
	}
	void SetCheckDistance	(float fDistance)
	{
		m_fCheckDistance = fDistance;
	}
	void SetDefaultXWay		(float fWay)
	{
		m_fXWay = fWay;
	}
	void SetDamage			(float fDamage)
	{
		m_fDamage = fDamage;
	}

	void UpdateCool			();
	void UpdateCheckRect	();

	virtual void Attack		() PURE;

	virtual void Act		() PURE;
	void CheckWay			();

	//bool CanAnotherAction	();

public:
	virtual ~CMonster		();

	virtual int Update		() override;
	virtual void LateUpdate	() override;
	virtual void Render		() override;

};

#define __MONSTER_H__
#endif