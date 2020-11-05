#ifndef WeaponEquip_h__
#define WeaponEquip_h__

#include "EquipBase.h"

class CWeaponEquip : public CEquipBase
{
private:
	explicit				CWeaponEquip(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CWeaponEquip(void) = default;

public:
	virtual void			Click_Action(void) override;

public:
	static CWeaponEquip*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
};

#endif // WeaponEquip_h__
