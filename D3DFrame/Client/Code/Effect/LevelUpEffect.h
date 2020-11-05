#ifndef LevelUpEffect_h__
#define LevelUpEffect_h__

#include "EffectBase.h"

class CLevelUpEffect : public CEffectBase
{
private:
	explicit						CLevelUpEffect(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CLevelUpEffect(const CLevelUpEffect& rhs);
	virtual							~CLevelUpEffect(void) = default;

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;
	virtual void					Ready_ToGo(void) override;

private:
	virtual HRESULT					setUp_ConstantTable(LPD3DXEFFECT& pEffect);

	Engine::_float					m_fCurTime;
	Engine::_float					m_fParticleMakeTime;
	Engine::_float					m_fLifeTime;
	Engine::_float					m_fDeadTime;

public:
	static CLevelUpEffect*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;


};

#endif // LevelUpEffect_h__
