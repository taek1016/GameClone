#include "PoolMgr.h"

#include "Gameobject.h"

USING(Engine)
IMPLEMENT_SINGLETON(CPoolMgr)
CPoolMgr::~CPoolMgr(void)
{
	freeMem();
}

HRESULT CPoolMgr::Add_Pool(const _int& iCurType, CGameObject * pObj)
{
	if (iCurType >= m_iMaxPoolType)
	{
		return E_FAIL;
	}

	for (_int i = 0; i < m_iPoolSize; ++i)
	{
		m_vecPool[iCurType].push_back(pObj->Clone(nullptr));
	}
	m_vecOriginalPool[iCurType] = pObj;

	for (auto iter : m_vecPool[iCurType])
	{
		iter->Late_Initialize();
	}

	return S_OK;
}

HRESULT CPoolMgr::Initialize_Pool(const _int& iPoolType, const _int & iPoolSize)
{
	m_iPoolSize = iPoolSize;
	m_iMaxPoolType = iPoolType;

	m_vecPool.resize(m_iMaxPoolType);
	m_vecOriginalPool.resize(m_iMaxPoolType);

	return S_OK;
}

HRESULT CPoolMgr::Back_Pool(const _int& iPoolType, CGameObject* pObj)
{
	if (iPoolType >= m_iMaxPoolType)
	{
		return E_FAIL;
	}

	m_vecPool[iPoolType].push_back(pObj);

	return S_OK;
}

inline void CPoolMgr::freeMem()
{
	for (auto iterList : m_vecPool)
	{
		for (auto iter : iterList)
		{
			Safe_Release(iter);
		}
		iterList.clear();
	}

	for (auto iter : m_vecOriginalPool)
	{
		Safe_Release(iter);
	}
	m_vecOriginalPool.clear();
}
