#include "stdafx.h"
#include "Hecate.h"

#include "../Bullet/Bullet.h"
#include "../Effect/Effect.h"

CHecate::CHecate()
{
	SetObjectKey(L"Hecate");
	SetObjectStatus(L"Weapon");

	m_tInfo.SetSize(D3DXVECTOR3(80.f / 31.f, 20.f / 11.f, 0.f));
	SetDefaultY(m_tInfo.vSize.y);
	SetEdge(45.f);

	SetDamage(30.f);
}


CHecate::~CHecate()
{
}

CHecate * CHecate::Create()
{
	CHecate* pInstance = new CHecate;

	return pInstance;
}

void CHecate::CreateBullet()
{
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_BULLET,
		CBullet::Create
		(
			ATTACK_FROM::ATTACK_FROM_PLAYER,
			m_tInfo.vDir + m_tInfo.vPos,
			m_fAngle,
			m_fDamage
		)
	);
}

void CHecate::CreateEffect()
{
	// 헤카테 쏘는 것 추가
	D3DXVECTOR3 frontShot(m_tInfo.vDir);
	
	D3DXVec3Normalize(&frontShot, &frontShot);

	frontShot *= 100.f;
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_EFFECT,
		CEffect::Create
		(
			m_tInfo.vPos + frontShot,
			SHOT_EFFECT_SIZE,
			EFFECT_TYPE::EFFECT_HECATE_SHOT,
			m_fAngle + D3DXToRadian(90.f), 
			4.f
		)
	);

	// 헤카테 뒤쪽으로 스모크 나가는 것 추가.
	D3DXVECTOR3 backSmoke(-m_tInfo.vDir);

	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_EFFECT,
		CEffect::Create
		(
			m_tInfo.vPos + backSmoke,
			SMOKE_EFFECT_SIZE,
			EFFECT_TYPE::EFFECT_HECATE_SMOKE,
			m_fAngle + D3DXToRadian(90.f)
		)
	);
}

void CHecate::Render()
{
	CBasicGun::Render();

	// 스코프에서 선 나가게.
}
