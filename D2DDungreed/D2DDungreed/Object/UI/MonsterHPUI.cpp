#include "stdafx.h"
#include "MonsterHPUI.h"


CMonsterHPUI::CMonsterHPUI()
	: m_pTarget(nullptr)

	, m_fPercent(0.f)
{
	SetObjectKey(L"UI");
	SetObjectStatus(L"MonsterLifeBar");

	m_tInfo.SetSize(D3DXVECTOR3(60.f / 100.f, 10.f / 20.f, 0.f));
}

CMonsterHPUI::~CMonsterHPUI()
{
	m_pTarget = nullptr;
}

CMonsterHPUI * CMonsterHPUI::Create(const CMoveObject * pObj)
{
	CMonsterHPUI* pInstance = new CMonsterHPUI;

	pInstance->SetObject(pObj);

	return pInstance;
}

int CMonsterHPUI::Update()
{
	m_tInfo.SetPos(m_pTarget->GetPos());

	m_tInfo.vPos.x -= 30.f;
	m_tInfo.vPos.y -= 60.f;

	m_fPercent = m_pTarget->GetHP() / static_cast<float>(m_pTarget->GetMaxHP());

	return 0;
}

void CMonsterHPUI::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);
	UpdateRect();
}

void CMonsterHPUI::Render()
{
	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, 0);

	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CSINGLETON::pDirectMgr->GetSprite()->Draw
	(
		pTexInfo->pTexture,
		nullptr,
		nullptr,
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, 1);

	CSINGLETON::pDirectMgr->GetSprite()->Draw
	(
		pTexInfo->pTexture,
		&m_tMainRect,
		nullptr,
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CMonsterHPUI::UpdateRect()
{
	m_tMainRect.left	= static_cast<LONG>(0.f);
	m_tMainRect.top		= static_cast<LONG>(0.f);
	m_tMainRect.right	= static_cast<LONG>(95.f * m_fPercent);
	m_tMainRect.bottom	= static_cast<LONG>(15.f);
}