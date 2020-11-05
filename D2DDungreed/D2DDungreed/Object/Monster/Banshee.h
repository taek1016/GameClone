#ifndef __BANSHEE_H__

#include "RangeMonster.h"

class CBanshee : public CRangeMonster
{
private:
	CBanshee();

public:
	virtual ~CBanshee		();

	static CBanshee* Create	(const D3DXVECTOR3& vecPos);

	virtual void Attack		() override;
	virtual void Act		() override;
	virtual void UpdateRect	() override;
};

#define __BANSHEE_H__
#endif