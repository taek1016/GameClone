#include "stdafx.h"
#include "ItemMgr.h"

#include "Item/Staff/DefaultStaff.h"
#include "Item/Staff/FinalStaff.h"

USING(Engine)
IMPLEMENT_SINGLETON(CItemMgr)

CItemMgr::CItemMgr(void)
{
}

CItemMgr::~CItemMgr(void)
{
	Free();
}

void CItemMgr::Initialize_Items(LPDIRECT3DDEVICE9& pGraphicDev)
{
	CItemBase* pItem = CDefaultStaff::Create(pGraphicDev);
	add_Item(L"DefaultStaff", pItem, 500);

	pItem = CFinalStaff::Create(pGraphicDev);
	add_Item(L"FinalStaff", pItem, 8000);

	add_Item(L"BlueCloth", nullptr, 5000);
	add_Item(L"MetalPlate", nullptr, 10000);
}

CItemBase * CItemMgr::Clone_Item(const Engine::_tchar * pName)
{
	auto iter = m_mapItems.find(pName);

	if (m_mapItems.end() == iter)
	{
		return nullptr;
	}

	return dynamic_cast<CItemBase*>(iter->second.first->Clone());
}

const Engine::_bool CItemMgr::Is_Item(const Engine::_tchar * pName) const
{
	for (auto iter : m_mapItems)
	{
		if (0 == wcscmp(pName, iter.second.first->Get_Name()))
		{
			return true;
		}
	}
	return false;
}

const Engine::_int CItemMgr::Get_ItemPrice(const Engine::_tchar * pItemName)
{
	auto iter = m_mapItems.find(pItemName);

	if (m_mapItems.end() == iter)
	{
		return 0;
	}

	return iter->second.second;
}

void CItemMgr::add_Item(const Engine::_tchar * pName, CItemBase * pItem, const Engine::_int& iMoney)
{
	auto iterList = m_mapItems.find(pName);

	if (m_mapItems.end() == iterList)
	{
		m_mapItems.emplace(pName, make_pair(pItem, iMoney));

		return;
	}

	if (0 == wcscmp(pItem->Get_Name(), pName))
	{
		return;
	}

	m_mapItems.emplace(pName, make_pair(pItem, iMoney));
}

inline void CItemMgr::Free(void)
{
	for (auto iter : m_mapItems)
	{
		Safe_Release(iter.second.first);
	}
	m_mapItems.clear();
}
