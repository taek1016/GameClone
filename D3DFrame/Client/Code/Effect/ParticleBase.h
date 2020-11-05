#ifndef ParticleBase_h__
#define ParticleBase_h__

#include "EffectBase.h"

class CParticleBase : public CEffectBase
{
protected:
	explicit				CParticleBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CParticleBase(const CParticleBase& rhs);
	virtual					~CParticleBase(void) = default;

public:
	virtual HRESULT			Initialize_GameObject(void) override;
	virtual HRESULT			Late_Initialize(void) override;
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void			Render_GameObject(void) override;

	void					Set_Speed(const Engine::_float& fSpeed);
	void					Set_Dir(const Engine::_vec3* pDir);

protected:
	virtual void			set_Texture(const D3DXCOLOR& tColor);
	void					set_Speed(const Engine::_float& fSpeed);
	void					set_DeadTime(const Engine::_float& fDeadTime);
	void					set_MaxFrame(const Engine::_float& fMaxFrame);

	virtual HRESULT			setUp_ConstantTable(LPD3DXEFFECT& pEffect) override;
	virtual void			move_Particle(const Engine::_float& fTimeDelta) override { ; }

	CRigidBody*				m_pRigidBody;
	Engine::CShader*		m_pShader;
	LPDIRECT3DTEXTURE9		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;

	Engine::_float			m_fFrameCnt;
	Engine::_float			m_fFrameMax;
	Engine::_float			m_fSpeed;

	Engine::_float			m_fCurTime;
	Engine::_float			m_fDeadTime;

	Engine::_vec3			m_vDir;

protected:
	inline virtual void		Free(void) override;
};

#endif // ParticleBase_h__
