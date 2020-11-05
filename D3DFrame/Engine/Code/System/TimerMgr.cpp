#include "TimerMgr.h"

#include "Timer.h"

USING(Engine)
IMPLEMENT_SINGLETON(CTimerMgr)

Engine::CTimerMgr::CTimerMgr(void)
	: CBase()
	, m_bInitialized(false)
{
}

Engine::CTimerMgr::~CTimerMgr(void)
{
	Free();
}

HRESULT Engine::CTimerMgr::Ready_Timer(const _int iTimerTag)
{
	if (false == m_bInitialized)
	{
		return E_FAIL;
	}

	CTimer*		pInstance = Find_Timer(iTimerTag);

	if (nullptr != pInstance)
		return E_FAIL;

	pInstance = CTimer::Create();
	NULL_CHECK_RETURN(pInstance, E_FAIL);

	m_vecTimer[iTimerTag] = pInstance;

	return S_OK;
}

void Engine::CTimerMgr::Free(void)
{
	for_each(m_vecTimer.begin(), m_vecTimer.end(), Safe_Delete<CTimer*>);
	m_vecTimer.clear();
}

CTimer* Engine::CTimerMgr::Find_Timer(const _int iTimerTag)
{
	auto iter = m_vecTimer[iTimerTag];

	if (nullptr == iter)
	{
		return nullptr;
	}

	return iter;
}

void CTimerMgr::Set_TimeDelta(const _int iTimerTag)
{
	CTimer*		pInstance = Find_Timer(iTimerTag);

	if (nullptr == pInstance)
		return;

	pInstance->Set_TimeDelta();
}

_float CTimerMgr::Get_TimeDelta(const _int iTimerTag)
{
	CTimer*		pInstance = Find_Timer(iTimerTag);

	if (nullptr == pInstance)
		return 0.f;

	return pInstance->Get_TimeDelta();
}

void CTimerMgr::Initialize_Timer(const _int iTimerSize)
{
	if (true == m_bInitialized)
	{
		return;
	}

	m_vecTimer.resize(iTimerSize);
	m_bInitialized = true;
}
