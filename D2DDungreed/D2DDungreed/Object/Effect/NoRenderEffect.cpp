#include "stdafx.h"
#include "NoRenderEffect.h"

#include "../Player.h"
#include "../Effect/Effect.h"

CNoRenderEffect::CNoRenderEffect()
	: m_fDelta(0.f)
	, m_fHeight(0.f)
	, m_fWidth(0.f)
	, m_fDamage(0.f)
{
}


CNoRenderEffect::~CNoRenderEffect()
{
}

CNoRenderEffect * CNoRenderEffect::Create(const D3DXVECTOR3 & vecPos, float fWidth, float fHeight, float fDamage)
{
	CNoRenderEffect* pInstance = new CNoRenderEffect;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->SetWidth(fWidth);
	pInstance->SetHeight(fHeight);
	pInstance->SetDamage(fDamage);
	pInstance->UpdateRect();

	return pInstance;
}

int CNoRenderEffect::Update()
{
	m_fDelta += CSINGLETON::pTimeMgr->GetDelta();

	if (m_fDelta >= 0.2f)
	{
		return DEAD_OBJ;
	}

	return 0;
}

void CNoRenderEffect::LateUpdate()
{
	RECT rc{};

	CPlayer* const pPlayer = dynamic_cast<CPlayer*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());

	if (IntersectRect(&rc, &m_tMainRect, &pPlayer->GetRect()))
	{
		pPlayer->GetDamage(m_fDamage);
	}
}

void CNoRenderEffect::Render()
{
#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 255, 0, 0));
#endif // _DEBUG
}

void CNoRenderEffect::UpdateRect()
{
	m_tMainRect.left	= static_cast<LONG>(m_tInfo.vPos.x - m_fWidth);
	m_tMainRect.right	= static_cast<LONG>(m_tInfo.vPos.x + m_fWidth);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.vPos.y - m_fHeight);
	m_tMainRect.bottom	= static_cast<LONG>(m_tInfo.vPos.y + m_fHeight);
}
