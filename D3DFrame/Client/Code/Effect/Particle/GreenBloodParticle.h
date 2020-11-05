#ifndef GreenBloodParticle_h__
#define GreenBloodParticle_h__

#include "BloodParticleBase.h"

class CGreenBloodParticle : public CBloodParticleBase
{
private:
	explicit						CGreenBloodParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CGreenBloodParticle(const CGreenBloodParticle& rhs);
	virtual							~CGreenBloodParticle(void) = default;

public:
	static CGreenBloodParticle*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};
#endif // GreenBloodParticle_h__
