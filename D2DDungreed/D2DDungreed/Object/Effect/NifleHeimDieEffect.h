#ifndef __BOSS_DIE_H__

#include "../GameObject.h"

class CNifleHeimDieEffect : public CGameObject
{
private:
	CNifleHeimDieEffect();

public:
	virtual ~CNifleHeimDieEffect();

	static CNifleHeimDieEffect* Create	(const D3DXVECTOR3& vecPos);

	virtual int Update					() override;
	virtual void LateUpdate				() override;
	virtual void Render					() override;
	virtual void UpdateRect				() override;
};

#define __BOSS_DIE_H__
#endif