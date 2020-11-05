#include "stdafx.h"
#include "Banshee.h"

#include "../Bullet/BansheeBullet.h"

CBanshee::CBanshee()
{
	SetObjectKey(L"Banshee");

	m_pAttackRect = CRect::Create(800.f, m_tInfo.vPos);

	m_tInfo.SetSize(D3DXVECTOR3(60.f / 20.f, 70.f / 22.f, 0.f));
	SetDefaultXWay(m_tInfo.vSize.x);


	for (int i = 0; i < static_cast<int>(OBJECT_STATUS::STATUS_END); ++i)
	{
		SetAnimation(static_cast<OBJECT_STATUS>(i), 0);
	}
	SetAnimation(OBJECT_STATUS::IDLE, 6);
	SetAnimation(OBJECT_STATUS::ATTACK, 6);

	SetObjType(OBJECT_TYPE::OBJECT_MONSTER);

	SetCurStatus(OBJECT_STATUS::IDLE);
	ChangeStatus();

	SetAttackCool(4.f);

	SetDamage(6.f);

	InitializeHP(30);
}

CBanshee::~CBanshee()
{
}

CBanshee * CBanshee::Create(const D3DXVECTOR3 & vecPos)
{
	CBanshee* pInstance = new CBanshee;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

void CBanshee::Attack()
{
	m_bAction = true;

	SetCurStatus(OBJECT_STATUS::ATTACK);

	float fAngle = 0.f;
	D3DXVECTOR3 vecPos;
	for (int i = 0; i < BANSHEE_BULLET_COUNT; ++i)
	{
		fAngle = i * D3DXToRadian(THIRTY_DEGREE);
		vecPos = D3DXVECTOR3(cosf(fAngle), sinf(fAngle), 0.f) * LENGTH_FROM_BANSHEE;

		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_EFFECT,
			CBansheeBullet::Create
			(
				m_tInfo.vPos + vecPos,
				fAngle
			)
		);
	}
	CSINGLETON::pSoundMgr->PlaySound(L"Scream.wav", CSoundMgr::CHANNEL_ID::MONSTER);
}

void CBanshee::Act()
{
	SetPreStatus();

	if (m_bAction)
	{
		return;
	}

	SetCurStatus(OBJECT_STATUS::IDLE);

	if (!m_pPlayer)
	{
		return;
	}

	InitializeMove();

	if (m_pAttackRect->GetCanAct())
	{
		if (m_fAttackCool.GetNextCool())
		{
			Attack();
		}
	}
}

void CBanshee::UpdateRect()
{
	const float fHalfX = 25.f;
	const float fHalfY = 25.f;

	m_tMainRect.left = static_cast<LONG>(m_tInfo.vPos.x - fHalfX);
	m_tMainRect.right = static_cast<LONG>(m_tInfo.vPos.x + fHalfX);
	m_tMainRect.top = static_cast<LONG>(m_tInfo.vPos.y - fHalfY);
	m_tMainRect.bottom = static_cast<LONG>(m_tInfo.vPos.y + fHalfY);
}