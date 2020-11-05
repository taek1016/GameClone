#include "stdafx.h"
#include "Inventory.h"

#include "WeaponSlot.h"
#include "MaterialSlot.h"
#include "InstallSlot.h"

#include "Rifle.h"
#include "ShotGun.h"
#include "ChainSaw.h"
#include "ItemBase.h"
#include "WeaponBase.h"

USING(Engine)
IMPLEMENT_SINGLETON(CInventory)

CInventory::CInventory(void)
{
	
}

CInventory::~CInventory(void)
{
	freeMem();
}

void CInventory::Initialize_Inventory()
{
	m_vecWeaponSlots.resize(WEAPON::WEAPON_END);

	_vec3 vPos;

	CItemBase*	pItems[WEAPON_END] = { CRifle::Create(), CShotGun::Create(), CChainSaw::Create() };

	vPos.y = 225.f;
	vPos.z = 0.f;
	for (_int i = 0; i < static_cast<_int>(WEAPON_END); ++i)
	{
		// vPos 위치 잡기.
		vPos.x = -350.f + 80.f * i;
		m_vecWeaponSlots[i] = CWeaponSlot::Create(&vPos, pItems[i]);
	}

	m_vecWeaponSlots[0]->Activate_Slot();

	m_vecMaterialSlots.resize(MATERIAL_TYPE::MATERIAL_END);

	vPos.x = -350.f;
	for (_int i = 0; i < static_cast<_int>(MATERIAL_END); ++i)
	{
		vPos.y = 75 - 100.f * i;
		m_vecMaterialSlots[i] = CMaterialSlot::Create(&vPos, static_cast<MATERIAL_TYPE>(i));
	}

	m_vecInstallSlots.resize(INSTALL_TYPE::INSTALL_END);

	vPos.x = 350.f;
	for (_int i = 0; i < static_cast<_int>(INSTALL_END); ++i)
	{
		vPos.y = 75 - 100.f * i;
		m_vecInstallSlots[i] = CInstallSlot::Create(&vPos, static_cast<INSTALL_TYPE>(i));
	}
	for (auto iter : m_vecWeaponSlots)
	{
		iter->Late_Initialize();
	}

	for (auto iter : m_vecMaterialSlots)
	{
		iter->Late_Initialize();
	}

	for (auto iter : m_vecInstallSlots)
	{
		iter->Late_Initialize();
	}

	Activate_Item(0);
}

void CInventory::Update_Inventory(const Engine::_float & fTimeDelta)
{
	for (auto iter : m_vecWeaponSlots)
	{
		iter->Update_GameObject(fTimeDelta);
	}

	for (auto iter : m_vecMaterialSlots)
	{
		iter->Update_GameObject(fTimeDelta);
	}

	for (auto iter : m_vecInstallSlots)
	{
		iter->Update_GameObject(fTimeDelta);
	}
}

void CInventory::Activate_Item(const Engine::_int & iIdx)
{
	for (auto iter : m_vecWeaponSlots)
	{
		iter->Deactivate_Slot();
	}
	m_vecWeaponSlots[iIdx]->Activate_Slot();

	DLL::pSoundMgr->PlaySound(L"Equip.mp3", CSoundMgr::EFFECT);

	CGameObject* pPlayer = DLL::pSearchMgr->Get_Object(L"Player");
	pPlayer->Set_Weapon(dynamic_cast<CWeaponBase*>(m_vecWeaponSlots[iIdx]->Get_Item()));
}

Engine::_int CInventory::Get_Material(const MATERIAL_TYPE & eType)
{
	if (eType >= MATERIAL_END)
	{
		return -1;
	}
	return m_vecMaterialSlots[eType]->Get_MaterialNum();
}

void CInventory::Add_InstallItem(const INSTALL_TYPE& eType, CGameObject* pObj)
{
	if (eType >= INSTALL_TYPE::INSTALL_END)
	{
		return;
	}

	if (nullptr != pObj)
	{
		m_vecInstallSlots[eType]->Add_Install(pObj);
	}
}

CPickableObject* CInventory::Get_InstallItem(const INSTALL_TYPE & eType)
{
	return dynamic_cast<CPickableObject*>(m_vecInstallSlots[eType]->Get_Install());
}

void CInventory::Add_Material(const MATERIAL_TYPE& eType)
{
	if (eType >= MATERIAL_END)
	{
		return;
	}
	m_vecMaterialSlots[eType]->Add_MaterialNum();
}

void CInventory::Remove_Material(const MATERIAL_TYPE & eType, const Engine::_int iCnt)
{
	if (eType >= MATERIAL_END)
	{
		return;
	}
	m_vecMaterialSlots[eType]->Delete_MaterialNum(iCnt);
}

inline void CInventory::freeMem()
{
	for_each(m_vecWeaponSlots.begin(), m_vecWeaponSlots.end(), CDeleteObj());
	m_vecWeaponSlots.clear();

	for_each(m_vecMaterialSlots.begin(), m_vecMaterialSlots.end(), CDeleteObj());
	m_vecMaterialSlots.clear();

	for_each(m_vecInstallSlots.begin(), m_vecInstallSlots.end(), CDeleteObj());
	m_vecInstallSlots.clear();
}
