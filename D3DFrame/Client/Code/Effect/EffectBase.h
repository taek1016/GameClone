#ifndef EffectBase_h__
#define EffectBase_h__

#include "GameObject.h"

class CEffectBase : public Engine::CGameObject
{
protected:
	explicit				CEffectBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CEffectBase(const CEffectBase& rhs);
	virtual					~CEffectBase(void) = default;

public:
	virtual HRESULT			Initialize_GameObject(void) override PURE;
	virtual HRESULT			Late_Initialize(void) override PURE;
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override PURE;
	virtual void			Render_GameObject(void) override PURE;
	virtual void			Ready_ToGo(void) PURE;

protected:
	virtual HRESULT			setUp_ConstantTable(LPD3DXEFFECT& pEffect) PURE;
	virtual void			move_Particle(const Engine::_float& fTimeDelta) { ; }
};
#endif // EffectBase_h__
