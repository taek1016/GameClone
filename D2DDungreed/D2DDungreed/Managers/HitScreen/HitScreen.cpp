#include "stdafx.h"
#include "HitScreen.h"

IMPLEMENT_SINGLETON(CHitScreen)

CHitScreen::CHitScreen()
	: m_bActivate(false)
	, m_fDelta(0.f)
{
	SetObjectKey(L"UI");
	SetObjectStatus(L"Hit");

	m_tInfo.SetSize(D3DXVECTOR3(CSINGLETON::GetWidth() / 320.f, CSINGLETON::GetHeight() / 180.f, 0.f));
	m_tInfo.SetPos(D3DXVECTOR3(CSINGLETON::GetWidth() TO_HALF, CSINGLETON::GetHeight() TO_HALF, 0.f));
}


CHitScreen::~CHitScreen()
{
}

int CHitScreen::Update()
{
	if (m_bActivate)
	{
		m_fDelta += CSINGLETON::pTimeMgr->GetDelta();
		if (m_fDelta >= 1.f)
		{
			m_bActivate = false;
		}
	}

	return NO_EVENT;
}

void CHitScreen::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f, false);
}

void CHitScreen::Render()
{
	if (!m_bActivate)
	{
		return;
	}
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(GetObjectKey(), GetObjectStatus());

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CHitScreen::UpdateRect()
{
}
