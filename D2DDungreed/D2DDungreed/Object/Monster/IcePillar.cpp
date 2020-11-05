#include "stdafx.h"
#include "IcePillar.h"

#include "Boss.h"
#include "../Player.h"
#include "../Bullet/IceBullet.h"

CIcePillar::CIcePillar()
	: m_pTarget(nullptr)
	, m_iIndex(0)
	, m_matRev()
	, m_ePattern(PATTERN_END)
	, m_CoolTime()
{
	D3DXMatrixIdentity(&m_matRev);

	SetObjectKey(L"IcePillar");

	SetSpeed(200.f);

	m_tInfo.SetSize(D3DXVECTOR3(120.f / 62.f, 50.f / 33.f, 0.f));

	m_tInfo.SetLook(D3DXVECTOR3(0.f, -1.f, 0.f));

	for (int i = 0; i < static_cast<int>(OBJECT_END); ++i)
	{
		SetAnimation(static_cast<OBJECT_STATUS>(i), 0);
	}
	SetAnimation(OBJECT_STATUS::IDLE, 20);

	SetObjType(OBJECT_TYPE::OBJECT_MONSTER);

	SetCurStatus(OBJECT_STATUS::IDLE);
	ChangeStatus();

	InitializeHP(50);

	SetDamage(6.f);

	m_tInfo.SetSize(D3DXVECTOR3(100.f / 62.f, 50.f / 33.f, 0.f));
}


void CIcePillar::SummonBullet(const D3DXVECTOR3 & vecPos, const float fRotation, const float fWay)
{
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_BULLET,
		CIceBullet::Create
		(
			vecPos,
			fWay,
			fRotation
		)
	);
}

CIcePillar::~CIcePillar()
{
}

CIcePillar* CIcePillar::Create(int iIndex, float fSelfRotAngle, float fRevolveAngle, CBoss* pObj)
{
	CIcePillar* pInstance = new CIcePillar;

	pInstance->SetSelfRot(fSelfRotAngle);
	pInstance->SetRevolve(fRevolveAngle);
	pInstance->SetIndex(iIndex);

	pInstance->SetTarget(pObj);

	return pInstance;
}

int CIcePillar::Update()
{
	CMoveObject::HitCheck();

	if (m_pHPUI)
	{
		m_pHPUI->Update();
	}

	if (m_iHP <= 0)
	{
		m_pTarget->DecreasePillar();
		m_iHP = 0;
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_EFFECT,
			CEffect::Create
			(
				m_tInfo.vPos,
				DEAD_EFFECT_SIZE,
				EFFECT_TYPE::EFFECT_DIE,
				NO_ROTATION,
				ZERO_POINT_FIVE_SEC
			)
		);
		return DEAD_OBJ;
	}

	if (m_bAction)
	{
		if (m_tFrame.fCurFrame + NEXT_ANIMATION_DELAY >= m_tFrame.fMaxFrame)
		{
			m_bAction = false;
		}
	}
	m_pPlayer = dynamic_cast<CPlayer*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());

	CMoveObject::HitCheck();

	// 각 몬스터마다 Act를 따로 지정.
	// 플레이어의 KeyInput()과 같음.
	Act();
	CMoveObject::ChangeStatus();
	// 애니메이션
	CGameObject::Animate();

	return 0;
}

void CIcePillar::LateUpdate()
{
	m_fSelfRot += D3DXToRadian(5.f);

	m_tInfo.SetPos(m_pTarget->GetPos());
	m_tInfo.SetDir(D3DXVECTOR3(cosf(m_fSelfRot), sinf(m_fSelfRot), 0.f));

	m_fRevolve += D3DXToRadian(5.5f);
	if (m_fRevolve >= D3DXToRadian(180.f))
	{
		m_fRevolve *= -1.f;
	}

	m_tInfo.vDir *= 80.f;
	m_tInfo.vPos += m_tInfo.vDir;
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fRevolve);
}

void CIcePillar::Attack()
{
}

void CIcePillar::Act()
{
	m_ePrePattern = m_ePattern;
	m_ePattern = m_pTarget->GetCurPattern();

	if (m_ePrePattern != m_ePattern)
	{
		switch (m_ePattern)
		{
		case PILLAR_NORMAL:
			m_CoolTime.SetCool(0.4f);
			break;
		case PILLAR_FAST:
			m_CoolTime.SetCool(0.2f);
			break;
		default:
			break;
		}
	}
	m_CoolTime.Update();

	D3DXVECTOR3 normalVec;
	D3DXVECTOR3 vPos = m_tInfo.vPos - m_pTarget->GetPos();
	::D3DXVec3Normalize(&normalVec, &(vPos));

	D3DXVECTOR3 wayVec(1.f, 0.f, 0.f);
	D3DXVECTOR3 rotationVec(0.f, -1.f, 0.f);
	float fWayAngle = acosf(D3DXVec3Dot(&normalVec, &wayVec));

	float fRotationAngle = acosf(D3DXVec3Dot(&normalVec, &rotationVec));
	
	if (vPos.y < 0)
	{
		fWayAngle *= -1;
	}
	if (vPos.x < 0)
	{
		fRotationAngle *= -1;
	}

	D3DXVECTOR3 vecPos = m_tInfo.vPos + D3DXVECTOR3(cosf(m_fAngle), sinf(m_fAngle), 0.f) * 30.f;
	switch (m_ePattern)
	{
	case PILLAR_NORMAL:
		if (m_CoolTime.GetNextCool())
		{
			SummonBullet(vecPos, fWayAngle, fRotationAngle);
		}
		break;
	case PILLAR_FAST:
		if (m_CoolTime.GetNextCool())
		{
			CSINGLETON::pSoundMgr->SetVolume(CSoundMgr::CHANNEL_ID::EFFECT, 0.1f);
			SummonBullet(vecPos, fWayAngle, fRotationAngle);
		}
		break;
	}
}