#include "stdafx.h"
#include "BigWhiteSkel.h"

CBigWhiteSkel::CBigWhiteSkel()
{
	m_pAttackRect = CRect::Create(90.f, m_tInfo.vPos, true);
	m_pMoveRect = CRect::Create(300.f, m_tInfo.vPos, true);

	SetSpeed(50.f);

	m_tInfo.SetLook(UP_LOOK_VECTOR);

	for (int i = 0; i < static_cast<int>(OBJECT_END); ++i)
	{
		SetAnimation(static_cast<OBJECT_STATUS>(i), 0);
	}
	SetAnimation(OBJECT_STATUS::IDLE, 6);
	SetAnimation(OBJECT_STATUS::MOVE, 6);
	SetAnimation(OBJECT_STATUS::ATTACK, 12);

	SetObjType(OBJECT_TYPE::OBJECT_MONSTER);

	SetCurStatus(OBJECT_STATUS::IDLE);
	ChangeStatus();

	m_fAttackCool.SetCool(2.5f);

	InitializeHP(50);

	SetDamage(6.f);

	m_tInfo.SetSize(SKELETON_SIZE);
	SetDefaultXWay(m_tInfo.vSize.x);

	SetObjectKey(L"BigWhiteSkel");
}

void CBigWhiteSkel::CreateEffect()
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

CBigWhiteSkel::~CBigWhiteSkel()
{
}

CBigWhiteSkel* CBigWhiteSkel::Create(const D3DXVECTOR3 & vecPos)
{
	CBigWhiteSkel* pInstance = new CBigWhiteSkel;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

void CBigWhiteSkel::Attack()
{
	if (m_fAttackCool.GetNextCool())
	{
		m_bAction = true;
		SetCurStatus(OBJECT_STATUS::ATTACK);
		CreateEffect();
	}
}

void CBigWhiteSkel::Act()
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

void CBigWhiteSkel::UpdateRect()
{
	float fWidth = 30.f;
	float fHeight = 35.f;

	m_tMainRect.left = static_cast<LONG>(m_tInfo.vPos.x - fWidth);
	m_tMainRect.right = static_cast<LONG>(m_tInfo.vPos.x + fWidth);
	m_tMainRect.top = static_cast<LONG>(m_tInfo.vPos.y - fHeight);
	m_tMainRect.bottom = static_cast<LONG>(m_tInfo.vPos.y + fHeight);
}