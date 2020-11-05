#include "stdafx.h"
#include "BigGraySkel.h"

#include "../Player.h"
#include "../Effect/NoRenderIceBulletSummon.h"

CBigGraySkel::CBigGraySkel()
	: m_fSkillCool()
	, m_pSkillRect(nullptr)
{
	m_pSkillRect = CRect::Create(400.f, m_tInfo.vPos);
	m_fSkillCool.SetCool(3.f);

	m_pAttackRect = CRect::Create(90.f, m_tInfo.vPos, true);
	m_pMoveRect = CRect::Create(300.f, m_tInfo.vPos, true);

	SetObjectKey(L"BigGrayIceSkel");

	SetSpeed(50.f);

	m_tInfo.SetLook(D3DXVECTOR3(0.f, -1.f, 0.f));

	for (int i = 0; i < static_cast<int>(OBJECT_END); ++i)
	{
		SetAnimation(static_cast<OBJECT_STATUS>(i), 0);
	}
	SetAnimation(OBJECT_STATUS::IDLE, 8);
	SetAnimation(OBJECT_STATUS::MOVE, 6);
	SetAnimation(OBJECT_STATUS::ATTACK, 13);
	SetAnimation(OBJECT_STATUS::SKILL, 13);

	SetObjType(OBJECT_TYPE::OBJECT_MONSTER);

	SetCurStatus(OBJECT_STATUS::IDLE);
	ChangeStatus();

	m_fAttackCool.SetCool(2.5f);
	m_fSkillCool.SetCool(10.f);

	InitializeHP(50);

	SetDamage(6.f);
}


CBigGraySkel::~CBigGraySkel()
{
	SafeDelete(m_pSkillRect);
}

CBigGraySkel* CBigGraySkel::Create(const D3DXVECTOR3 & vecPos)
{
	CBigGraySkel* pInstance = new CBigGraySkel;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

void CBigGraySkel::Attack()
{
	if (m_fAttackCool.GetNextCool())
	{
		m_bAction = true;
		SetCurStatus(OBJECT_STATUS::ATTACK);
		CreateEffect();
	}
}

void CBigGraySkel::Act()
{
	CMoveObject::SetPreStatus();

	if (m_bAction)
	{
		return;
	}

	CMoveObject::SetCurStatus(OBJECT_STATUS::IDLE);

	if (!m_pPlayer)
	{
		return;
	}

	InitializeMove();

	if (m_pAttackRect->GetCanAct())
	{
		Attack();
	}
	else if (m_pSkillRect->GetCanAct() && m_fSkillCool.GetNextCool())
	{
		Skill();
	}
	else if (m_pMoveRect->GetCanAct())
	{
		SetCurStatus(OBJECT_STATUS::MOVE);

		const D3DXVECTOR3& vecPlayerPos = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front()->GetPos();

		m_tMove = (vecPlayerPos - m_tInfo.vPos);
		D3DXVec3Normalize(&m_tMove, &m_tMove);

		m_tMove *= m_fSpeed * CSINGLETON::pTimeMgr->GetDelta();
	}

	CMoveObject::FreeDownObject();
}

int CBigGraySkel::Update()
{
	CMoveObject::HitCheck();

	if (m_pHPUI)
	{
		m_pHPUI->Update();
	}

	if (m_iHP <= 0)
	{
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

	UpdateCool();
	m_fSkillCool.Update();
	UpdateCheckRect();
	m_pSkillRect->Update();

	CMoveObject::HitCheck();

	// 각 몬스터마다 Act를 따로 지정.
	// 플레이어의 KeyInput()과 같음.
	Act();
	CMoveObject::ChangeStatus();
	// 바라보는 방향 지정.

	ConvertSizeVector();

	CMonster::CheckWay();
	// 애니메이션
	CGameObject::Animate();

	return NO_EVENT;
}

void CBigGraySkel::LateUpdate()
{
	m_pSkillRect->LateUpdate();

	CMonster::LateUpdate();
}

void CBigGraySkel::Render()
{
	CMonster::Render();
#ifdef _DEBUG
	m_pSkillRect->Render();
#endif // _DEBUG
}

void CBigGraySkel::UpdateRect()
{
	float fHalfX = 30.f;
	float fHalfY = 40.f;

	m_tMainRect.left = static_cast<LONG>(m_tInfo.vPos.x - fHalfX);
	m_tMainRect.right = static_cast<LONG>(m_tInfo.vPos.x + fHalfX);
	m_tMainRect.top = static_cast<LONG>(m_tInfo.vPos.y - fHalfY);
	m_tMainRect.bottom = static_cast<LONG>(m_tInfo.vPos.y + fHalfY);
}

void CBigGraySkel::CreateEffect()
{
	if (2.f > m_tFrame.fCurFrame && m_tFrame.fCurFrame >= 3.f)
	{
		return;
	}
	const D3DXVECTOR3& playerPos = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front()->GetPos();

	D3DXVECTOR3 vecPos = playerPos - m_tInfo.vPos;

	D3DXVec3Normalize(&vecPos, &vecPos);

	float fAngle = acosf(D3DXVec3Dot(&vecPos, &m_tInfo.vLook));

	if (vecPos.x < 0.f)
	{
		fAngle *= REVERSE;
	}

	vecPos *= m_fSpeed;

	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_EFFECT,
		CNoRenderEffect::Create
		(
			vecPos + m_tInfo.vPos,
			ATTACK_WIDTH,
			ATTACK_HEIGHT,
			m_fDamage
		)
	);
}

void CBigGraySkel::Skill()
{
	m_bAction = true;
	SetCurStatus(OBJECT_STATUS::SKILL);

	D3DXVECTOR3 vecDir = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front()->GetPos() - m_tInfo.vPos;
	D3DXVec3Normalize(&vecDir, &vecDir);
	vecDir *= m_fSpeed;
	CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_EFFECT, CNoRenderIceBulletSummon::Create(m_tInfo.vPos + vecDir));
}

void CBigGraySkel::ConvertSizeVector()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus);

	if (m_eCurStatus == ATTACK)
	{
		m_tInfo.SetSize(D3DXVECTOR3(250.f / pTexInfo->tImgInfo.Width, 160.f / pTexInfo->tImgInfo.Height, 0.f));
	}
	else
	{
		m_tInfo.SetSize(SKELETON_SIZE);
	}
	SetDefaultXWay(m_tInfo.vSize.x);
}