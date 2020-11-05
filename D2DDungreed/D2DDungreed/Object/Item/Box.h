#ifndef __BOX_H__

#include "../GameObject.h"
#include "BaseItem.h"

class CBox : public CGameObject
{
private:
	bool		m_bActivate;
	CBaseItem*	m_pItem;

protected:
	CBox();

	void SetItem			(CBaseItem* pItem)
	{
		m_pItem = pItem;
	}

public:
	virtual ~CBox();

	virtual int Update		() override;
	virtual void LateUpdate	() override;
	virtual void Render		() override;
	virtual void UpdateRect	() override;
};

#define __BOX_H__
#endif