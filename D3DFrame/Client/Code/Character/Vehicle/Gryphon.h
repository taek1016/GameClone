#ifndef Gryphon_h__
#define Gryphon_h__

#include "FlyVehicle.h"

class CGryphon : public CFlyVehicle
{
private:
	explicit						CGryphon(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CGryphon(const CGryphon& rhs);
	virtual							~CGryphon(void) = default;

public:
	static CGryphon*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};
#endif // Gryphon_h__
