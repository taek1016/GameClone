#ifndef Weapon_h__
#define Weapon_h__

#include "ItemBase.h"

BEGIN(Engine)

class ENGINE_DLL CWeaponBase : public CItemBase
{
protected:
	explicit				CWeaponBase(void);
	explicit				CWeaponBase(const CWeaponBase& rhs);
	virtual					~CWeaponBase(void);

public:
	virtual HRESULT			Late_Initialize() PURE;
	virtual HRESULT			Initialize_GameObject() PURE;
	virtual _int			Update_GameObject(const _float& fTimeDelta);
	virtual void			Render_GameObject() PURE;

	virtual void			Attack(const _float& fTimeDelta) PURE;

protected:
	_int					m_iDamage;
	_vec3					m_vSidePos;

public:
	virtual CGameObject*	Clone(const _vec3* pPos) PURE;
	virtual void			Set_Obj(CGameObject* pOwnObj);

	virtual void			LoadData(HANDLE hFile) PURE;
};

END

#endif // Weapon_h__
