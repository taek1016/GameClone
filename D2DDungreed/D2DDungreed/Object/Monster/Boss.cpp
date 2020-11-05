#include "stdafx.h"
#include "Boss.h"

#include "../Effect/NifleHeimDieEffect.h"

#include "../Player.h"
#include "../UI/BossHP.h"

#include "../Effect/MissileWarningEffect.h"
#include "../Effect/IcePillarCreate.h"
#include "../Bullet/IcicleSummon.h"
#include "../Effect/IceSpearEffect.h"

CBoss::CBoss()
	: m_iPillarNum(0)

	, m_bStun(false)

	, m_eCurPattern(BOSS_PATTERN::PATTERN_END)

	, m_PatternCool()
	, m_StunCool()

	, m_pHPUI(nullptr)
	, m_pPillar{ nullptr }
{
	SetObjectKey(L"Niflheim");

	m_tInfo.SetSize(D3DXVECTOR3(80.f / 40.f, 80.f / 31.f, 0.f));
	SetDefaultXWay(m_tInfo.vSize.x);

	for (int i = 0; i < static_cast<int>(OBJECT_STATUS::STATUS_END); ++i)
	{
		SetAnimation(static_cast<OBJECT_STATUS>(i), 0);
	}
	SetAnimation(OBJECT_STATUS::IDLE, 6);
	SetAnimation(OBJECT_STATUS::ATTACK, 11);

	SetObjType(OBJECT_TYPE::OBJECT_MONSTER);

	SetCurStatus(OBJECT_STATUS::IDLE);
	ChangeStatus();

	InitializeHP(100);

	SafeDelete(m_pHPUI);

	m_PatternCool.SetCool(4.f);
	m_StunCool.SetCool(5.f);
}

CBoss::~CBoss()
{
	SafeDelete(m_pHPUI);
}

CBoss * CBoss::Create(const D3DXVECTOR3 & vecPos)
{
	CBoss* pInstance = new CBoss;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->m_pHPUI = CBossHP::Create(D3DXVECTOR3(400.f, 500.f, 0.f), pInstance);
	pInstance->InitializePillar();

	return pInstance;
}

void CBoss::Attack()
{
}

void CBoss::Act()
{
	SetPreStatus();

	if (m_iPillarNum == 0)
	{
		m_bStun = true;
		m_StunCool.Update();
		if (m_StunCool.GetNextCool())
		{
			m_bAction = true;
			CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_EFFECT, CIceSpearEffect::Create(m_tInfo.vPos + D3DXVECTOR3(50.f, 0.f, 0.f)));
			SetCurStatus(OBJECT_STATUS::ATTACK);
			m_bStun = false;
			InitializePillar();
		}
	}

	if (m_bAction || m_bStun)
	{
		return;
	}

	SetCurStatus(OBJECT_STATUS::IDLE);

	if (!m_pPlayer)
	{
		return;
	}

	InitializeMove();

	if (!m_PatternCool.GetNextCool())
	{
		return;
	}

	switch (m_eCurPattern)
	{
	case TOP_ICICLE:
		SetPattern(TOP_ICICLE_NEXT);
		break;
	case TOP_ICICLE_NEXT:
		SetPattern(PILLAR_NORMAL);
		break;
	case PILLAR_NORMAL:
		m_PatternCool.SetCool(5.f);
		SetPattern(PILLAR_FAST);
		break;
	case PILLAR_FAST:
		m_PatternCool.SetCool(4.f);
		SetPattern(TOP_ICICLE);
		break;
	case PATTERN_END:
		SetPattern(TOP_ICICLE);
		break;
	}
	switch (m_eCurPattern)
	{
	case TOP_ICICLE:
		PatternOne();
		break;
	case TOP_ICICLE_NEXT:
		PatternTwo();
		break;
	}
}

int CBoss::Update()
{
	CMoveObject::HitCheck();

	if (m_pHPUI)
	{
		m_pHPUI->Update();
	}

	if (m_iHP <= 0)
	{
		m_iHP = 0;

		CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_EFFECT, CNifleHeimDieEffect::Create(m_tInfo.vPos));

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

	m_PatternCool.Update();

	CMoveObject::HitCheck();

	Act();
	CMoveObject::ChangeStatus();
	CMonster::CheckWay();
	CGameObject::Animate();

	return NO_EVENT;
}

void CBoss::LateUpdate()
{
	if (m_pHPUI)
	{
		m_pHPUI->LateUpdate();
	}

	m_tInfo.SetDir(m_tMove);
	m_tInfo.SetPos(m_tInfo.vPos + m_tInfo.vDir);

	CMoveObject::CheckMapOutside();

	UpdateRect();

	CSINGLETON::pPhysicMgr->IntersectObjToTile(this);

	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fAngle);

	UpdateRect();
}

void CBoss::Render()
{
	CMoveObject::Render();

	if (m_pHPUI)
	{
		m_pHPUI->Render();
	}
}

void CBoss::UpdateRect()
{
	float fHalf = 40.f;

	m_tMainRect.left = static_cast<LONG>(m_tInfo.vPos.x - fHalf);
	m_tMainRect.right = static_cast<LONG>(m_tInfo.vPos.x + fHalf);
	m_tMainRect.top = static_cast<LONG>(m_tInfo.vPos.y - fHalf);
	m_tMainRect.bottom = static_cast<LONG>(m_tInfo.vPos.y + fHalf);
}

void CBoss::GetDamage(float fDamage)
{
	if (!m_bHit && m_iPillarNum == 0)
	{
		m_bHit = true;
		m_iHP -= static_cast<int>(fDamage);

		if (m_iHP <= 0)
		{
			return;
		}
		CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_EFFECT, CHitEffect::Create(m_tInfo.vPos, this));
	}
}

void CBoss::InitializePillar()
{
	float fAngle[MAX_PILLAR_COUNT] = { 0.f, D3DXToRadian(90.f), D3DXToRadian(180.f), D3DXToRadian(-90.f) };
	float fRevolve[MAX_PILLAR_COUNT] = { D3DXToRadian(-90.f), D3DXToRadian(180.f), D3DXToRadian(-90.f), D3DXToRadian(180.f) };

	for (int i = 0; i < MAX_PILLAR_COUNT; ++i)
	{
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_EFFECT,
			CIcePillarCreate::Create(i, fAngle[i], fRevolve[i], this)
		);
	}
	m_iPillarNum = MAX_PILLAR_COUNT;
	CSINGLETON::pSoundMgr->PlaySound(L"IceSummon.wav", CSoundMgr::CHANNEL_ID::EFFECT);
}

void CBoss::PatternOne()
{
	m_bAction = true;
	D3DXVECTOR3 startPos(PATTERN_ONE_POSITION);

	for (int i = 0; i < ICICLE_COUNT; ++i)
	{
		startPos.x = ICICLE_WIDTH + i * ICICLE_WIDTH;
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_EFFECT,
			CMissileWarningEffect::Create(startPos)
		);
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_EFFECT,
			CIcicleSummon::Create(startPos)
		);
	}
	m_PatternCool.SetCool(2.f);
}

void CBoss::PatternTwo()
{
	m_bAction = true;
	D3DXVECTOR3 startPos(PATTERN_ONE_POSITION);

	for (int i = 0; i < ICICLE_COUNT; ++i)
	{
		startPos.x = ICICLE_WIDTH TO_HALF + i * ICICLE_WIDTH;
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_EFFECT,
			CMissileWarningEffect::Create(startPos)
		);
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_EFFECT,
			CIcicleSummon::Create(startPos)
		);
	}
	m_PatternCool.SetCool(2.f);
}

void CBoss::PatternThree()
{
}

void CBoss::PatternFour()
{
}

void CBoss::PatternFive()
{
}