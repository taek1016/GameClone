#ifndef __PLAYER_H__

#include "../D2DDungreed/Object/MoveObject.h"

class CPlayer :	public CMoveObject
{
protected:
	CPlayer					();

public:
	virtual ~CPlayer		();
	static CPlayer* Create	(const D3DXVECTOR3& vPos);

	virtual int Update		() override;
	virtual void LateUpdate	() override;
	virtual void Render		() override;
	inline void ChangeJump	();

	int GetMaxDashCount		() const
	{
		return m_tDashCount.iMaxCount;
	}
	int GetCurDashCount		() const
	{
		return m_tDashCount.iCurCount;
	}
	void GetHeal			(int iHealPoint)
	{
		m_iHP += iHealPoint;
		if (m_iHP >= m_iMaxHP)
		{
			m_iHP = m_iMaxHP;
		}
	}

private:
	virtual	void UpdateRect	();
	void KeyInput			();
	void CheckWay			();
	void CheckDashCount		();

	// 움직임 함수
	void Dash				();
	void ContinueDash		();
		 
	void AssertMember		();

private:
	COUNT					m_tDashCount;

	float					m_fDashDelta;
	float					m_fDashContinue;
	
	class CWeapon*			m_pWeapon;
};

#define __PLAYER_H__
#endif