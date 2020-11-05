#ifndef ToolGameObject_h__
#define ToolGameObject_h__

#include "Engine_Defines.h"
#include "GameObject.h"

#include "Collider.h"

class CToolGameObject : public Engine::CGameObject
{
protected:
	explicit				CToolGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CToolGameObject(const CToolGameObject& rhs);
	virtual					~CToolGameObject(void);

public:
	virtual HRESULT			Initialize_GameObject(void) PURE;
	virtual HRESULT			Late_Initialize(void) PURE;

	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) PURE;
	virtual void			Render_GameObject(void) PURE;

protected:
	Engine::CCollider*		m_pCollider;

public:
	virtual CGameObject*	Clone(void) PURE;
	virtual void			SaveData(HANDLE hFile) PURE;
	virtual void			LoadData(HANDLE hFile) PURE;

protected:
	inline virtual void		Free(void) override;
};

#endif // ToolGameObject_h__
