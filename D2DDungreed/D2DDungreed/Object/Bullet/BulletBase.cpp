#include "stdafx.h"
#include "BulletBase.h"

#include "../MoveObject.h"

CBulletBase::CBulletBase()
	: m_bDead(false)
	, m_fAngle(0.f)
	, m_fSpeed(0.f)
	, m_fHalfX(0.f)
	, m_fHalfY(0.f)
	, m_eFrom(ATTACK_FROM::ATTACK_FROM_END)
{
}

CBulletBase::~CBulletBase()
{
}

int CBulletBase::Update()
{
	if (m_bDead)
	{
		return DEAD_OBJ;
	}
	const float fDelta = CSINGLETON::pTimeMgr->GetDelta();

	m_tInfo.SetDir(D3DXVECTOR3(cosf(m_fAngle), sinf(m_fAngle), 0.f));

	m_tInfo.vDir *= m_fSpeed * fDelta;

	m_tInfo.vPos += m_tInfo.vDir;

	CGameObject::Animate();

	return NO_EVENT;
}

void CBulletBase::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fAngle);

	UpdateRect();

	RECT rc{};

	// 플레이어
	if (ATTACK_FROM::ATTACK_FROM_PLAYER == m_eFrom)
	{
		CMoveObject* pObj = nullptr;
		for (auto iter : *CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_MONSTER))
		{
			pObj = dynamic_cast<CMoveObject*>(iter);
			if (IntersectRect(&rc, &m_tMainRect, &pObj->GetRect()))
			{
				pObj->GetDamage(m_fDamage);
				m_bDead = true;
			}
		}
	}
	// 몬스터
	else if (ATTACK_FROM::ATTACK_FROM_MONSTER == m_eFrom)
	{
		CMoveObject* const pPlayer = dynamic_cast<CMoveObject*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());
		if (IntersectRect(&rc, &m_tMainRect, &pPlayer->GetRect()))
		{
			pPlayer->GetDamage(m_fDamage);
		}
	}

	if (CSINGLETON::pPhysicMgr->CollideWithTile(this))
	{
		m_bDead = true;
		SetEffect();
	}
}

void CBulletBase::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 255, 0, 0));
#endif // _DEBUG
}

void CBulletBase::UpdateRect()
{
	m_tMainRect.left = static_cast<LONG>(m_tInfo.vPos.x - m_fHalfX);
	m_tMainRect.right = static_cast<LONG>(m_tInfo.vPos.x + m_fHalfX);
	m_tMainRect.top = static_cast<LONG>(m_tInfo.vPos.y - m_fHalfY);
	m_tMainRect.bottom = static_cast<LONG>(m_tInfo.vPos.y + m_fHalfY);
}
