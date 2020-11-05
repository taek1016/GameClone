#ifndef __MELEE_MONSTER_H__

#include "Monster.h"

#include "../Effect/NoRenderEffect.h"

class CMeleeMonster : public CMonster
{
protected:
	CMeleeMonster			();

public:
	virtual ~CMeleeMonster	();

	virtual void Attack		() override PURE;
	virtual void Act		() override PURE;
};

#define __MELEE_MONSTER_H__
#endif