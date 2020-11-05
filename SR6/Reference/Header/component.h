#ifndef Component_h__
#define Component_h__

#include "Engine_Defines.h"
#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)
class CGameObject;
class ENGINE_DLL CComponent : public CBase
{
protected:
	explicit				CComponent(void);
	explicit				CComponent(const CComponent& rhs);
	virtual					~CComponent(void);

public:
	virtual HRESULT			Late_Initialize() { return S_OK; };
	virtual HRESULT			Initialize_Component() { return S_OK; };
	virtual _int			Update_Component(const _float& fTimeDelta) { return 0; }

protected:
	void					Set_ComType(COMPONENT_TYPE eType);

	CGameObject*			m_pGameObject = nullptr;
	COMPONENT_TYPE			m_eComType = COMPONENT_TYPE::COMP_TYPE_END;

public:
	virtual CComponent*		Clone() { return nullptr; }
	virtual HRESULT			Attach(CGameObject* pObj, COMPONENTID com_ID) { return S_OK; }
	
	virtual void			LoadData(HANDLE hFile) {}

	void					SetGameObject(CGameObject* obj) { m_pGameObject = obj; }
protected:
	virtual void			freeMem(void);
};

END
#endif // Component_h__
