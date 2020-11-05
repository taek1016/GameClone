#include "stdafx.h"
#include "SpikeObject.h"

#include "../Effect/NoRenderEffect.h"

CSpikeObject::CSpikeObject()
	: m_bActivate(false)
	, m_fDamage(6.f)
{
	SetObjectKey(L"Object");
	SetObjectStatus(L"IceSpike");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(5.f);

	m_tInfo.SetSize(D3DXVECTOR3(40.f / 16.f, 80.f / 32.f, 0.f));
}


CSpikeObject::~CSpikeObject()
{
}

CSpikeObject * CSpikeObject::Create(const D3DXVECTOR3 & vecPos)
{
	CSpikeObject* pInstance = new CSpikeObject;

	pInstance->m_tInfo.SetPos(vecPos);
	

	return pInstance;
}

int CSpikeObject::Update()
{
	if (m_bActivate)
	{
		m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta() * 1.2f;

		if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
		{
			m_tFrame.fCurFrame = 0.f;
			m_bActivate = false;
		}
	}

	return 0;
}

void CSpikeObject::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);
	UpdateRect();

	CGameObject* pPlayer = (CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());
	RECT rc{};

	if (m_bActivate)
	{
		if (static_cast<int>(m_tFrame.fCurFrame) != SPIKE_UP_START_ANIMATION)
		{
			return;
		}

		if (IntersectRect(&rc, &m_tMainRect, &pPlayer->GetRect()))
		{
			CSINGLETON::pSoundMgr->SetVolume(CSoundMgr::CHANNEL_ID::EFFECT, 0.7f);
			CSINGLETON::pSoundMgr->PlaySound(L"TouchHamjung.wav", CSoundMgr::CHANNEL_ID::EFFECT);
			CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_EFFECT, CNoRenderEffect::Create(m_tInfo.vPos, 10, 40, m_fDamage));
		}
	}
	else
	{
		if (IntersectRect(&rc, &m_tMainRect, &pPlayer->GetRect()))
		{
			m_bActivate = true;
		}
	}
}

void CSpikeObject::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 0, 255, 0));
#endif // _DEBUG

}

void CSpikeObject::UpdateRect()
{
	float fHalfX = 20.f;
	float fHalfY = 40.f;

	m_tMainRect.left	= static_cast<LONG>(m_tInfo.vPos.x - fHalfX);
	m_tMainRect.right	= static_cast<LONG>(m_tInfo.vPos.x + fHalfX);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.vPos.y - fHalfY);
	m_tMainRect.bottom	= static_cast<LONG>(m_tInfo.vPos.y + fHalfY);
}
