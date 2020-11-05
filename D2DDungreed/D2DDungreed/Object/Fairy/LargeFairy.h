#ifndef __LARGE_FAIRY_H__
#include "Fairy.h"
class CLargeFairy : public CFairy
{
private:
	CLargeFairy();

public:
	virtual ~CLargeFairy();

	static CLargeFairy* Create(const D3DXVECTOR3& vecPos);
};

#define __LARGE_FAIRY_H__
#endif