#ifndef __BULLET_BASE_H__
#include "../GameObject.h"
class CBulletBase : public CGameObject
{
protected:
	bool		m_bDead;

	float		m_fAngle;
	float		m_fSpeed;

	float		m_fHalfX;
	float		m_fHalfY;

	ATTACK_FROM	m_eFrom;

	float		m_fDamage;

protected:
	CBulletBase();

	void SetAngle(float fAngle)
	{
		m_fAngle = fAngle;
	}
	void SetSpeed(float fSpeed)
	{
		m_fSpeed = fSpeed;
	}
	void SetHalfXY(float fHalfX, float fHalfY)
	{
		m_fHalfX = fHalfX;
		m_fHalfY = fHalfY;
	}
	void SetFrom(ATTACK_FROM eFrom)
	{
		m_eFrom = eFrom;
	}
	void SetDamage(float fDamage)
	{
		m_fDamage = fDamage;
	}

public:
	virtual ~CBulletBase();

	virtual int Update		() override;
	virtual void LateUpdate	() override;
	virtual void Render		() override;
	virtual void UpdateRect	() override;

	virtual void SetEffect	() PURE;
};

#define __BULLET_BASE_H__
#endif