#include "stdafx.h"
#include "Monster.h"

#include "../Player.h"

CMonster::CMonster()
	: CMoveObject()

	, m_pPlayer(nullptr)

	, m_fAttackCool()
	, m_fSkillCool()
	, m_fCheckDistance(0.f)
	, m_fXWay(0.f)

	, m_pAttackRect(nullptr)

	, m_bAction(false)
	, m_bFlashed(false)
{
	m_pHPUI = CMonsterHPUI::Create(this);
}

void CMonster::UpdateCool()
{
	m_fAttackCool.Update();
	m_fSkillCool.Update();
}

void CMonster::UpdateCheckRect()
{
	if (m_pAttackRect)
	{
		m_pAttackRect->Update();
	}
	if (m_pSkillRect)
	{
		m_pSkillRect->Update();
	}
	if (m_pMoveRect)
	{
		m_pMoveRect->Update();
	}
}

void CMonster::CheckWay()
{
	D3DXVECTOR3 vecDistance = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front()->GetPos() - m_tInfo.vPos;

	if (vecDistance.x >= 0.f)
	{
		m_tInfo.vSize.x = m_fXWay;
	}
	else
	{
		m_tInfo.vSize.x = -m_fXWay;
	}
}

CMonster::~CMonster()
{
	m_pPlayer = nullptr;
	SafeDelete(m_pAttackRect);
	SafeDelete(m_pSkillRect);
	SafeDelete(m_pMoveRect);
	SafeDelete(m_pHPUI);
}

int CMonster::Update()
{
	CMoveObject::HitCheck();

	if (m_pHPUI)
	{
		m_pHPUI->Update();
	}

	if (m_iHP <= 0)
	{
		m_iHP = 0;
		CSINGLETON::pSoundMgr->PlaySound(L"MonsterDie.wav", CSoundMgr::CHANNEL_ID::EFFECT);
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_EFFECT,
			CEffect::Create
			(
				m_tInfo.vPos,
				DEAD_EFFECT_SIZE,
				EFFECT_TYPE::EFFECT_DIE,
				0.f,
				0.5f
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

	UpdateCool();
	UpdateCheckRect();

	CMoveObject::HitCheck();

	// 각 몬스터마다 Act를 따로 지정.
	// 플레이어의 KeyInput()과 같음.
	Act();
	CMoveObject::ChangeStatus();
	// 바라보는 방향 지정.
	CMonster::CheckWay();
	// 애니메이션
	CGameObject::Animate();

	return 0;
}

void CMonster::LateUpdate()
{
	if (m_pAttackRect)
	{
		m_pAttackRect->LateUpdate();
	}

	if (m_pHPUI)
	{
		m_pHPUI->LateUpdate();
	}

	m_tInfo.SetDir(m_tMove);
	// 이동
	m_tInfo.SetPos(m_tInfo.vPos + m_tInfo.vDir);

	CMoveObject::CheckMapOutside();

	UpdateRect();

	CSINGLETON::pPhysicMgr->IntersectObjToTile(this);

	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fAngle);

	// 몬스터마다 다른 UpdateRect를 돌릴 것.
	UpdateRect();
}

void CMonster::Render()
{
	CMoveObject::Render();

	if (m_pAttackRect)
	{
		m_pAttackRect->Render();
	}
	if (m_pSkillRect)
	{
		m_pSkillRect->Render();
	}
	if (m_pMoveRect)
	{
		m_pMoveRect->Render();
	}
	if (m_pHPUI)
	{
		m_pHPUI->Render();
	}
}