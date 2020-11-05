#include "stdafx.h"
#include "FrameMgr.h"

IMPLEMENT_SINGLETON(CFrameMgr)

CFrameMgr::CFrameMgr()
	: m_fFps(0.f)
	, m_fTimeCount(0.f)
	, m_fDeltaTime(0.f)

	, m_iFpsCount(0)
	
	, m_szFPS{}
	
	, m_liCpuTick()
	, m_liCurTime()
	, m_liOldTimeOne()
	, m_liOldTimeTwo()
{
	AssertMember();

	QueryPerformanceCounter(&m_liOldTimeOne);
	QueryPerformanceCounter(&m_liOldTimeTwo);
	QueryPerformanceCounter(&m_liCurTime);

	QueryPerformanceFrequency(&m_liCpuTick);

	SetFps(60.f);
}

CFrameMgr::~CFrameMgr()
{
	m_fFps					= 0.f;
	m_fTimeCount			= 0.f;
	m_fDeltaTime			= 0.f;

	m_iFpsCount				= 0;

	for (int i = 0; i < MIN_STR; ++i)
	{
		m_szFPS[i]			= 0;
	}

	m_liCpuTick.QuadPart	= 0;
	m_liCurTime.QuadPart	= 0;
	m_liOldTimeOne.QuadPart = 0;
	m_liOldTimeTwo.QuadPart = 0;

	AssertMember();
}

bool CFrameMgr::LimitFrame()
{
	QueryPerformanceCounter(&m_liCurTime);

	if (m_liCurTime.QuadPart - m_liOldTimeTwo.QuadPart > m_liCpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_liCpuTick);
		m_liOldTimeTwo = m_liCurTime;
	}

	m_fTimeCount	+= static_cast<float>(m_liCurTime.QuadPart - m_liOldTimeOne.QuadPart) / m_liCpuTick.QuadPart;
	m_liOldTimeOne	= m_liCurTime;

	if ((1.f / m_fFps) <= m_fTimeCount)
	{
		m_fTimeCount = 0.f;
		return true;
	}

	return false;
}

void CFrameMgr::RenderFPS()
{
	++m_iFpsCount;				// 출력할 FPS

	m_fDeltaTime	+= CSINGLETON::pTimeMgr->GetDelta();

	// 1초가 지났을 때 갱신.
	if (1.f <= m_fDeltaTime)
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFpsCount);

		m_fDeltaTime	= 0.f;
		m_iFpsCount		= 0;
	}

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderFont(D3DXVECTOR3(100.f, 100.f, 0.f), m_szFPS, D3DCOLOR_ARGB(255, 255, 0, 0));
#endif // _DEBUG
}

void CFrameMgr::SetFps(float fFps)
{
	m_fFps = fFps;
}

void CFrameMgr::AssertMember() const
{
	assert(m_fFps == 0.f);
	assert(m_fTimeCount == 0.f);
	assert(m_fDeltaTime == 0.f);
	assert(m_iFpsCount == 0);

	for (int i = 0; i < MIN_STR; ++i)
	{
		assert(m_szFPS[i] == 0);
	}

	assert(m_liCpuTick.QuadPart == 0);
	assert(m_liCurTime.QuadPart == 0);
	assert(m_liOldTimeOne.QuadPart == 0);
	assert(m_liOldTimeTwo.QuadPart == 0);
}