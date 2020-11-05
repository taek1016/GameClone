#ifndef BloodParticleBase_h__
#define BloodParticleBase_h__

#include "../ParticleBase.h"

class CBloodParticleBase : public CParticleBase
{
protected:
	explicit				CBloodParticleBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CBloodParticleBase(const CBloodParticleBase& rhs);
	virtual					~CBloodParticleBase(void) = default;

public:
	virtual HRESULT			Initialize_GameObject(void) override;
	virtual HRESULT			Late_Initialize(void) override;
	virtual void			Ready_ToGo(void) override;

protected:
	virtual void			move_Particle(const Engine::_float& fTimeDelta) override;
};

#endif // BloodParticleBase_h__
