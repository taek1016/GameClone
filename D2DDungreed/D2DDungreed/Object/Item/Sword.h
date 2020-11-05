#ifndef __SWORD_H__

#include "Weapon.h"

class CSword : public CWeapon
{
protected:
	CSword						();

public:
	virtual ~CSword				();

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void UpdateRect		() override;
	virtual void Render			();

protected:
	virtual void CreateEffect	() PURE;

	void SetEffectKey			(const std::wstring wEffectKey)
	{
		m_wStrEffectKey = wEffectKey;
	}
	void SetEffectStatus		(const std::wstring wEffectStatus)
	{
		m_wStrEffectStatus = wEffectStatus;
	}
	void SetAttackCool			(const float fCool)
	{
		m_fAttackCool = fCool;
	}

	void SetStartPos			();
	void SetAngle				();
protected:
	bool			m_bSwing;
	bool			m_bAttack;

	std::wstring	m_wStrEffectKey;
	std::wstring	m_wStrEffectStatus;
	
	float			m_fAttackCool;

	D3DXVECTOR3		m_vecZ;
	D3DXVECTOR3		m_vecStartDir;
};

#define __SWORD_H__
#endif