#ifndef __ICE_PILLAR_H__

#include "Monster.h"
class CBoss;
class CIcePillar : public CMonster
{
private:
	int				m_iIndex;

	float			m_fSelfRot;
	float			m_fRevolve;

	D3DXMATRIX		m_matRev;

	BOSS_PATTERN	m_ePattern;
	BOSS_PATTERN	m_ePrePattern;
	CCoolTime		m_CoolTime;
	CBoss*			m_pTarget;

private:
	CIcePillar();

	void SetTarget	(CBoss* pObj)
	{
		m_pTarget = pObj;
	}
	void SetIndex	(int iIndex)
	{
		m_iIndex = iIndex;
	}
	void SetSelfRot	(float fAngle)
	{
		m_fSelfRot = fAngle;
	}
	void SetRevolve	(float fAngle)
	{
		m_fRevolve = fAngle;
	}
	void SummonBullet(const D3DXVECTOR3& vecPos, const float fRotation, const float fWay);
public:
	virtual ~CIcePillar();

	static CIcePillar* Create(int iIndex, float fSelfRotAngle, float fRevolveAngle, CBoss* pObj);

	virtual int Update		() override;
	virtual void LateUpdate	() override;
	virtual void Attack		() override;
	virtual void Act		() override;
};

#define __ICE_PILLAR_H__
#endif