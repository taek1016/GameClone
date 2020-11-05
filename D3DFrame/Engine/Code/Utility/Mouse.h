#ifndef Mouse_h__
#define Mouse_h__

#include "Engine_Defines.h"
#include "Component.h"
#include "GameObject.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CMouse : public CGameObject
{
protected:
	explicit		CMouse(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit		CMouse(const CMouse& rhs);
	virtual			~CMouse(void);

public:
	virtual HRESULT	Late_Initialize() PURE;
	virtual HRESULT	Initialize_GameObject() PURE;
	_int			Update_GameObject(const _float& fTimeDelta) PURE;
};

END

#endif // Mouse_h__