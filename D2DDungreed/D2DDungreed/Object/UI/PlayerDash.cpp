#include "stdafx.h"
#include "PlayerDash.h"

#include "../Player.h"
#include "PlayerDashImage.h"

CPlayerDash::CPlayerDash()
	: m_iMaxDashCount(0)
	, m_iCurDashCount(0)
	, m_iRealMaxDashCount(6)
	, m_pDashImage(nullptr)
{
	SetObjectKey(L"DashCount");
	SetObjectStatus(L"Base");

	m_tInfo.SetSize(D3DXVECTOR3(PLAYER_UI_SIZE_X / 61.8f, (PLAYER_UI_SIZE_Y TO_HALF) / 8.f, 0.f));
}

CPlayerDash::~CPlayerDash()
{
	for (int i = 0; i < m_iRealMaxDashCount; ++i)
	{
		SafeDelete(m_pDashImage[i]);
	}
	SafeDelete_Array(m_pDashImage);
}

CPlayerDash* CPlayerDash::Create(const D3DXVECTOR3 & vecPos)
{
	CPlayerDash* pInstance = new CPlayerDash;

	pInstance->m_tInfo.SetPos(vecPos);

	pInstance->m_pDashImage = new CPlayerDashImage*[pInstance->m_iRealMaxDashCount];

	for (int i = 0; i < pInstance->m_iRealMaxDashCount; ++i)
	{
		pInstance->m_pDashImage[i] = CPlayerDashImage::Create(D3DXVECTOR3((vecPos.x - 60.f) + i * 25.f, vecPos.y, 0.f));
	}

	return pInstance;
}

int CPlayerDash::Update()
{
	const CPlayer* pPlayer = dynamic_cast<CPlayer*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());
	NULL_CHECK_RETURN(pPlayer, NO_EVENT);

	m_iMaxDashCount = pPlayer->GetMaxDashCount();
	m_iCurDashCount = pPlayer->GetCurDashCount();

	for (int i = 0; i < m_iRealMaxDashCount; ++i)
	{
		m_pDashImage[i]->Update();
	}

	return 0;
}

void CPlayerDash::LateUpdate()
{
	UpdateRect();

	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f, false);

	for (int i = 0; i < m_iRealMaxDashCount; ++i)
	{
		m_pDashImage[i]->LateUpdate();
	}

}

void CPlayerDash::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus);

	D3DXVECTOR3	vecCenter{ pTexInfo->tImgInfo.Width TO_HALF, pTexInfo->tImgInfo.Height TO_HALF, 0.f };
	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CSINGLETON::pDirectMgr->GetSprite()->Draw
	(
		pTexInfo->pTexture,
		&m_tMainRect,
		&vecCenter,
		nullptr,
		m_tInfo.iColorValue
	);

	for (int i = 0; i < m_iCurDashCount; ++i)
	{
		m_pDashImage[i]->Render();
	}

}

void CPlayerDash::UpdateRect()
{
	m_tMainRect.left	= static_cast<LONG>(0);
	m_tMainRect.right	= static_cast<LONG>(10 * m_iMaxDashCount + 1);
	m_tMainRect.top		= static_cast<LONG>(0);
	m_tMainRect.bottom	= static_cast<LONG>(8);
}
