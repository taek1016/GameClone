#ifndef BloodParticle_h__
#define BloodParticle_h__

#include "Effect/Particle.h"

class CBloodParticle : public CParticle
{
	explicit						CBloodParticle();
	explicit						CBloodParticle(Engine::_vec3 emitPoint, int numOfParticles);
									CBloodParticle(const CBloodParticle& rhs);
public:
	HRESULT							Initialize_GameObject()override;
	HRESULT							Late_Initialize()override;
public:
	virtual void					Reset_AllParticles()override;
	void							Reset_Particle(Engine::PARTICLEATTRIBUTE *attribute)override;
	void							Pre_Render()override;
	void							Post_Render()override;

	Engine::_int					Update_GameObject(const Engine::_float& ftimeDelta)override;

	void							freeMem()override;

	static CBloodParticle*			Create();

	CBloodParticle*					Clone(const Engine::_vec3* pPos = nullptr)override;
};

#endif