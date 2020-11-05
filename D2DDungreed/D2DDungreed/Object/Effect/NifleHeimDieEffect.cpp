#include "stdafx.h"
#include "NifleHeimDieEffect.h"

CNifleHeimDieEffect::CNifleHeimDieEffect()
{
	SetObjectKey(L"Niflheim");
	SetObjectStatus(L"Die");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(30.f);

	m_tInfo.SetSize(D3DXVECTOR3(80.f / 30.f, 80.f / 24.f, 0.f));
}

CNifleHeimDieEffect::~CNifleHeimDieEffect()
{
}

CNifleHeimDieEffect * CNifleHeimDieEffect::Create(const D3DXVECTOR3 & vecPos)
{
	CNifleHeimDieEffect* pInstance = new CNifleHeimDieEffect;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

int CNifleHeimDieEffect::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta() * 0.25f;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		float fLastAnimationIndex = m_tFrame.fMaxFrame - 1.f;
		m_tFrame.fCurFrame = fLastAnimationIndex;
	}

	return NO_EVENT;
}

void CNifleHeimDieEffect::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);
}

void CNifleHeimDieEffect::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CNifleHeimDieEffect::UpdateRect()
{
	const float fHalf = 50.f;
	m_tMainRect.left = static_cast<LONG>(m_tInfo.vPos.x - fHalf);
	m_tMainRect.right = static_cast<LONG>(m_tInfo.vPos.x + fHalf);
	m_tMainRect.top = static_cast<LONG>(m_tInfo.vPos.y - fHalf);
	m_tMainRect.bottom = static_cast<LONG>(m_tInfo.vPos.y + fHalf);
}