#ifndef Inventory_h__
#define Inventory_h__

#include "Engine_Defines.h"
#include "Base.h"

#include "ItemBase.h"
#include "SceneObject/PickableObject.h"

class CWeaponSlot;
class CMaterialSlot;
class CInstallSlot;

class CInventory : public CBase
{
	DECLARE_SINGLETON(CInventory)

private:
	explicit					CInventory(void);
	virtual						~CInventory(void);

public:
	void						Initialize_Inventory();
	void						Update_Inventory(const Engine::_float& fTimeDelta);
	void						Activate_Item(const Engine::_int& iIdx);

	void						Add_Material(const MATERIAL_TYPE& eType);
	void						Remove_Material(const MATERIAL_TYPE& eType, const Engine::_int iCnt);
	Engine::_int				Get_Material(const MATERIAL_TYPE& eType);

	void						Add_InstallItem(const INSTALL_TYPE& eType, Engine::CGameObject* pObj);
	CPickableObject*			Get_InstallItem(const INSTALL_TYPE& eType);
private:
	vector<CWeaponSlot*>	m_vecWeaponSlots;
	vector<CMaterialSlot*>	m_vecMaterialSlots;
	vector<CInstallSlot*>	m_vecInstallSlots;

private:
	inline virtual void		freeMem() override;
};

#endif // Inventory_h__
