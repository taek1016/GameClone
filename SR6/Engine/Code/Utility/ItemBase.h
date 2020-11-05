#ifndef ItemBase_h__
#define ItemBase_h__

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CItemBase : public CGameObject
{
protected:
	explicit				CItemBase(void);
	explicit				CItemBase(const CItemBase& rhs);
	virtual					~CItemBase(void);

public:
	virtual HRESULT			Late_Initialize() PURE;
	virtual HRESULT			Initialize_GameObject() PURE;
	virtual _int			Update_GameObject(const _float& fTimeDelta) PURE;
	
	void					Set_Pos(const _vec3* pPos);
protected:
	COMPONENT_TYPE			m_eComType = COMPONENT_TYPE::COMP_TYPE_END;
	CGameObject*			m_pGameObject = nullptr;

public:
	virtual CGameObject*	Clone(const _vec3* pPos) PURE;
	virtual void			Set_Obj(CGameObject* pObj) PURE;

	virtual void			LoadData(HANDLE hFile) PURE;

protected:
	virtual void			freeMem(void);
};

END
#endif // ItemBase_h__
