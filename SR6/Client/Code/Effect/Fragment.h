#ifndef Fragment_h__
#define Fragment_h__

#include "Effect/Particle.h"

class CFragment : public CParticle
{
	explicit						CFragment();
	explicit						CFragment(Engine::_vec3 emitPoint, int numOfParticles);
	CFragment(const CFragment& rhs);
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

	static CFragment*				Create();

	CFragment*						Clone(const Engine::_vec3* pPos = nullptr)override;
};

#endif