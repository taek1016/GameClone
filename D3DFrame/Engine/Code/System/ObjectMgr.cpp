#include "ObjectMgr.h"

#include "GameObject.h"

USING(Engine)
IMPLEMENT_SINGLETON(CObjectMgr)

CObjectMgr::CObjectMgr(void)
	: CBase()
{
}

CObjectMgr::~CObjectMgr(void)
{
	Free();
}

_int CObjectMgr::Update_Objects(const _float& fTimeDelta)
{
	_int iReturnValue = 0;

	list<CGameObject*>* pList = nullptr;
	for (auto iterList = m_ObjList.begin(); iterList != m_ObjList.end(); ++iterList)
	{
		pList = iterList->second;

		for (auto iter = pList->begin(); iter != pList->end(); )
		{
			iReturnValue = (*iter)->Update_GameObject(fTimeDelta);

			if (DEAD_OBJ == iReturnValue)
			{
				Safe_Release(*iter);
				iter = pList->erase(iter);
			}
			else if (BACK_POOL == iReturnValue)
			{
				iter = pList->erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	return 0;
}

HRESULT CObjectMgr::Add_GameObject(const _tchar* pContainerKey, CGameObject* pObj)
{
	auto iter = find_Layer(pContainerKey);

	if (nullptr == iter)
	{
		list<CGameObject*>* pList = new list<CGameObject*>;
		pList->push_back(pObj);
		m_ObjList.push_back(make_pair(pContainerKey, pList));
		pList = nullptr;
	}
	else
	{
		iter->push_back(pObj);
	}

	return S_OK;
}

void CObjectMgr::Clear_List(void)
{
	for (auto iter : m_ObjList)
	{
		for_each(iter.second->begin(), iter.second->end(), CDeleteObj());
		Safe_Delete(iter.second);
	}
	m_ObjList.clear();
}

list<CGameObject*>* CObjectMgr::Get_ObjList(const _tchar* pKey) const
{
	return find_Layer(pKey);
}

HRESULT CObjectMgr::Set_PoolMgr(CPoolMgr * pPool)
{
	if (nullptr != m_pPoolMgr)
	{
		return E_FAIL;
	}

	m_pPoolMgr = pPool;
	return S_OK;
}

list<CGameObject*>* CObjectMgr::find_Layer(const _tchar* pLayerKey) const
{
	auto iter = find_if(m_ObjList.begin(), m_ObjList.end(), CTag_Finder(pLayerKey));

	if (m_ObjList.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

inline void CObjectMgr::Free(void)
{
	Clear_List();
}