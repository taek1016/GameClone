#include "stdafx.h"
#include "CameraMgr.h"

#include "../../Object/GameObject.h"
#include "../../Object/MoveObject.h"

IMPLEMENT_SINGLETON(CCamera)

CCamera::CCamera()
	: m_vecPos{}
	, m_vecClientRS{}
	, m_vecPivot{}
	
	, m_vecWorldRS{}

	, m_pTarget(nullptr)

	, m_bHit(false)
	, m_fCurTime(0.f)
{
	AssertMember();
}

CCamera::~CCamera()
{
	AssertMember();
}

void CCamera::AssertMember()
{
	m_vecPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_vecClientRS = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_vecWorldRS = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_vecPivot = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_pTarget = nullptr;

	assert(D3DXVECTOR3(0.f, 0.f, 0.f) == m_vecPos);
	assert(D3DXVECTOR3(0.f, 0.f, 0.f) == m_vecClientRS);
	assert(D3DXVECTOR3(0.f, 0.f, 0.f) == m_vecWorldRS);
	assert(D3DXVECTOR3(0.f, 0.f, 0.f) == m_vecPivot);
	assert(nullptr == m_pTarget);
}

void CCamera::LateUpdate()
{
	if (m_pTarget)
	{
		int iRand = 0;
		if (m_bHit)
		{
			float fDelta = CSINGLETON::pTimeMgr->GetDelta();
			m_fCurTime += fDelta;
			if (m_fCurTime >= 1.f)
			{
				m_bHit = false;
			}

			static float fDeltaTime = 0.f;
			fDeltaTime += fDelta;
			if (fDeltaTime >= 0.4f)
			{
				iRand = rand() % 5 + 1;
			}
		}
		D3DXVECTOR3 vecPos = m_pTarget->GetPos();
		
		const float fLeftArea = m_vecClientRS.x * m_vecPivot.x;
		const float fRightArea = m_vecClientRS.x - fLeftArea;
		
		const float fTopArea = m_vecClientRS.y * m_vecPivot.y;
		const float fBottomArea = m_vecClientRS.y - fTopArea;

		if (vecPos.x <= fLeftArea)
		{
			m_vecPos.x = 0.f + iRand;
		}
		else if (vecPos.x >= m_vecWorldRS.x - fRightArea)
		{
			m_vecPos.x = m_vecWorldRS.x - m_vecClientRS.x - iRand;
		}
		else
		{
			m_vecPos.x = vecPos.x - m_vecClientRS.x * m_vecPivot.x + iRand;
		}

		if (vecPos.y <= fTopArea)
		{
			m_vecPos.y = 0.f + iRand;
		}
		else if (vecPos.y >= m_vecWorldRS.y - fBottomArea)
		{
			m_vecPos.y = m_vecWorldRS.y - m_vecClientRS.y - iRand;
		}
		else
		{
			m_vecPos.y = vecPos.y - m_vecClientRS.y * m_vecPivot.y + iRand;
		}
	}
}