#include "stdafx.h"
#include "PlayerHpWave.h"

#include "../Player.h"

CPlayerHpWave::CPlayerHpWave()
{
	SetObjectKey(L"PlayerLifeBar");
	SetObjectStatus(L"Wave");

	m_tFrame.SetMaxFrame(7.f);

	m_tInfo.SetSize(D3DXVECTOR3(20.f / 6.f, 30.f / 10.f, 0.f));
}


CPlayerHpWave::~CPlayerHpWave()
{
}

CPlayerHpWave* CPlayerHpWave::Create(const D3DXVECTOR3& vecPos)
{
	CPlayerHpWave* pInstance = new CPlayerHpWave;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

int CPlayerHpWave::Update()
{
	m_pPlayer = dynamic_cast<CPlayer*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());

	NULL_CHECK_RETURN(m_pPlayer, NO_EVENT);

	float fPercent = m_pPlayer->GetHP() / static_cast<float>(m_pPlayer->GetMaxHP());

	if (fPercent < 0.f)
	{
		fPercent = 0.f;
	}
	else if (fPercent > 1.f)
	{
		fPercent = 1.f;
	}

	m_tInfo.vPos.x = 72.f + 100 * fPercent;

	CGameObject::Animate();

	return NO_EVENT;
}

void CPlayerHpWave::LateUpdate()
{
	NULL_CHECK(m_pPlayer);

	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f, false);
}

void CPlayerHpWave::Render()
{
	NULL_CHECK(m_pPlayer);

	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CPlayerHpWave::UpdateRect()
{
}
