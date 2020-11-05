#include "stdafx.h"
#include "BasicGun.h"

#include "../Bullet/Bullet.h"

CBasicGun::CBasicGun()
	: m_fEdge(0.f)
	, m_fDefaultYSize(0.f)
{
	m_tInfo.SetLook(D3DXVECTOR3(1.f, 0.f, 0.f));
}

CBasicGun::~CBasicGun()
{
}

int CBasicGun::Update()
{
	if (CSINGLETON::pInventory->GetActivate())
	{
		return NO_EVENT;
	}

	// 플레이어 포지션 == 총기 포지션.
	m_tInfo.vPos = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front()->GetPos();

	m_tInfo.SetDir(CSINGLETON::pCameraMgr->GetPos() + CSINGLETON::pMouseMgr->GetMousePos() - m_tInfo.vPos);

	// 각도 지정
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	m_fAngle = acosf(D3DXVec3Dot(&m_tInfo.vLook, &m_tInfo.vDir));

	if (m_tInfo.vDir.x < 0.f)
	{
		m_tInfo.vSize.y = -m_fDefaultYSize;
	}
	else
	{
		m_tInfo.vSize.y = m_fDefaultYSize;
	}

	if (m_tInfo.vDir.y < 0.f)
	{
		m_fAngle *= REVERSE;
	}
	m_tInfo.vDir *= m_fEdge;

	// 생성 총알과 이펙트만 오버라이딩.
	if (CSINGLETON::pKeyMgr->KeyDown(KEY_LBUTTON))
	{
		CSINGLETON::pSoundMgr->PlaySound(L"Shot.wav", CSoundMgr::CHANNEL_ID::PLAYER);
		CreateBullet();
		CreateEffect();
	}

	return 0;
}

void CBasicGun::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fAngle);
}

void CBasicGun::UpdateRect()
{
}
