#ifndef ChestEquip_h__
#define ChestEquip_h__

#include "EquipBase.h"

class CChestEquip : public CEquipBase
{
protected:
	explicit			CChestEquip(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CChestEquip(void) = default;

public:
	virtual void		Click_Action(void);

public:
	static CChestEquip*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
};

#endif // ChestEquip_h__
