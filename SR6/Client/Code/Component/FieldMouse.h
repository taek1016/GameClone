#ifndef FieldMouse_h__
#define FieldMouse_h__

#include "Mouse.h"

class CFieldMouse : public Engine::CMouse
{
private:
	explicit	CFieldMouse(void);
	virtual		~CFieldMouse(void);

public:
	virtual HRESULT	Late_Initialize();
	virtual HRESULT	Initialize_GameObject();
	Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta);
	void			Render_GameObject();

	void			Set_MouseState();
private:
	Engine::_bool			m_bFixed = true;
	Engine::_int			m_iCurState = 0;
	Engine::CTransform*		m_pTargetTransform = nullptr;
	Engine::CGameObject*	m_pGameObject = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;
	Engine::_vec3			m_vLook;

public:
	static CFieldMouse*	Create();

private:
	virtual void LoadData(HANDLE hFile) override;
	virtual CGameObject * Clone(const _vec3 * pPos = nullptr) override;
};

#endif // FieldMouse_h__