#include "stdafx.h"
#include "Rect.h"

#include "../Player.h"

CRect::CRect(float fRange)
	: m_fRange(fRange)
	
	, m_bCanAct(true)

	, m_tRect{}

	, m_pPlayer(nullptr)
	, m_pMonsterPos(nullptr)
{
}

CRect::~CRect()
{
	m_pPlayer		= nullptr;
	m_pMonsterPos	= nullptr;
	m_fRange		= 0.f;
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CRect* CRect::Create(const float fRange, const D3DXVECTOR3& vecPos, const bool bMelee)
{
	CRect* pInstance = new CRect(fRange);

	pInstance->m_pPlayer = dynamic_cast<CPlayer*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_PLAYER)->front());
	
	pInstance->m_bMelee = bMelee;

	pInstance->m_pMonsterPos = &vecPos;
	pInstance->UpdateRect();

	return pInstance;
}

void CRect::UpdateRect()
{
	if (!m_bMelee)
	{
		m_tRect.left = static_cast<LONG>(m_pMonsterPos->x - m_fRange);
		m_tRect.right = static_cast<LONG>(m_pMonsterPos->x + m_fRange);
		m_tRect.top = static_cast<LONG>(m_pMonsterPos->y - m_fRange);
		m_tRect.bottom = static_cast<LONG>(m_pMonsterPos->y + m_fRange);
	}
	else
	{
		m_tRect.left = static_cast<LONG>(m_pMonsterPos->x - m_fRange);
		m_tRect.right = static_cast<LONG>(m_pMonsterPos->x + m_fRange);
		m_tRect.top = static_cast<LONG>(m_pMonsterPos->y - 60);
		m_tRect.bottom = static_cast<LONG>(m_pMonsterPos->y + 60);
	}
}

void CRect::Update()
{
	m_bCanAct = false;
	RECT rc{};
	if (IntersectRect(&rc, &m_tRect, &m_pPlayer->GetRect()))
	{
		m_bCanAct = true;
	}

	UpdateRect();
}

void CRect::LateUpdate()
{
}

void CRect::Render()
{
#ifdef _DEBUG
	int iColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	if (m_bCanAct)
	{
		iColor = D3DCOLOR_ARGB(255, 0, 0, 255);
	}
	CSINGLETON::pDirectMgr->RenderRect(m_tRect, iColor);
#endif // _DEBUG
}