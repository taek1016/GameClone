#include "stdafx.h"
#include "MissileWarningEffect.h"


CMissileWarningEffect::CMissileWarningEffect()
	: m_fAngle(0.f)
{
	SetObjectKey(L"FX");
	SetObjectStatus(L"MissileWarning");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(5.f);

	m_tInfo.SetSize(D3DXVECTOR3(0.5F, 4.0F, 0.F));
}


CMissileWarningEffect::~CMissileWarningEffect()
{
}

CMissileWarningEffect * CMissileWarningEffect::Create(const D3DXVECTOR3 & vecPos, const float fAngle)
{
	CMissileWarningEffect* pInstance = new CMissileWarningEffect;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->SetAngle(fAngle);

	return pInstance;
}

int CMissileWarningEffect::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta() * 3;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		return DEAD_OBJ;
	}

	return NO_EVENT;
}

void CMissileWarningEffect::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fAngle);
}

void CMissileWarningEffect::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CMissileWarningEffect::UpdateRect()
{
}
