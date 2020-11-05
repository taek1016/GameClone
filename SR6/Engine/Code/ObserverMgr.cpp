#include "ObserverMgr.h"
#include "Observer.h"

USING(Engine)
IMPLEMENT_SINGLETON(CObserverMgr)

CObserverMgr::CObserverMgr(void)
{

}

CObserverMgr::~CObserverMgr(void)
{
	freeMem();
}

HRESULT CObserverMgr::Add_Observer(const _tchar* pObserverKey, CObserver* pObserver)
{
	NULL_CHECK_RETURN_MSG(pObserver, E_FAIL, L"Observer is nullptr");

	auto iter = find_if(m_mapObserver.begin(), m_mapObserver.end(), CTag_Finder(pObserverKey));

	if (m_mapObserver.end() != iter)
	{
		return E_FAIL;
	}

	m_mapObserver.insert(make_pair(pObserverKey, pObserver));

	return S_OK;
}

void CObserverMgr::Notify(const _tchar* pObserverKey, _int iMessage, void* pData)
{
	NULL_CHECK_MSG(pData, L"ObserverMgr Notify data is nullptr");

	auto iter = find_if(m_mapObserver.begin(), m_mapObserver.end(), CTag_Finder(pObserverKey));

	if (m_mapObserver.end() == iter)
	{
		MSG_BOX("ObserverMgr Notify Fails map container not contains observer");
		return;
	}

	iter->second->Notify(iMessage, pData);
}

void CObserverMgr::Subscribe(const _tchar* pObserverKey, CContent* pContent)
{
	NULL_CHECK(pContent);

	auto iter_find = m_mapObserver.find(pObserverKey);

	if (m_mapObserver.end() == iter_find)
	{
		return;
	}

	iter_find->second->Subscribe(pContent);

}

void CObserverMgr::Unsubscribe(const _tchar* pObserverKey, CContent* pContent)
{
	NULL_CHECK(pContent);

	auto iter_find = m_mapObserver.find(pObserverKey);

	if (m_mapObserver.end() == iter_find)
		return;

	iter_find->second->UnSubscribe(pContent);
}

void CObserverMgr::freeMem(void)
{
	for_each(m_mapObserver.begin(), m_mapObserver.end(), CDeleteMap());
	m_mapObserver.clear();
}

