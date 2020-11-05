#ifndef GameObject_h__
#define GameObject_h__

#include "Engine_Defines.h"
#include "Base.h"

#include "Component.h"

BEGIN(Engine)

class CWeaponBase;
class CArmorBase;
class CComponent;
class CUsableBase;

class ENGINE_DLL CGameObject : public CBase
{
protected:
	explicit					CGameObject();
	explicit					CGameObject(const CGameObject& rhs);
	virtual						~CGameObject();

	vector<CGameObject*>		m_vecChildObject;
	bool						m_bIsChild;

public:
	template<typename T>
	T* Get_Component(const _int iComponentTag, COMPONENTID eID)
	{
		auto iter = Find_Component(iComponentTag, eID);

		if (nullptr == iter)
		{
			return nullptr;
		}

		return dynamic_cast<T*>(iter);
	}

	virtual void				Attack(const _float& fTimeDelta);
	virtual void				Use_Item() { };

	virtual HRESULT				Late_Initialize(void) { return S_OK; };
	virtual HRESULT				Initialize_GameObject(void);
	virtual _int				Update_GameObject(const _float& fTimeDelta);
	virtual void				Render_GameObject(void);

	virtual void				Get_Heal(CUsableBase* pItem) { ; }
	const _tchar*				Get_Name(void) const;
	virtual const _float&		Get_Damage(void) { return m_fDamage; }
	virtual void				Take_Damage(const _float& fDamage) { ; }

	HRESULT						Add_Component(const _int iComponentTag, CComponent * pComponent, COMPONENTID com_id);

	virtual void				Set_Weapon(CWeaponBase* pWeapon);
	virtual void				Set_Armor(CArmorBase* pArmor) {}
	virtual void				Set_Dead() { m_bDead = true; }

	void						AddChildObject(CGameObject* obj);

	CGameObject*				GetChildObject(const _tchar* strName);			////

	vector<CGameObject*>		GetChildObjects();

	virtual void				LoadData(HANDLE hFile) PURE;

	IS_MONSTER					Get_Type(void) const { return m_eType; }

protected:
	

	CComponent*					Find_Component(const _int iComponentTag, COMPONENTID eID);
	void						SetName(const _tchar* pKey);

	vector<CComponent*>			m_vecComponent[COMPONENTID::ID_END];

	_bool						m_bDead = false;
	_int						m_iCloneNum;
	_float						m_fDamage;

	CWeaponBase*				m_pWeapon = nullptr;
	CArmorBase*					m_pArmorBase = nullptr;

	IS_MONSTER					m_eType = IS_MONSTER::OBJ_END;

private:
	bool						m_bClone = false;
	wstring						m_wStrObjName;

public:
	virtual CGameObject*		Clone(const _vec3* pPos = nullptr) PURE;
	virtual CGameObject*		Clone(void) { return nullptr; }

protected:
	virtual void				freeMem(void);
};

END
#endif // GameObject_h__