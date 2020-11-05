#ifndef HeadEquip_h__
#define HeadEquip_h__

#include "EquipBase.h"

class CHeadEquip : public CEquipBase
{
protected:
	explicit			CHeadEquip(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CHeadEquip(void) = default;

public:
	virtual void		Click_Action(void);

public:
	static CHeadEquip*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
};

#endif // HeadEquip_h__
