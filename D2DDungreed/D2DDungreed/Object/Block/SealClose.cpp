#include "stdafx.h"
#include "SealClose.h"


CSealClose::CSealClose()
	: m_fAngle(0.f)
{
	SetObjectKey(L"SealStone");
	SetObjectStatus(L"Close");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(12.f);
}


CSealClose::~CSealClose()
{
}

CSealClose * CSealClose::Create(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecSize, const float fAngle)
{
	CSealClose* pInstance = new CSealClose;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->m_tInfo.SetSize(vecSize);
	pInstance->m_fAngle = fAngle;

	CSINGLETON::pSoundMgr->PlaySound(L"SealStone.wav", CSoundMgr::CHANNEL_ID::EFFECT);

	return pInstance;
}

int CSealClose::Update()
{
	m_tFrame.fCurFrame += CSINGLETON::pTimeMgr->GetDelta() * 10.f;
#ifdef _DEBUG
	static float fDelta = 0.f;
	fDelta += CSINGLETON::pTimeMgr->GetDelta();
	if (fDelta >= 1.f)
	{
		fDelta = 0.f;
		printf("%f\n", m_tFrame.fCurFrame);
	}

#endif // _DEBUG

	if (m_tFrame.fCurFrame >= m_tFrame.fMaxFrame)
	{
		return DEAD_OBJ;
	}
	return NO_EVENT;
}

void CSealClose::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fAngle);
}

void CSealClose::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrObjectKey,
		m_wStrObjectStatus,
		static_cast<WORD>(m_tFrame.fCurFrame)
	);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CSealClose::UpdateRect()
{
}
