#include "stdafx.h"
#include "ComponentMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CComponentMgr)

CComponentMgr::CComponentMgr(void)
	: CBase()
{
	Add_Component(L"Transform", CTransform::Create());
}

CComponentMgr::~CComponentMgr(void)
{
	Free();
}

HRESULT CComponentMgr::Add_Component(const Engine::_tchar* pKey, Engine::CComponent* pCom)
{
	auto iter = m_mapComponent.find(pKey);

	if (m_mapComponent.end() != iter)
	{
		return E_FAIL;
	}

	m_mapComponent.emplace(pKey, pCom);

	return S_OK;
}

inline void CComponentMgr::Free(void)
{
	for (auto iter : m_mapComponent)
	{
		Safe_Release(iter.second);
	}
	m_mapComponent.clear();
}
