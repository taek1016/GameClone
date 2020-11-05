#include "stdafx.h"
#include "IceBullet.h"

#include "../Player.h"

CIceBullet::CIceBullet()
	: CBulletBase()
	, m_fRotationAngle(0.f)
{
	SetObjectKey(L"Bullet");
	SetObjectStatus(L"IceBullet");

	SetDamage(5.f);
	
	SetSpeed(300.f);

	SetHalfXY(20.f, 20.f);

	m_tInfo.SetSize(D3DXVECTOR3(25.f / 9.f, 40.f / 18.f, 0.f));
}

CIceBullet::~CIceBullet()
{
}

CIceBullet * CIceBullet::Create(const D3DXVECTOR3 & vecPos, const float fAngle, const float fRotationAngle)
{
	CIceBullet* pInstance = new CIceBullet;

	pInstance->m_tInfo.SetPos(vecPos);

	pInstance->SetAngle(fAngle);
	pInstance->SetRotationAngle(fRotationAngle);

	return pInstance;
}

void CIceBullet::SetEffect()
{
}

void CIceBullet::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fRotationAngle);
	UpdateRect();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());

	RECT rc{};
	if (IntersectRect(&rc, &pPlayer->GetRect(), &m_tMainRect))
	{
		pPlayer->GetDamage(m_fDamage);
		m_bDead = true;
		CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_EFFECT, CEffect::Create(m_tInfo.vPos, D3DXVECTOR3(30.f, 30.f, 0.f), EFFECT_TYPE::EFFECT_ICE_BULLET_CREATE, 0.f));
	}
}