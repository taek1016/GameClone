#ifndef __NORMAL_ATTACK_EFFECT_H__

#include "../GameObject.h"

class CNormalAttackEffect : public CGameObject
{
private:
	float		m_fDamage;
	float		m_fAngle;

	ATTACK_FROM	m_eFrom;

private:
	CNormalAttackEffect			();

	void SetDamage	(float fDamage)
	{
		m_fDamage = fDamage;
	}
	void SetFrom	(ATTACK_FROM eFrom)
	{
		m_eFrom = eFrom;
	}
	void SetAngle	(float fAngle)
	{
		m_fAngle = fAngle;
	}

public:
	virtual ~CNormalAttackEffect();

	static CNormalAttackEffect*	Create
	(
		const ATTACK_FROM	eFrom,
		const float			fDamage,
		const float			fAngle,
		const D3DXVECTOR3&	vecPos,
		const D3DXVECTOR3&	vecSize,
		const std::wstring& wStrKey,
		const std::wstring& wStrStatus,
		const WORD&			wIndex
	);

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;
};

#define __NORMAL_ATTACK_EFFECT_H__
#endif