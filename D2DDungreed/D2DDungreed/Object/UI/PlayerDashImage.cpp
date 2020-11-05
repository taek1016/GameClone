#include "stdafx.h"
#include "PlayerDashImage.h"

#include "../Player.h"

CPlayerDashImage::CPlayerDashImage()
{
	SetObjectKey(L"DashCount");
	SetObjectStatus(L"Count");

	m_tFrame.SetMaxFrame(0.f);

	m_tInfo.SetSize(D3DXVECTOR3(22.f / 9.f, (PLAYER_UI_SIZE_Y TO_HALF - 10.f) / 4.f, 0.f));
}


CPlayerDashImage::~CPlayerDashImage()
{
}

CPlayerDashImage * CPlayerDashImage::Create(const D3DXVECTOR3 & vecPos)
{
	CPlayerDashImage* pInstance = new CPlayerDashImage;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

int CPlayerDashImage::Update()
{
	const CPlayer* pPlayer = dynamic_cast<CPlayer*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());
	NULL_CHECK_RETURN(pPlayer, NO_EVENT);

	CGameObject::Animate();

	return 0;
}

void CPlayerDashImage::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f, false);
}

void CPlayerDashImage::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
	/*D3DXVECTOR3	vecCenter{ pTexInfo->tImgInfo.Width TO_HALF, pTexInfo->tImgInfo.Height TO_HALF, 0.f };
	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CSINGLETON::pDirectMgr->GetSprite()->Draw
	(
		pTexInfo->pTexture,
		&m_tMainRect,
		&vecCenter,
		nullptr,
		m_tInfo.iColorValue
	);*/
}

void CPlayerDashImage::UpdateRect()
{
}
