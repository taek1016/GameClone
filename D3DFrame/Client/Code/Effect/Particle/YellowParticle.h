#ifndef YellowParticle_h__
#define YellowParticle_h__

#include "../ParticleBase.h"

class CYellowParticle : public CParticleBase
{
protected:
	explicit		CYellowParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit		CYellowParticle(const CYellowParticle& rhs);
	virtual			~CYellowParticle(void) = default;

public:
	virtual HRESULT	Initialize_GameObject(void) override;
	virtual HRESULT	Late_Initialize(void) override;

	void			Set_Data(const Engine::_float& fAngle, const Engine::_vec3* pPos);
	virtual void	Ready_ToGo(void) override;

protected:
	void			set_Angle(const Engine::_float& fAngle);
	void			set_TargetPos(const Engine::_vec3* pPos);

	virtual void	move_Particle(const Engine::_float& fTimeDelta) override PURE;

	Engine::_float	m_fAngle;
	Engine::_vec3	m_vTargetPos;
	Engine::_bool	m_bDead;
};

#endif // YellowParticle_h__
