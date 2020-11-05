#include "stdafx.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr()
	: m_fDeltaTime(0.f)
	, m_fTimeScale(0.f)
	
	, m_liOldTimeOne()
	, m_liOldTimeTwo()
	, m_liCurTime()
	, m_liCpuTick()
{
	AssertMember();

	QueryPerformanceCounter(&m_liOldTimeOne);
	QueryPerformanceCounter(&m_liOldTimeTwo);
	QueryPerformanceCounter(&m_liCurTime);
	QueryPerformanceFrequency(&m_liCpuTick);

	m_fTimeScale = 1.f;
}

CTimeMgr::~CTimeMgr()
{
	AssertMember();
}

const float CTimeMgr::GetDelta() const
{
	return m_fDeltaTime * m_fTimeScale;
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_liCurTime);

	// 일정 시간이 지날 때마다 CPU 진동수 갱신
	if (m_liCurTime.QuadPart - m_liOldTimeTwo.QuadPart > m_liCpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_liCpuTick);
		m_liOldTimeTwo = m_liCurTime;
	}

	m_fDeltaTime = float(m_liCurTime.QuadPart - m_liOldTimeOne.QuadPart) / m_liCpuTick.QuadPart;
	m_liOldTimeOne = m_liCurTime;
}

void CTimeMgr::SetTimeScale(float fScale)
{
	m_fTimeScale = fScale;
	if (0.f > m_fTimeScale)
	{
		m_fTimeScale = 0.f;
	}
	else if (m_fTimeScale >= 1.f)
	{
		m_fTimeScale = 1.f;
	}
}

void CTimeMgr::AssertMember()
{
	m_liCpuTick.QuadPart = 0;
	m_liOldTimeOne.QuadPart = 0;
	m_liOldTimeTwo.QuadPart = 0;
	m_liCurTime.QuadPart = 0;

	m_fDeltaTime = 0.f;
	m_fTimeScale = 0.f;

	assert(0.f	== m_fDeltaTime);
	assert(0.f	== m_fTimeScale);

	assert(0	== m_liOldTimeOne.QuadPart);
	assert(0	== m_liOldTimeTwo.QuadPart);
	assert(0	== m_liCurTime.QuadPart);
	assert(0	== m_liCpuTick.QuadPart);
}
