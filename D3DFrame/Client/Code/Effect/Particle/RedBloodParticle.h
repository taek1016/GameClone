#ifndef RedBloodParticle_h__
#define RedBloodParticle_h__

#include "BloodParticleBase.h"

class CRedBloodParticle : public CBloodParticleBase
{
private:
	explicit						CRedBloodParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CRedBloodParticle(const CRedBloodParticle& rhs);
	virtual							~CRedBloodParticle(void) = default;

public:
	static CRedBloodParticle*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};
#endif // RedBloodParticle_h__
