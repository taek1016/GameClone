#include "stdafx.h"
#include "Crafting.h"

#include "ItemBase.h"
#include "WeaponSlot.h"

USING(Engine)

CCrafting::CCrafting(void)
{
}

CCrafting::~CCrafting(void)
{
}

Engine::CGameObject* CCrafting::Make_Item(const _int& iWoodCnt, const _int& iIronCnt)
{
	if (Can_Make(iWoodCnt, iIronCnt))
	{
		return (m_pItem->Clone(nullptr));
	}

	return nullptr;
}

void CCrafting::Setup_Craft(Engine::CGameObject* pItem, const Engine::_int iNeedWood, const Engine::_int iNeedIron)
{
	m_pItem = pItem;

	m_iWoodCnt = iNeedWood;
	m_iIronCnt = iNeedIron;
}

void CCrafting::Get_NeedMaterial(_int* pWood, _int* pIron)
{
	*pWood = m_iWoodCnt;
	*pIron = m_iIronCnt;
}

Engine::CGameObject * CCrafting::Clone(void)
{
	return m_pItem->Clone(nullptr);
}

Engine::_bool CCrafting::Can_Make(const _int& iWoodCnt, const _int& iIronCnt)
{
	if (iWoodCnt < m_iWoodCnt || iIronCnt < m_iIronCnt)
	{
		return false;
	}
	return true;
}

CCrafting * CCrafting::Create(void)
{
	return new CCrafting;
}

inline void CCrafting::freeMem(void)
{
	Safe_Release(m_pItem);
}
