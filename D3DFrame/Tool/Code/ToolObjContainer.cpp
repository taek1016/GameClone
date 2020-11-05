#include "stdafx.h"
#include "ToolObjContainer.h"

USING(Engine)

CToolObjContainer::CToolObjContainer(void)
{
}

CToolObjContainer::~CToolObjContainer(void)
{
}

void CToolObjContainer::Update(const float fTimeDelta)
{
	for (auto iter : m_mapObjContainer)
	{
		iter.second->Update_GameObject(fTimeDelta);
	}
}

void CToolObjContainer::Render(void)
{
	for (auto iter : m_mapObjContainer)
	{
		iter.second->Render_GameObject();
	}
}

CGameObject* CToolObjContainer::Get_Obj(const Engine::_tchar * pKey)
{
	auto iter = find_if(m_mapObjContainer.begin(), m_mapObjContainer.end(), CTag_Finder(pKey));

	if (m_mapObjContainer.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

void CToolObjContainer::Add_Obj(const Engine::_tchar * pKey, CGameObject * pObj)
{
	auto iter = find_if(m_mapObjContainer.begin(), m_mapObjContainer.end(), CTag_Finder(pKey));

	if (m_mapObjContainer.end() != iter)
	{
		return;
	}

	m_mapObjContainer.insert(make_pair(pKey, pObj));
}

void CToolObjContainer::Delete_Obj(const Engine::_tchar * pKey)
{
	auto iter = find_if(m_mapObjContainer.begin(), m_mapObjContainer.end(), CTag_Finder(pKey));

	if (m_mapObjContainer.end() == iter)
	{
		return;
	}

	Engine::Safe_Release(iter->second);
	m_mapObjContainer.erase(iter);
}

const map<const Engine::_tchar*, Engine::CGameObject*>* CToolObjContainer::Get_Map(void)
{
	return &m_mapObjContainer;
}

inline void CToolObjContainer::Free(void)
{
	for (auto iter : m_mapObjContainer)
	{
		Safe_Release(iter.second);
	}
}
