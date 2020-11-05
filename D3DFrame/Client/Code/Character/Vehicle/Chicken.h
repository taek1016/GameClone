#ifndef Chicken_h__
#define Chicken_h__

#include "WalkVehicle.h"

class CChicken : public CWalkVehicle
{
private:
	explicit						CChicken(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CChicken(const CChicken& rhs);
	virtual							~CChicken(void) = default;

public:
	static CChicken*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};
#endif // Chicken_h__