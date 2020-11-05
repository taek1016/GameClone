#include "ObjPool.h"

#include "Gameobject.h"

USING(Engine)
IMPLEMENT_SINGLETON(CPoolMgr)

CPoolMgr::~CPoolMgr(void)
{
	Free();
}

HRESULT CPoolMgr::Add_Pool(const _tchar* pKey, CGameObject* pObj)
{
	if (find_Pool(pKey) != nullptr)
	{
		return E_FAIL;
	}

	m_mapOriginalPool.insert(make_pair(pKey, pObj));
	list<CGameObject*>*	pList = new list<CGameObject*>;
	for (_int i = 0; i < m_iPoolSize; ++i)
	{
		pList->push_back(pObj->Clone());
	}
	m_mapPool.insert(make_pair(pKey, pList));

	return S_OK;
}

HRESULT CPoolMgr::Back_Pool(const _tchar* pKey, CGameObject* pObj)
{
	list<CGameObject*>* pList = find_List(pKey);

	if (nullptr == pList)
	{
		return E_FAIL;
	}

	pList->push_back(pObj);

	return S_OK;
}

CGameObject* CPoolMgr::Get_Pool(const _tchar* pKey)
{
	list<CGameObject*>*	pList = find_List(pKey);
	
	if (nullptr == pList)
	{
		return nullptr;
	}

#pragma region If_Empty
	if (pList->empty())
	{
		CGameObject* pOrigin = find_Pool(pKey);
		for (_int i = 0; i < m_iPoolSize; ++i)
		{
			pList->push_back(pOrigin->Clone());
		}
	}
#pragma endregion

#pragma region Get_Obj
	CGameObject* pObj = pList->front();
	pObj->Set_Initialze();
	pList->pop_front();
#pragma endregion

	return pObj;
}

CGameObject* CPoolMgr::find_Pool(const _tchar* pKey)
{
	auto iter = find_if(m_mapOriginalPool.begin(), m_mapOriginalPool.end(), CTag_Finder(pKey));

	if (m_mapOriginalPool.end() == iter)
	{
		return nullptr;
	}

	return m_mapOriginalPool[pKey];
}

list<CGameObject*>* CPoolMgr::find_List(const _tchar* pKey)
{
	if (nullptr == find_Pool(pKey))
	{
		return nullptr;
	}

	return m_mapPool[pKey];
}

inline void CPoolMgr::Free()
{
	for_each(m_mapOriginalPool.begin(), m_mapOriginalPool.end(), CDeleteMap());
	m_mapOriginalPool.clear();

	for (auto iter : m_mapPool)
	{
		for_each(iter.second->begin(), iter.second->end(), CDeleteObj());
		Safe_Delete(iter.second);
	}
	m_mapPool.clear();
}