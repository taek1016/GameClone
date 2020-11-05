#ifndef LeftSide_h__
#define LeftSide_h__

#include "YellowParticle.h"

class CLeftSide : public CYellowParticle
{
private:
	explicit						CLeftSide(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CLeftSide(const CLeftSide& rhs);
	virtual							~CLeftSide(void) = default;

private:
	virtual void					move_Particle(const Engine::_float& fTimeDelta) override;

public:
	static CLeftSide*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};
#endif // LeftSide_h__
