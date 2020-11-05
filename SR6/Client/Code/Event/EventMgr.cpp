#include "stdafx.h"
#include "EventMgr.h"

#include "SingleEvent.h"

USING(Engine)
IMPLEMENT_SINGLETON(CEventMgr)

CEventMgr::CEventMgr(void)
{
}

CEventMgr::~CEventMgr(void)
{
	freeMem();
}

void CEventMgr::Register_Event(const Engine::_tchar* pKey, CSingleEvent* pEvent)
{
	auto iter = find_if(m_mapEvent.begin(), m_mapEvent.end(), CTag_Finder(pKey));

	if (m_mapEvent.end() != iter)
	{
		return;
	}

	m_mapEvent.emplace(make_pair(pKey, pEvent));
}

void CEventMgr::Update_Event(const Engine::_float & fTimeDelta)
{
	// 각 이벤트 업데이트
	for (auto iter : m_mapEvent)
	{
		iter.second->Update_Event(fTimeDelta);
	}
}

void CEventMgr::Activate_Mgr(const Engine::_tchar* pKey)
{
	auto iter = find_if(m_mapEvent.begin(), m_mapEvent.end(), CTag_Finder(pKey));

	if (m_mapEvent.end() == iter)
	{
		return;
	}

	// 이벤트 활성화
	m_mapEvent[pKey]->Activate_Event();
}

inline void CEventMgr::freeMem()
{
	for_each(m_mapEvent.begin(), m_mapEvent.end(), CDeleteMap());
	m_mapEvent.clear();
}