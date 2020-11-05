#ifndef ArmorBase_h__
#define ArmorBase_h__

#include "ItemBase.h"

BEGIN(Engine)

class CItemBase;

class ENGINE_DLL CArmorBase : public CItemBase
{
protected:
	explicit		CArmorBase(void);
	explicit		CArmorBase(const CArmorBase& rhs);
	virtual			~CArmorBase(void);

public:
	virtual HRESULT		Late_Initialize() PURE;
	virtual HRESULT		Initialize_GameObject() PURE;
	virtual _int		Update_GameObject(const _float& fTimeDelta);
	
	virtual void		Set_Item(CGameObject* pObj);

protected:
	_int				m_iArmor;

public:
	virtual CGameObject* Clone(const _vec3* pPos) PURE;

	virtual void		LoadData(HANDLE hFile) PURE;
};

END
#endif // ArmorBase_h__
