#ifndef UsableBase_h__
#define UsableBase_h__

#include "ItemBase.h"

BEGIN(Engine)

class ENGINE_DLL CUsableBase : public CItemBase
{
protected:
	explicit	CUsableBase(void);
	explicit	CUsableBase(const CUsableBase& rhs);
	virtual		~CUsableBase(void);

public:
	virtual HRESULT		Late_Initialize() PURE;
	virtual HRESULT		Initialize_GameObject() PURE;
	virtual _int		Update_Component(const _float& fTimeDelta);

	virtual void		Use();

protected:
	_int				m_iHungry = 0;
	_int				m_iHeal = 0;
	_int				m_iHydrate = 0;

public:
	virtual CGameObject* Clone(const _vec3* pPos) PURE;
	virtual void		Set_Item(CGameObject* pObj);

	virtual void		LoadData(HANDLE hFile) PURE;
};

END

#endif // UsableBase_h__
