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

HRESULT CTimer::Initialize_Timer(void)
{
#pragma region Initialize_Counter
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceCounter(&m_FixTime);
#pragma endregion

#pragma region Initialize_Frequency
	QueryPerformanceFrequency(&m_CpuTick);
#pragma endregion

	return S_OK;
}

void CTimer::Set_TimeDelta(void)
{
	// 단위 프레임 설정
	QueryPerformanceCounter(&m_FrameTime);

#pragma region Check_OneSec
	if (m_FrameTime.QuadPart - m_FixTime.QuadPart >= m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_FixTime = m_FrameTime;
	}
#pragma endregion

	// 단위 프레임 시간 설정.
	m_fTimeDelta = (m_FrameTime.QuadPart - m_LastTime.QuadPart) / static_cast<_float>(m_CpuTick.QuadPart);

	m_LastTime = m_FrameTime;
}

CTimer * CTimer::Create(void)
{
	CTimer*	pInstance = new CTimer;

	if (FAILED(pInstance->Initialize_Timer()))
		Safe_Release(pInstance);

	return pInstance;
}

void CTimer::Free(void)
{
}