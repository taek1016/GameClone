#include "stdafx.h"
#include "CraftingMgr.h"

#include "ItemBase.h"
#include "CraftingUI.h"
#include "CraftingFont.h"

USING(Engine)
IMPLEMENT_SINGLETON(CCraftingMgr)

CCraftingMgr::CCraftingMgr(void)
{
}

CCraftingMgr::~CCraftingMgr(void)
{
}

void CCraftingMgr::Register_Crafting(const Engine::_tchar * pKey, CCrafting * pCraft)
{
	auto iter = find_if(m_mapCraft.begin(), m_mapCraft.end(), CTag_Finder(pKey));

	if (m_mapCraft.end() != iter)
	{
		return;
	}

	m_mapCraft.emplace(pKey, pCraft);
}

void CCraftingMgr::Update_Crafting(const Engine::_float & fDelta)
{
	if (!m_bActivate)
	{
		return;
	}
	m_pCraftFont->Update_GameObject(fDelta);

	m_fCurTime += fDelta;
	if (m_fCurTime >= m_fEndTime)
	{
		m_fCurTime = 0.f;
		m_bActivate = false;
		return;
	}
	if (!m_bCanMake)
	{
		// 불가능하다는 메시지.
		m_pCraftFont->Set_Failed();
	}
	else
	{
		m_pCraftFont->Set_Succeed();
	}

}

Engine::_bool CCraftingMgr::Make_Item(const Engine::_tchar * pKey, const INSTALL_TYPE& eType)
{
	_int iNeedWood, iNeedIron;
	m_mapCraft[pKey]->Get_NeedMaterial(&iNeedWood, &iNeedIron);

	m_pItem = m_mapCraft[pKey]->Make_Item(DLL::pInventory->Get_Material(MATERIAL_TYPE::MATERIAL_WOOD), DLL::pInventory->Get_Material(MATERIAL_TYPE::MATERIAL_STONE));
	if (nullptr != m_pItem)
	{
		DLL::pSoundMgr->PlaySound(L"Crafting.mp3", CSoundMgr::CHANNEL_ID::EFFECT);
		DLL::pInventory->Remove_Material(MATERIAL_WOOD, iNeedWood);
		DLL::pInventory->Remove_Material(MATERIAL_STONE, iNeedIron);

		m_eType = eType;
		m_bCanMake = true;
		return true;
	}
	else
	{
		m_bCanMake = false;
	}
	m_bActivate = true;

	return false;
}

HRESULT CCraftingMgr::Initialize_Crafting(void)
{
	m_pCraftFont = CCraftFont::Create();
	m_pCraftFont->Initialize_GameObject();

	return S_OK;
}

void CCraftingMgr::Set_Activate()
{
	m_bActivate = true; 
	m_bCanMake = true; 		
}

void CCraftingMgr::Finish_Craft()
{
	DLL::pInventory->Add_InstallItem(m_eType, m_pItem);
	m_bActivate = false;
	m_pItem = nullptr;
}

Engine::CGameObject * CCraftingMgr::Clone(const INSTALL_TYPE & eType)
{
	CGameObject* pInstance = nullptr;

	switch (eType)
	{
	case INSTALL_WALL:
		pInstance = m_mapCraft[L"Barricade"]->Clone();
		break;
	case INSTALL_MACHINE_GUN:
		pInstance = m_mapCraft[L"Turret"]->Clone();
		break;
	}
	return pInstance;
}

inline void CCraftingMgr::freeMem(void)
{
	for_each(m_mapCraft.begin(), m_mapCraft.end(), CDeleteMap());
	m_mapCraft.clear();

	m_pItem = nullptr;
}
