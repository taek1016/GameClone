#ifndef __BOSS_SUMMON_H__
#include "../GameObject.h"
class CNiffleHeimSummon : public CGameObject
{
private:
	CNiffleHeimSummon();

public:
	virtual ~CNiffleHeimSummon();

	static CNiffleHeimSummon* Create	(const D3DXVECTOR3& vecPos);

	virtual int Update					() override;
	virtual void LateUpdate				() override;
	virtual void Render					() override;
	virtual void UpdateRect				() override;
};

#define __BOSS_SUMMON_H__
#endif