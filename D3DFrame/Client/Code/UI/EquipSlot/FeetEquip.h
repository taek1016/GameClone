#ifndef FeetEquip_h__
#define FeetEquip_h__

#include "EquipBase.h"

class CFeetEquip : public CEquipBase
{
protected:
	explicit			CFeetEquip(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CFeetEquip(void) = default;

public:
	virtual void		Click_Action(void);

public:
	static CFeetEquip*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
};

#endif // FeetEquip_h__
