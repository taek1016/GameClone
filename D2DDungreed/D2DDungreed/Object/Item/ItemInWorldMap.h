#ifndef __ITEM_IN_WORLD_MAP_H__

#include "../GameObject.h"

class CBaseItem;
class CItemInWorldMap : public CGameObject
{
private:
	GRAVITY_INFO	m_tGravity;
	
	CBaseItem*		m_pItem;

	const float		m_fYDir;

	bool			m_bDown;
	bool			m_bSpawn;

private:
	CItemInWorldMap();

	void SetItem				(CBaseItem* pObj)
	{
		m_pItem = pObj;
	}

public:
	virtual ~CItemInWorldMap	();

	static CItemInWorldMap*	Create
	(
		const D3DXVECTOR3&	vecPos,
		const D3DXVECTOR3&	vecSizeDefault,
		CBaseItem*			pItem
	);

	// CGameObject을(를) 통해 상속됨
	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;

};

#define __ITEM_IN_WORLD_MAP_H__
#endif