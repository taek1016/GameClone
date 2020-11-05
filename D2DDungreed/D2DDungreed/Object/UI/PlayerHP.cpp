#include "stdafx.h"
#include "PlayerHP.h"

#include "PlayerHpBar.h"
#include "PlayerHpWave.h"
#include "../Player.h"

CPlayerHP::CPlayerHP()
{
	SetObjectKey(L"PlayerLifeBar");
	SetObjectStatus(L"Base");

	m_tFrame.SetMaxFrame(2.f);

	m_tInfo.SetSize(D3DXVECTOR3(PLAYER_UI_SIZE_X / 74.f, PLAYER_UI_SIZE_Y / 16.f, 0.f));
}

CPlayerHP::~CPlayerHP()
{
	m_pPlayer = nullptr;

	SafeDelete(m_pBar);
	SafeDelete(m_pWave);
}

CPlayerHP* CPlayerHP::Create(const D3DXVECTOR3 & vecPos)
{
	CPlayerHP* pInstance = new CPlayerHP;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->m_pBar = CPlayerHpBar::Create(pInstance->m_tInfo.vPos);
	pInstance->m_pWave = CPlayerHpWave::Create(pInstance->m_tInfo.vPos);

	return pInstance;
}

int CPlayerHP::Update()
{
	m_pPlayer = dynamic_cast<CPlayer*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());
	NULL_CHECK_RETURN(m_pPlayer, NO_EVENT);

	if (m_pBar)
	{
		m_pBar->Update();
	}

	if (m_pWave)
	{
		m_pWave->Update();
	}

	return 0;
}

void CPlayerHP::LateUpdate()
{
	NULL_CHECK(m_pPlayer);

	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f, false);

	if (m_pBar)
	{
		m_pBar->LateUpdate();
	}

	if (m_pWave)
	{
		m_pWave->LateUpdate();
	}
}

void CPlayerHP::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, 0);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

	if (m_pBar)
	{
		m_pBar->Render();
	}

	if (m_pWave)
	{
		m_pWave->Render();
	}

	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, 1);
	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CPlayerHP::UpdateRect()
{
}
