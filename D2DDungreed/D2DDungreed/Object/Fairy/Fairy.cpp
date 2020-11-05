#include "stdafx.h"
#include "Fairy.h"

#include "../Player.h"

CFairy::CFairy()
	: m_longWidthHalf(0)

	, m_longHeightHalf(0)

	, m_iHealPoint(0)

	, m_bTouched(false)
{
}

CFairy::~CFairy()
{
}

int CFairy::Update()
{
	if (m_bTouched)
	{
		return DEAD_OBJ;
	}

	Animate();

	return NO_EVENT;
}

void CFairy::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);
	UpdateRect();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());

	RECT rc{};
	if (IntersectRect(&rc, &pPlayer->GetRect(), &m_tMainRect))
	{
		CSINGLETON::pSoundMgr->PlaySound(L"Fairy.wav", CSoundMgr::CHANNEL_ID::EFFECT);
		pPlayer->GetHeal(m_iHealPoint);
		m_bTouched = true;
	}
}

void CFairy::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 0, 255, 0));
#endif // _DEBUG

}

void CFairy::UpdateRect()
{
	m_tMainRect.left	= static_cast<LONG>(m_tInfo.vPos.x - m_longWidthHalf);
	m_tMainRect.right	= static_cast<LONG>(m_tInfo.vPos.x + m_longWidthHalf);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.vPos.y - m_longHeightHalf);
	m_tMainRect.bottom	= static_cast<LONG>(m_tInfo.vPos.y + m_longHeightHalf);
}
