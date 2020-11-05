#ifndef DeafultStaff_h__
#define DeafultStaff_h__

#include "../WeaponBase.h"

class CDefaultStaff : public CWeaponBase
{
private:
	explicit						CDefaultStaff(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CDefaultStaff(const CDefaultStaff& rhs);
	virtual							~CDefaultStaff(void) = default;

private:
	virtual Engine::_bool			check_Collide(void) override { return false; }

public:
	static CDefaultStaff*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void);
	
};

#endif // DeafultStaff_h__
