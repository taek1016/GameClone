#include "stdafx.h"
#include "HitEffect.h"


CHitEffect::CHitEffect()
	: m_pTarget(nullptr)
	, m_fCurTime(0.f)
{
}

CHitEffect::~CHitEffect()
{
}

CHitEffect * CHitEffect::Create(const D3DXVECTOR3 & vecPos, const CGameObject * pObj)
{
	CHitEffect* pInstance = new CHitEffect;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->SetTarget(const_cast<CGameObject*>(pObj));

	return pInstance;
}

int CHitEffect::Update()
{
	m_fCurTime += CSINGLETON::pTimeMgr->GetDelta();

	if (m_fCurTime >= 0.2f)
	{
		return DEAD_OBJ;
	}

	return NO_EVENT;
}

void CHitEffect::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_pTarget->GetPos(), m_pTarget->GetSize(), 0.f);
	UpdateRect();
}

void CHitEffect::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_pTarget->GetObjectKey(), 
		m_pTarget->GetObjectStatus(), 
		static_cast<WORD>(m_pTarget->GetCurFrame())
	);
	
	int iColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	if (m_pTarget->GetObjectKey() != L"Player")
	{
		CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, iColor);
	}
	else
	{
		if (m_pTarget->GetObjectKey() == L"Player")
		{
			D3DXVECTOR3	vecCenter{ pTexInfo->tImgInfo.Width TO_HALF, pTexInfo->tImgInfo.Height * 0.7f, 0.f };
			CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CSINGLETON::pDirectMgr->GetSprite()->Draw
			(
				pTexInfo->pTexture,
				nullptr,
				&vecCenter,
				nullptr,
				iColor
			);
		}
	}
}

void CHitEffect::UpdateRect()
{
	float fHalf = 30.f;

	m_tMainRect.left	= static_cast<LONG>(m_tInfo.vPos.x - fHalf);
	m_tMainRect.right	= static_cast<LONG>(m_tInfo.vPos.x + fHalf);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.vPos.x - fHalf);
	m_tMainRect.bottom	= static_cast<LONG>(m_tInfo.vPos.x + fHalf);
}
