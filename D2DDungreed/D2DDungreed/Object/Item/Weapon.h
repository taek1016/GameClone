#ifndef __WEAPON_H__

#include "BaseItem.h"

class CWeapon : public CBaseItem
{
protected:
	float				m_fDamage;
	float				m_fAngle;
	float				m_fWidth;
	float				m_fHeight;

protected:
	CWeapon						();

	void SetEquipWidth			(const float fWidth)
	{
		m_fWidth = fWidth;
	}
	void SetEquipHeight			(const float fHeight)
	{
		m_fHeight = fHeight;
	}
	void SetDamage				(float fDamage)
	{
		m_fDamage = fDamage;
	}

	virtual void CreateEffect	() PURE;

public:
	virtual ~CWeapon			();

	virtual int Update			() override PURE;
	virtual void LateUpdate		() override PURE;
	virtual void Render			() override;
	virtual void UpdateRect		() override PURE;

	float GetDamage				() const
	{
		return m_fDamage;
	}
};

#define __WEAPON_H__
#endif