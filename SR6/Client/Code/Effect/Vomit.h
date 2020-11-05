#ifndef Vomit_h__
#define Vomit_h__

#include "Effect/Particle.h"

class CVomit : public CParticle
{
	explicit						CVomit();
	explicit						CVomit(Engine::_vec3 emitPoint, int numOfParticles);
	CVomit(const CVomit& rhs);

	Engine::_float					m_fRunningTime = 0;
	Engine::_float					m_fDeathTime = 0;

	Engine::_float					m_fEmitTime = 0;
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

	static CVomit*				Create();

	CVomit*						Clone(const Engine::_vec3* pPos = nullptr)override;
};

#endif