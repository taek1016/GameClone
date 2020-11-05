#include "stdafx.h"
#include "IceSpearEffect.h"

#include "MissileWarningEffect.h"
#include "../Bullet/IceSpear.h"

CIceSpearEffect::CIceSpearEffect()
{
	SetObjectKey(L"FX");
	SetObjectStatus(L"IceSpearCreate");

	m_tFrame.SetMaxFrame(13.f);

	m_tInfo.SetSize(D3DXVECTOR3(50.f / 25.f, 150.f / 111.f, 0.f));

	m_tInfo.SetDir(D3DXVECTOR3(0.F, 1.F, 0.F));
}


CIceSpearEffect::~CIceSpearEffect()
{
}

CIceSpearEffect * CIceSpearEffect::Create(const D3DXVECTOR3 & vecPos)
{
	CIceSpearEffect* pInstance = new CIceSpearEffect;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

int CIceSpearEffect::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta();

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		CSINGLETON::pObjectMgr->AddObject(OBJECT_BULLET, CIceSpear::Create(m_tInfo.vPos));
		return DEAD_OBJ;
	}
	return NO_EVENT;
}

void CIceSpearEffect::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);
}

void CIceSpearEffect::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CIceSpearEffect::UpdateRect()
{
}
