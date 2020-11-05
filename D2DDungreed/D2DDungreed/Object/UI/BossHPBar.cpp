#include "stdafx.h"
#include "BossHPBar.h"


CBossHPBar::CBossHPBar()
	: m_pTarget(nullptr)
	, m_fPercent(0.f)
{
	SetObjectKey(L"BossLifeBar");
	SetObjectStatus(L"Bar");
}


CBossHPBar::~CBossHPBar()
{
}

CBossHPBar * CBossHPBar::Create(const D3DXVECTOR3 & vecPos, CBoss * pTarget)
{
	CBossHPBar* pInstance = new CBossHPBar;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->SetTarget(pTarget);

	return pInstance;
}

int CBossHPBar::Update()
{
	m_fPercent = m_pTarget->GetHP() / static_cast<float>(m_pTarget->GetMaxHP());

	if (m_fPercent < 0.f)
	{
		m_fPercent = 0.f;
	}
	else if (m_fPercent > FULL_HP)
	{
		m_fPercent = FULL_HP;
	}

	return 0;
}

void CBossHPBar::LateUpdate()
{
	m_tInfo.SetSize(D3DXVECTOR3(250.f * m_fPercent, 30.f / 10.f, 0.f));

	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f, false);
}

void CBossHPBar::Render()
{
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

void CBossHPBar::UpdateRect()
{
}
