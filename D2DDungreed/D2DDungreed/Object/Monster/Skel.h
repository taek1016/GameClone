#ifndef __SKEL_H__

#include "MeleeMonster.h"

class CWeapon;
class CSkel : public CMeleeMonster
{
private:
	CWeapon*	m_pWeapon;

private:
	CSkel();

	void SetWeapon			(CWeapon* pObj)
	{
		m_pWeapon = pObj;
	}

public:
	virtual ~CSkel			();

	static CSkel* Create	(const D3DXVECTOR3& vecPos, const D3DXVECTOR3& vecSize, CWeapon* pWeapon);

	virtual void Act		() override;
	virtual void Attack		() override;
	virtual void Render		() override;
};

#define __SKEL_H__
#endif