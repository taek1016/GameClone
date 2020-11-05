#ifndef MouseBase_h__
#define MouseBase_h__

#include "GameObject.h"

class CMouseBase : public Engine::CGameObject
{
protected:
	explicit						CMouseBase(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CMouseBase(void) = default;

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

	virtual void					Click_Action(void) PURE;

protected:

	Engine::CTexture*				m_pTexture;
	Engine::CRcTex*					m_pBuffer;

public:
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // MouseBase_h__
