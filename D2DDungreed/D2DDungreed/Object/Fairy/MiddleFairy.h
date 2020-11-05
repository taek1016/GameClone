#ifndef __MIDDLE_FAIRY_H__

#include "Fairy.h"

class CMiddleFairy : public CFairy
{
private:
	CMiddleFairy();

public:
	virtual ~CMiddleFairy();

	static CMiddleFairy* Create(const D3DXVECTOR3& vecPos);
};

#define __MIDDLE_FAIRY_H__
#endif