#ifndef __BASIC_BOX_H__

#include "Box.h"
#include "BaseItem.h"

class CBasicBox :
	public CBox
{
private:
	CBasicBox();

public:
	virtual ~CBasicBox();

	static CBasicBox* Create(const D3DXVECTOR3& vecPos, CBaseItem* pIem);
};

#define __BASIC_BOX_H__
#endif