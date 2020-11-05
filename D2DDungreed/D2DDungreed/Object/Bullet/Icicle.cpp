#include "stdafx.h"
#include "Icicle.h"

#include "../Effect/Effect.h"
#include "../MoveObject.h"

CIcicle::CIcicle()
	: m_fCurTime(0.f)
{
	SetObjectKey(L"Bullet");
	SetObjectStatus(L"Icicle");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(1.f);

	SetSpeed(600.f);
	SetAngle(D3DXToRadian(90.f));

	m_tInfo.SetSize(D3DXVECTOR3(30.f / 27.f, 90.f / 40.f, 0.f));
	SetHalfXY(15.f, 40.f);

	SetDamage(5.f);

	m_tFrame.SetMaxFrame(1.f);
}

CIcicle::~CIcicle()
{
}

CIcicle * CIcicle::Create(const D3DXVECTOR3 & vecPos)
{
	CIcicle* pInstance = new CIcicle;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

void CIcicle::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);

	UpdateRect();

	RECT rc{};

	CMoveObject* const pPlayer = dynamic_cast<CMoveObject*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());
	if (IntersectRect(&rc, &m_tMainRect, &pPlayer->GetRect()))
	{
		m_bDead = true;
		pPlayer->GetDamage(m_fDamage);
	}

	m_fCurTime += CSINGLETON::pTimeMgr->GetDelta();
	if (m_fCurTime >= 1.5f)
	{
		m_bDead = true;
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_EFFECT,
			CEffect::Create(m_tInfo.vPos, D3DXVECTOR3(45.F, 90.f, 0.f), EFFECT_TYPE::EFFECT_ICICLE_DESTROY, 0.f)
		);
	}
}

void CIcicle::SetEffect()
{
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_EFFECT,
		CEffect::Create
		(
			m_tInfo.vPos,
			D3DXVECTOR3(45.f, 90.f, 0.f),
			EFFECT_TYPE::EFFECT_ICICLE_DESTROY,
			0.f
		)
	);
}