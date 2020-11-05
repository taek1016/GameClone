#include "Timer.h"

USING(Engine)

CTimer::CTimer(void)
{
	ZeroMemory(&m_FrameTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_LastTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_FixTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));

}

CTimer::~CTimer(void)
{
	
}

HRESULT CTimer::Ready_Timer(void)
{

	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceCounter(&m_FixTime);

	QueryPerformanceFrequency(&m_CpuTick);

	return S_OK;
}


void CTimer::Set_TimeDelta(void)
{
	QueryPerformanceCounter(&m_FrameTime);


	if (m_FrameTime.QuadPart - m_FixTime.QuadPart >= m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_FixTime = m_FrameTime;
	}


	m_fTimeDelta = (static_cast<_float>(m_FrameTime.QuadPart - m_LastTime.QuadPart)) / (_float)m_CpuTick.QuadPart;

	m_LastTime = m_FrameTime;
}


CTimer* CTimer::Create(void)
{
	CTimer*	pInstance = new CTimer;

	if (FAILED(pInstance->Ready_Timer()))
		Safe_Release(pInstance);

	return pInstance;
}

void CTimer::freeMem(void)
{

}
