#include "CObjContainerMgr.h"

#include "GameObject.h"
#include "Engine_Entry.h"

USING(Engine)
IMPLEMENT_SINGLETON(CObjContainerMgr)

CObjContainerMgr::CObjContainerMgr(void)
{
	m_pObjMgr		= Ready_ObjMgr();
	m_pSearchMgr	= Ready_SearchMgr();
}

CObjContainerMgr::~CObjContainerMgr(void)
{
	freeMem();
}

HRESULT CObjContainerMgr::Initialize_Managers(const _int & iMapNum, const _int & iObjType, const _float& fDistance)
{
	m_pObjMgr->SetUp_ObjectMgr(iMapNum, iObjType);
	m_pSearchMgr->Initialize_SearchMgr(iMapNum);

	return S_OK;
}

HRESULT CObjContainerMgr::Add_Objects(const _tchar * pKey, CGameObject* pObj)
{
	auto iter = find_if(m_mapContainer.begin(), m_mapContainer.end(), CTag_Finder(pKey));

	if (m_mapContainer.end() != iter)
	{
		return E_FAIL;
	}

	m_mapContainer.insert(make_pair(pKey, pObj));

	return S_OK;
}

CGameObject* CObjContainerMgr::Clone(const _int iMapNum, const _int& iObjTag, const _tchar* pKey, const _vec3* pPos)
{
	auto iter = find_if(m_mapContainer.begin(), m_mapContainer.end(), CTag_Finder(pKey));

	if (m_mapContainer.end() == iter)
	{
		return nullptr;
	}

	CGameObject* pInstance = iter->second->Clone(pPos);

	m_pObjMgr->Add_GameObject(iMapNum, iObjTag, pInstance);
	m_pSearchMgr->Add_Object(pInstance->Get_Name(), pInstance);

	pInstance->Late_Initialize();

	return pInstance;
}

inline void CObjContainerMgr::freeMem()
{
	_int iMapSize = m_mapContainer.size();
	for (auto iter : m_mapContainer)
	{
		Safe_Release(iter.second);
	}
	//for_each(m_mapContainer.begin(), m_mapContainer.end(), CDeleteMap());
	m_mapContainer.clear();
}