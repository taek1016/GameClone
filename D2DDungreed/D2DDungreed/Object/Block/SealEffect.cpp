#include "stdafx.h"
#include "SealEffect.h"

#include "BlockObject.h"

CSealEffect::CSealEffect()
	: m_fAngle(0.f)
{
	SetObjectKey(L"SealStone");
	SetObjectStatus(L"Open");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(12.f);
}


CSealEffect::~CSealEffect()
{
}

CSealEffect * CSealEffect::Create(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecSize, const float fAngle)
{
	CSealEffect* pInstance = new CSealEffect;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->m_tInfo.SetSize(vecSize);
	pInstance->m_fAngle = fAngle;

	CSINGLETON::pSoundMgr->PlaySound(L"SealStone.wav", CSoundMgr::CHANNEL_ID::EFFECT);
	return pInstance;
}

int CSealEffect::Update()
{
	m_tFrame.fCurFrame += CSINGLETON::pTimeMgr->GetDelta() * 10.f;

	if (m_tFrame.fCurFrame >= m_tFrame.fMaxFrame)
	{
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_OBJECT, 
			CBlockObject::Create(m_tInfo.vPos, m_tInfo.vSize, m_fAngle)
		);
		return DEAD_OBJ;
	}
	return NO_EVENT;
}

void CSealEffect::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fAngle);
}

void CSealEffect::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrObjectKey, 
		m_wStrObjectStatus, 
		static_cast<WORD>(m_tFrame.fCurFrame)
	);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CSealEffect::UpdateRect()
{
}
