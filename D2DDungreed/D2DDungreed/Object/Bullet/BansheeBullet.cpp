#include "stdafx.h"
#include "BansheeBullet.h"

#include "../Player.h"
#include "../Effect/Effect.h"

CBansheeBullet::CBansheeBullet()
	: m_fCurTime(0.f)
{
	SetObjectKey(L"Bullet");
	SetObjectStatus(L"BansheeBullet");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(10.f);

	SetSpeed(300.f);

	m_tInfo.SetSize(D3DXVECTOR3(30.f / 13.f, 36.f / 16.f, 0.f));
	SetHalfXY(10.f, 12.f);

	SetDamage(5.f);

	m_tFrame.SetMaxFrame(4.f);
}

CBansheeBullet::~CBansheeBullet()
{
}

CBansheeBullet * CBansheeBullet::Create(const D3DXVECTOR3 & vecPos, const float fAngle)
{
	CBansheeBullet* pInstance = new CBansheeBullet;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->SetAngle(fAngle);

	return pInstance;
}

void CBansheeBullet::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);

	UpdateRect();

	RECT rc{};

	CMoveObject* const pPlayer = dynamic_cast<CMoveObject*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());
	if (IntersectRect(&rc, &m_tMainRect, &pPlayer->GetRect()))
	{
		m_bDead = true;
		pPlayer->GetDamage(m_fDamage);
		SetEffect();
	}

	m_fCurTime += CSINGLETON::pTimeMgr->GetDelta();
	if (m_fCurTime >= 5.f)
	{
		m_bDead = true;
		SetEffect();
	}
}

void CBansheeBullet::SetEffect()
{
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_EFFECT,
		CEffect::Create
		(
			m_tInfo.vPos,
			D3DXVECTOR3(30.f, 36.f, 0.f),
			EFFECT_TYPE::EFFECT_BANSHEE_BULLET_DESTORY,
			0.f
		)
	);
}