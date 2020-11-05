#include "stdafx.h"
#include "PlayerHpBar.h"

#include "../Player.h"

CPlayerHpBar::CPlayerHpBar()
	: m_pPlayer(nullptr)
	, m_fPercent(0.f)
{
	SetObjectKey(L"PlayerLifeBar");
	SetObjectStatus(L"Bar");

	m_tFrame.SetMaxFrame(0.f);
}


CPlayerHpBar::~CPlayerHpBar()
{
}

CPlayerHpBar * CPlayerHpBar::Create(const D3DXVECTOR3 & vecPos)
{
	CPlayerHpBar* pInstance = new CPlayerHpBar;

	pInstance->m_tInfo.SetPos(D3DXVECTOR3(vecPos.x - 30, vecPos.y - 15, vecPos.z));

	return pInstance;
}

int CPlayerHpBar::Update()
{
	m_pPlayer = dynamic_cast<CPlayer*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());

	NULL_CHECK_RETURN(m_pPlayer, NO_EVENT);

	m_fPercent = m_pPlayer->GetHP() / static_cast<float>(m_pPlayer->GetMaxHP());

	if (m_fPercent <= 0.f)
	{
		m_fPercent = 0.f;
	}
	if (m_fPercent >= 1.f)
	{
		m_fPercent = 1.f;
	}
	return 0;
}

void CPlayerHpBar::LateUpdate()
{
	NULL_CHECK(m_pPlayer);

	m_tInfo.SetSize(D3DXVECTOR3(100.f * m_fPercent, 30.f / 10.f, 0.f));

	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f, false);
}

void CPlayerHpBar::Render()
{
	NULL_CHECK(m_pPlayer);

	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus);

	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CSINGLETON::pDirectMgr->GetSprite()->Draw
	(
		pTexInfo->pTexture,
		nullptr,
		nullptr,
		nullptr,
		m_tInfo.iColorValue
	);

}

void CPlayerHpBar::UpdateRect()
{
}
