#ifndef Component_h__
#define Component_h__

#include "Engine_Defines.h"
#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CComponent : public CBase
{
protected:
	explicit				CComponent(void);
	explicit				CComponent(const CComponent& rhs);
	virtual					~CComponent(void);

public:
	virtual HRESULT			Late_Initialize() { return S_OK; };
	virtual HRESULT			Initialize_Component() { return S_OK; };
	virtual _int			Update_Component(const _float& fTimeDelta) { fTimeDelta; return 0; };

protected:
	CGameObject*			m_pGameObject = nullptr;

public:
	virtual CComponent*		Clone() PURE;
	virtual HRESULT			Attach(const _tchar* pKey, CGameObject* pObj, COMPONENTID com_ID);

protected:
	inline virtual void		Free(void) override;
};

END
#endif // Component_h__