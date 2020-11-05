#ifndef GunParticle_h__
#define GunParticle_h__

#include "Effect/Particle.h"

class CGunParticle : public CParticle
{
	explicit						CGunParticle();
	CGunParticle(const CGunParticle& rhs);

public:
	HRESULT							Initialize_GameObject()override;
	HRESULT							Late_Initialize()override;

	virtual void					Reset_AllParticles()override;

	int								m_iTexIndex = 0;

	void							Reset_Particle(Engine::PARTICLEATTRIBUTE *attribute)override;
	void							Pre_Render()override;
	void							Post_Render()override;

	void							Render_GameObject()override;

	Engine::_int					Update_GameObject(const Engine::_float& ftimeDelta)override;

	void							freeMem()override;

	static CGunParticle*			Create();

	CGunParticle*					Clone(const Engine::_vec3* pPos = nullptr)override;
};

#endif