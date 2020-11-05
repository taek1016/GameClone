#ifndef FinalStaff_h__
#define FinalStaff_h__

#include "../WeaponBase.h"

class CFinalStaff : public CWeaponBase
{
private:
	explicit						CFinalStaff(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CFinalStaff(const CFinalStaff& rhs);
	virtual							~CFinalStaff(void) = default;

private:
	virtual Engine::_bool			check_Collide(void) override { return false; }

public:
	static CFinalStaff*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void);

};

#endif // FinalStaff_h__
