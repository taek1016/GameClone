#ifndef __BASIC_GUN_H__

#include "Weapon.h"

class CBasicGun : public CWeapon
{
protected:
	float			m_fEdge;
	float			m_fDefaultYSize;

protected:
	CBasicGun();

	void SetDefaultY			(float fDefaultYSize)
	{
		m_fDefaultYSize = fDefaultYSize;
	}
	void SetEdge				(float fEdge)
	{
		m_fEdge = fEdge;
	}

	virtual void CreateBullet	() PURE;
	virtual void CreateEffect	() override PURE;

public:
	virtual ~CBasicGun			();

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void UpdateRect		() override;
};

#define __BASIC_GUN_H__
#endif