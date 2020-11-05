#ifndef __RANGE_MONSTER_H__
#include "Monster.h"
class CRangeMonster : public CMonster
{
protected:
	CRangeMonster();

public:
	virtual ~CRangeMonster();

	virtual void Attack	() override PURE;
	virtual void Act	() override;
};

#define __RANGE_MONSTER_H__
#endif