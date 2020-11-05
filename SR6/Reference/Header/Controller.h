#ifndef Controller_h__
#define Controller_h__

#include "Engine_Defines.h"
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CController : public CComponent
{
protected:
	explicit				CController(void);
	virtual					~CController(void);

public:
	virtual HRESULT			Late_Initialize() PURE;
	virtual HRESULT			Initialize_Component() PURE;
	virtual _int			Update_Component(const _float& fTimeDelta) PURE;

	virtual HRESULT			Attach(CGameObject* pObj, COMPONENTID com_ID);

protected:
	inline virtual void		freeMem();
};

END

#endif // Controller_h__
