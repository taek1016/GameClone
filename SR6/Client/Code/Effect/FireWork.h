#ifndef FireWork_h__
#define FireWork_h__

#include "Effect/Particle.h"

class CFireWork : public CParticle
{
	explicit						CFireWork();
	explicit						CFireWork(Engine::_vec3 emitPoint, int numOfParticles);
	CFireWork(const CFireWork& rhs);

	PARTICLEATTRIBUTE				m_particle;

	Engine::_int					m_iYOffset = 1;

	Engine::_bool					m_bFirstFire = false;
public:
	HRESULT							Initialize_GameObject()override;
	HRESULT							Late_Initialize()override;
public:
	virtual void					Reset_AllParticles()override;
	void							Reset_Particle(Engine::PARTICLEATTRIBUTE *attribute)override;
	void							Pre_Render()override;
	void							Post_Render()override;

	void							Render_GameObject()override;

	void							SetBombPoint(Engine::_vec3 vPoint);

	Engine::_int					Update_GameObject(const Engine::_float& ftimeDelta)override;

	void							freeMem()override;

	static CFireWork*			Create();

	CFireWork*					Clone(const Engine::_vec3* pPos = nullptr)override;
};

#endif