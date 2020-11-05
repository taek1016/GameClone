#include "stdafx.h"
#include "MoveObject.h"

CMoveObject::CMoveObject()
	: CGameObject()

	, m_fAngle(0.f)
	, m_fSpeed(0.f)
	, m_tGravityInfo{}

	, m_iObjectStatus{}

	, m_tJumpCount()

	, m_eCurStatus(OBJECT_STATUS::IDLE)
	, m_ePreStatus(OBJECT_STATUS::STATUS_END)

	, m_bGround(false)

	, m_bHit(false)

	, m_iHP(0)
	, m_iMaxHP(0)

	, m_NextHitCool()
{
	CMoveObject::AssertMember();
	InitializeAnimation();

	m_NextHitCool.SetCool(0.5f);
}

CMoveObject::~CMoveObject()
{
	CMoveObject::AssertMember();
}

void CMoveObject::Render()
{
	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrObjectKey,
		m_wStrObjectStatus,
		static_cast<WORD>(m_tFrame.fCurFrame)
	);
	assert(nullptr != pTexInfo);
	NULL_CHECK(pTexInfo);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
	UpdateRect();

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(
		m_tMainRect,
		D3DCOLOR_ARGB(255, 255, 125, 255));

	const D3DXVECTOR3& cameraPos = CSINGLETON::pCameraMgr->GetPos();

	D3DXVECTOR2 temp[2] = {
		D3DXVECTOR2(m_tInfo.vPos.x - cameraPos.x, m_tInfo.vPos.y - cameraPos.y),
		D3DXVECTOR2(m_tInfo.vPos.x + 10.f - cameraPos.x, m_tInfo.vPos.y - cameraPos.y)
	};
	CSINGLETON::pDirectMgr->GetLine()->Draw(
		temp,
		2,
		D3DCOLOR_ARGB(255, 255, 0, 0)
	);
#endif // _DEBUG
}

void CMoveObject::SetCollideGround()
{
	m_tJumpCount.SetCurCount(0);
	m_tJumpCount.SetAction(false);

	m_tGravityInfo.SetInitial();

	m_bGround = true;
}

void CMoveObject::ChangeStatus()
{
	if (m_eCurStatus != m_ePreStatus)
	{
		CMoveObject::SetStatus();
		CMoveObject::SetFrame();
	}
}

void CMoveObject::SetStatus()
{
	switch (m_eCurStatus)
	{
	case IDLE:
		CGameObject::SetObjectStatus(L"Idle");
		break;
	case MOVE:
		CGameObject::SetObjectStatus(L"Move");
		break;
	case ATTACK:
		CGameObject::SetObjectStatus(L"Attack");
		break;
	case JUMP:
		CGameObject::SetObjectStatus(L"Jump");
		m_bGround = false;
		break;
	case SKILL:
		CGameObject::SetObjectStatus(L"Skill");
		break;
	case DIE:
		CGameObject::SetObjectStatus(L"Die");
		break;
	}
}

void CMoveObject::AssertMember()
{
	m_fAngle = 0.f;
	m_fSpeed = 0.f;

	m_eCurStatus = OBJECT_STATUS::STATUS_END;
	m_ePreStatus = OBJECT_STATUS::STATUS_END;

	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 0.f;

	m_tGravityInfo.fAcc = 0.f;
	m_tGravityInfo.fPower = 0.f;

	for (int i = 0; i < OBJECT_STATUS::STATUS_END; ++i)
	{
		m_iObjectStatus[i] = 0;
	}

	m_iWidth = 0;
	m_iHeight = 0;

	assert(0.f == m_tGravityInfo.fAcc);
	assert(0.f == m_tGravityInfo.fPower);

	assert(0.f == m_fAngle);
	assert(0.f == m_fSpeed);

#ifdef _DEBUG
	for (int i = 0; i < OBJECT_STATUS::STATUS_END; ++i)
	{
		assert(0 == m_iObjectStatus[i]);
	}
#endif // _DEBUG
}

void CMoveObject::UpdateRect()
{
	// 몸통 Rect에 대해 그림그리기
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrObjectKey,
		m_wStrObjectStatus,
		0
	);

	float fWidth = pTexInfo->tImgInfo.Width	* m_tInfo.vSize.x TO_HALF TO_HALF;
	float fHeight = pTexInfo->tImgInfo.Height * m_tInfo.vSize.y TO_HALF TO_HALF;

	m_tMainRect.left = static_cast<LONG>(m_tInfo.vPos.x - fWidth);
	m_tMainRect.right = static_cast<LONG>(m_tInfo.vPos.x + fWidth);
	m_tMainRect.top = static_cast<LONG>(m_tInfo.vPos.y - fHeight);
	m_tMainRect.bottom = static_cast<LONG>(m_tInfo.vPos.y + fHeight);
}

void CMoveObject::FreeDownObject()
{
	// 지상이 아닐 때 가속도 붙게 만들기.
	if (!m_bGround)
	{
		m_tGravityInfo.SetAcc(m_tGravityInfo.fAcc + 1.5f * CSINGLETON::pTimeMgr->GetDelta() * 2);
		if (m_tGravityInfo.fAcc >= MAX_ACC)
		{
			m_tGravityInfo.SetAcc(MAX_ACC);
		}
		m_tMove.y = CSINGLETON::pMathMgr->ConvertGravity(&m_tGravityInfo);
	}
	else
	{
		m_tGravityInfo.SetAcc(0.f);
	}
}

void CMoveObject::CheckMapOutside()
{
	int iWidth = m_tMainRect.right - m_tMainRect.left;
	if (iWidth > m_tInfo.vPos.x)
	{
		m_tInfo.vPos.x = static_cast<FLOAT>(iWidth);
	}
	else if (m_tInfo.vPos.x > MAX_MAPSIZE_X - iWidth)
	{
		m_tInfo.vPos.x = static_cast<FLOAT>(MAX_MAPSIZE_X - iWidth);
	}
}

void CMoveObject::Jump()
{
	if (m_tJumpCount.iCurCount < m_tJumpCount.iMaxCount)
	{
		CMoveObject::SetCurStatus(OBJECT_STATUS::JUMP);

		m_tInfo.vPos.y -= 1;
		UpdateRect();

		m_tGravityInfo.SetPower(-9.f);
		m_tGravityInfo.SetAcc(0.f);

		m_tJumpCount.SetCurCount(m_tJumpCount.iCurCount + 1);
		m_tJumpCount.SetAction(true);

		CSINGLETON::pSoundMgr->PlaySound(L"Jump.wav", CSoundMgr::CHANNEL_ID::EFFECT);
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_EFFECT,
			CEffect::Create(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 30.f, 0.f), D3DXVECTOR3(30.f, 30.f, 0.f), EFFECT_TYPE::EFFECT_JUMP)
		);

	}
}

void CMoveObject::Move(float fX)
{
	m_tMove.x = fX;
	if (m_bGround)
	{
		SetCurStatus(OBJECT_STATUS::MOVE);
	}
}