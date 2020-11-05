#include "stdafx.h"
#include "NiffleHeimSummon.h"

#include "../Monster/Boss.h"

CNiffleHeimSummon::CNiffleHeimSummon()
{
	SetObjectKey(L"Niflheim");
	SetObjectStatus(L"Enter");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(16.f);

	m_tInfo.SetSize(D3DXVECTOR3(80.f / 40.f, 80.f / 31.f, 0.f));
}

CNiffleHeimSummon::~CNiffleHeimSummon()
{
}

CNiffleHeimSummon * CNiffleHeimSummon::Create(const D3DXVECTOR3 & vecPos)
{
	CNiffleHeimSummon* pInstance = new CNiffleHeimSummon;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

int CNiffleHeimSummon::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta() * 0.5f;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_MONSTER,
			CBoss::Create(m_tInfo.vPos)
		);
		return DEAD_OBJ;
	}
	return NO_EVENT;
}

void CNiffleHeimSummon::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);

	UpdateRect();
}

void CNiffleHeimSummon::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 0, 255, 0));
#endif // _DEBUG
}

void CNiffleHeimSummon::UpdateRect()
{
	const float fHalf = 50.f;
	m_tMainRect.left	= static_cast<LONG>(m_tInfo.vPos.x - fHalf);
	m_tMainRect.right	= static_cast<LONG>(m_tInfo.vPos.x + fHalf);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.vPos.y - fHalf);
	m_tMainRect.bottom	= static_cast<LONG>(m_tInfo.vPos.y + fHalf);
}
