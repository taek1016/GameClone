#ifndef __X_LARGE_FAIRY_H__
#include "Fairy.h"
class CXLargeFairy : public CFairy
{
private:
	CXLargeFairy();

public:
	virtual ~CXLargeFairy();

	static CXLargeFairy* Create(const D3DXVECTOR3& vecPos);
};

#define __X_LARGE_FAIRY_H__
#endif