#include "stdafx.h"
#include "Bullet.h"

#include "../Effect/Effect.h"

CBullet::CBullet()
{
	SetObjectKey(L"Bullet");
	SetObjectStatus(L"NormalBullet");

	m_tInfo.SetSize(D3DXVECTOR3(30.f / 5.f, 50.f / 28.f, 0.f));

	SetSpeed(800.f);

	SetHalfXY(10.f, 20.f);
	
	m_tFrame.SetMaxFrame(5.f);
}

CBullet::~CBullet()
{
}

CBullet* CBullet::Create
(
	const ATTACK_FROM	eFrom,
	const D3DXVECTOR3&	vecPos,
	const float			fAngle,
	const float			fDamage
)
{
	CBullet* pInstance = new CBullet;

	pInstance->SetFrom(eFrom);
	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->SetAngle(fAngle);
	pInstance->SetDamage(fDamage);

	return pInstance;
}

void CBullet::SetEffect()
{
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_EFFECT,
		CEffect::Create
		(
			m_tInfo.vPos,
			D3DXVECTOR3(50.f, 50.f, 0.f),
			EFFECT_TYPE::EFFECT_HIT,
			m_fAngle + D3DXToRadian(270.f),
			3.f
		)
	);
}