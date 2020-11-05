#include "stdafx.h"
#include "IcicleSummon.h"

#include "../Bullet/Icicle.h"

CIcicleSummon::CIcicleSummon()
{
	SetObjectKey(L"FX");
	SetObjectStatus(L"IcicleCreate");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(10.f);

	m_tInfo.SetSize(D3DXVECTOR3(45.f / 27.f, 90.f / 40.f, 0.f));
}

CIcicleSummon::~CIcicleSummon()
{
}

CIcicleSummon * CIcicleSummon::Create(const D3DXVECTOR3 & vecPos)
{
	CIcicleSummon* pInstance = new CIcicleSummon;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

int CIcicleSummon::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta() * 2.f;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_BULLET,
			CIcicle::Create(m_tInfo.vPos)
		);
		return DEAD_OBJ;
	}

	return NO_EVENT;
}

void CIcicleSummon::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);
}

void CIcicleSummon::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CIcicleSummon::UpdateRect()
{
}
