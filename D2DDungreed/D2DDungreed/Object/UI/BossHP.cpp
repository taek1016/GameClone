#include "stdafx.h"
#include "BossHP.h"

#include "BossHPBar.h"

CBossHP::CBossHP()
	: m_fPercent(0.f)
	, m_pBar(nullptr)
	, m_pTarget(nullptr)
{
	SetObjectKey(L"BossLifeBar");
	SetObjectStatus(L"Base");

	m_tInfo.SetSize(D3DXVECTOR3(300.f / 125.f, 50.f / 16.f, 0.f));
}

CBossHP::~CBossHP()
{
	SafeDelete(m_pBar);
	m_pTarget = nullptr;
}

CBossHP * CBossHP::Create(const D3DXVECTOR3 & vecPos, CBoss* pTarget)
{
	CBossHP* pInstance = new CBossHP;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->SetTarget(pTarget);
	D3DXVECTOR3 barPos(vecPos);
	barPos.x -= HP_START_POS_X;
	barPos.y -= HP_START_POS_Y;
	pInstance->m_pBar = CBossHPBar::Create(barPos, pInstance->m_pTarget);

	return pInstance;
}

int CBossHP::Update()
{
	if (m_pBar)
	{
		m_pBar->Update();
	}
	return 0;
}

void CBossHP::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f, false);
	if (m_pBar)
	{
		m_pBar->LateUpdate();
	}
}

void CBossHP::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, 0);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

	if (m_pBar)
	{
		m_pBar->Render();
	}

	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, 1);
	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CBossHP::UpdateRect()
{
}
