#ifndef ToolMouse_h__
#define ToolMouse_h__

#include "Mouse.h"

BEGIN(Engine)
class CGameObject;
END

class CToolMouse : public Engine::CMouse
{
private:
	explicit				CToolMouse(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CToolMouse(void);

public:
	virtual HRESULT			Late_Initialize() override;
	virtual HRESULT			Initialize_GameObject() override;
	Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;

	void					Set_Target(CGameObject* pObj);
	void					Set_TargetNull(void);

private:
	void					key_Input(void);

	Engine::CGameObject*	m_pGameObj;

public:
	static CToolMouse*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
};

#endif // ToolMouse_h__
