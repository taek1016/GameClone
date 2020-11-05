#ifndef __SMALL_FAIRY_H__
#include "Fairy.h"
class CSmallFairy : public CFairy
{
private:
	CSmallFairy();

public:
	virtual ~CSmallFairy();

	static CSmallFairy* Create(const D3DXVECTOR3& vecPos);
};

#define __SMALL_FAIRY_H__
#endif