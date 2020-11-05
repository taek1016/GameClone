#ifndef ShoulderEquip_h__
#define ShoulderEquip_h__

#include "EquipBase.h"

class CShoulderEquip : public CEquipBase
{
protected:
	explicit			CShoulderEquip(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CShoulderEquip(void) = default;

public:
	virtual void		Click_Action(void);

public:
	static CShoulderEquip*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
};

#endif // ShoulderEquip_h__
