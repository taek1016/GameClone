#include "stdafx.h"
#include "ToolObjMgr.h"

#include "GameObject.h"
#include "ToolObjContainer.h"


USING(Engine)
IMPLEMENT_SINGLETON(CToolObjMgr)

CToolObjMgr::CToolObjMgr(void)
	: m_pPrefabObj(nullptr)
{
}

CToolObjMgr::~CToolObjMgr(void)
{
	for (auto iter : m_mapObjList)
	{
		Safe_Release(iter.second);
	}
	m_mapObjList.clear();

	for_each(m_mapPrefab.begin(), m_mapPrefab.end(), CDeleteMap());
	m_mapPrefab.clear();
}

void CToolObjMgr::Update(const float fTimeDelta)
{
	for (auto iter : m_mapObjList)
	{
		iter.second->Update(fTimeDelta);
	}

	if (m_pPrefabObj)
	{
		m_pPrefabObj->Update_GameObject(fTimeDelta);
	}
}

void CToolObjMgr::Render(void)
{
	DLL::pGraphicDev->Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	for (auto iter : m_mapObjList)
	{
		iter.second->Render();
	}

	if (m_pPrefabObj)
	{
		m_pPrefabObj->Render_GameObject();
	}

	DLL::pGraphicDev->Render_End();
}

void CToolObjMgr::Add_ObjList(const Engine::_tchar * pType, const Engine::_tchar * pKey, Engine::CGameObject * pObj)
{
	auto iter = find_if(m_mapObjList.begin(), m_mapObjList.end(), CTag_Finder(pType));

	if (m_mapObjList.end() == iter)
	{
		m_mapObjList.insert(make_pair(pType, new CToolObjContainer));
		m_mapObjList.find(pType)->second->Add_Obj(pKey, pObj);
	}
	else
	{
		(iter->second)->Add_Obj(pKey, pObj);
	}
}

Engine::CGameObject* CToolObjMgr::Add_Prefab(const Engine::_tchar* pKey, Engine::CGameObject* pObj)
{
	auto iter = find_if(m_mapPrefab.begin(), m_mapPrefab.end(), CTag_Finder(pKey));

	if (m_mapPrefab.end() != iter)
	{
		return nullptr;
	}
	m_mapPrefab.insert(make_pair(pKey, pObj));

	return pObj;
}

void CToolObjMgr::Delete_Obj(const Engine::_tchar* pType, const Engine::_tchar * pKey)
{
	auto iter = find_if(m_mapObjList.begin(), m_mapObjList.end(), CTag_Finder(pType));

	if (m_mapObjList.end() == iter)
	{
		return;
	}

	iter->second->Delete_Obj(pKey);
}

void CToolObjMgr::Set_PrefabObj(const Engine::_tchar * pKey)
{
	auto iter = find_if(m_mapPrefab.begin(), m_mapPrefab.end(), Engine::CTag_Finder(pKey));

	if (m_mapPrefab.end() == iter)
	{
		return;
	}

	m_pPrefabObj = iter->second;
}

Engine::CGameObject * CToolObjMgr::Get_CurPrefabObj(void)
{
	return m_pPrefabObj;
}

void CToolObjMgr::Cancel_PrefabObj(void)
{
	m_pPrefabObj = nullptr;
}

Engine::CGameObject * CToolObjMgr::Clone(const Engine::_tchar * pKey)
{
	auto iter = find_if(m_mapPrefab.begin(), m_mapPrefab.end(), Engine::CTag_Finder(pKey));

	if (m_mapPrefab.end() == iter)
	{
		return nullptr;
	}

	return (iter->second->Clone());
}

const map<const Engine::_tchar*, Engine::CGameObject*>* CToolObjMgr::Get_Map(const Engine::_tchar * pKey)
{
	auto iter = find_if(m_mapObjList.begin(), m_mapObjList.end(), CTag_Finder(pKey));

	if (m_mapObjList.end() == iter)
	{
		return nullptr;
	}

	return iter->second->Get_Map();
}

const map<const Engine::_tchar*, Engine::CGameObject*>* CToolObjMgr::Get_PrefabMap(void)
{
	return &m_mapPrefab;
}
