#ifndef __BOSS_H__

#include "Monster.h"

#include "../Monster/IcePillar.h"

class CBoss : public CMonster
{
private:
	bool				m_bStun;
	int					m_iPillarNum;
	BOSS_PATTERN		m_eCurPattern;
	
	CCoolTime			m_PatternCool;
	CCoolTime			m_StunCool;

	class CBossHP*		m_pHPUI;
	class CIcePillar*	m_pPillar[4];

private:
	CBoss();

	void SetPattern(BOSS_PATTERN ePattern)
	{
		m_eCurPattern = ePattern;
	}

	void PatternOne();
	void PatternTwo();
	void PatternThree();
	void PatternFour();
	void PatternFive();

	virtual void Attack() override;
	virtual void Act() override;

public:
	virtual ~CBoss();

	static CBoss* Create		(const D3DXVECTOR3& vecPos);

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;

	virtual void UpdateRect		() override;
	virtual void GetDamage		(float fDamage) override;

	void DecreasePillar			()
	{
		m_iPillarNum--;
	}
	void InitializePillar		();
	BOSS_PATTERN GetCurPattern	()
	{
		return m_eCurPattern;
	}
};

#define __BOSS_H__
#endif