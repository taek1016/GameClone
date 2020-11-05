#ifndef RightSide_h__
#define RightSide_h__

#include "YellowParticle.h"

class CRightSide : public CYellowParticle
{
private:
	explicit						CRightSide(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CRightSide(const CRightSide& rhs);
	virtual							~CRightSide(void) = default;

private:
	virtual void					move_Particle(const Engine::_float& fTimeDelta) override;

public:
	static CRightSide*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};
#endif // RightSide_h__
