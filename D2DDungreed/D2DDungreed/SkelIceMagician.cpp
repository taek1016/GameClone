#include "stdafx.h"

#include "Object\Monster\SkelIceMagician.h"
#include "Object\Effect\BulletMakeEffect.h"

CSkelIceMagician::CSkelIceMagician()
	: CRangeMonster()
	, m_fCurTime(0.f)
{
	SetObjectKey(L"SkelIceMagician");
	m_pAttackRect = CRect::Create(800.f, m_tInfo.vPos);

	m_tInfo.SetSize(D3DXVECTOR3(70.f / 32.f, 100.f / 30.f, 0.f));
	SetDefaultXWay(m_tInfo.vSize.x);

	for (int i = 0; i < static_cast<int>(OBJECT_STATUS::STATUS_END); ++i)
	{
		SetAnimation(static_cast<OBJECT_STATUS>(i), 0);
	}
	SetAnimation(OBJECT_STATUS::IDLE, 6);
	SetAnimation(OBJECT_STATUS::ATTACK, 12);

	SetObjType(OBJECT_TYPE::OBJECT_MONSTER);

	SetCurStatus(OBJECT_STATUS::IDLE);
	ChangeStatus();

	SetAttackCool(4.f);

	SetDamage(6.f);

	InitializeHP(10);
}

CSkelIceMagician::~CSkelIceMagician()
{
}

CSkelIceMagician * CSkelIceMagician::Create(const D3DXVECTOR3& vecPos)
{
	CSkelIceMagician* pInstance = new CSkelIceMagician;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

void CSkelIceMagician::Attack()
{
	m_bAction = true;

	SetCurStatus(OBJECT_STATUS::ATTACK);

	const D3DXVECTOR3& vecPlayerPos = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front()->GetPos();

	CSINGLETON::pSoundMgr->PlaySound(L"IceEffect.wav", CSoundMgr::CHANNEL_ID::EFFECT);
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_EFFECT,
		CBulletMakeEffect::Create
		(
			vecPlayerPos,
			ICE_BULLET_MAKE_EFFECT_SIZE,
			L"FX",
			L"IceCrystalCreate",
			ICE_BULLET_MAKE_ANIMATION
		)
	);
}

void CSkelIceMagician::Act()
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

void CSkelIceMagician::UpdateRect()
{
	const float fHalfX = 25.f;
	const float fHalfY = 25.f;

	m_tMainRect.left	= static_cast<LONG>(m_tInfo.vPos.x - fHalfX);
	m_tMainRect.right	= static_cast<LONG>(m_tInfo.vPos.x + fHalfX);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.vPos.y - fHalfY);
	m_tMainRect.bottom	= static_cast<LONG>(m_tInfo.vPos.y + fHalfY);
}