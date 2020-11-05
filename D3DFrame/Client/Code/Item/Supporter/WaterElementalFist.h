#ifndef WaterElementFist_h__
#define WaterElementFist_h__

#include "../WeaponBase.h"

class CWaterElementalFist : public CWeaponBase
{
private:
	explicit						CWaterElementalFist(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CWaterElementalFist(const CWaterElementalFist& rhs);
	virtual							~CWaterElementalFist(void) = default;

public:
	virtual HRESULT					Late_Initialize(void) override;

private:
	virtual Engine::_bool			check_Collide(void) override;

public:
	static CWaterElementalFist*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void);

};

#endif // WaterElementFist_h__
