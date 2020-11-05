#ifndef __BASE_ITEM_H__

#include "../GameObject.h"

class CBaseItem : public CGameObject
{
protected:
	CBaseItem				();

public:
	virtual ~CBaseItem		();

	virtual int Update		() override PURE;
	virtual void LateUpdate	() override PURE;
	virtual void Render		() override;
	virtual void UpdateRect	() override PURE;
};

#define __BASE_ITEM_H__
#endif