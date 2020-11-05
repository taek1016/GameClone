#include "stdafx.h"
#include "CoolTime.h"


CCoolTime::CCoolTime()
	: m_fCurTime(0.f)
	, m_fCoolTime(0.f)
{
}


CCoolTime::~CCoolTime()
{
}

void CCoolTime::Update()
{
	const float fDeltaTime = CSINGLETON::pTimeMgr->GetDelta();
	m_fCurTime += fDeltaTime;
}
