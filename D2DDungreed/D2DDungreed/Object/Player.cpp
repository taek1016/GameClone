#include "stdafx.h"
#include "Player.h"

#include "../Object/Item/Weapon.h"
#include "../Object/Effect/Effect.h"
#include "../Object/Effect/DashEffect.h"

CPlayer::CPlayer()
	: CMoveObject()

	, m_tDashCount()

	, m_fDashDelta(0.f)
	, m_fDashContinue(0.f)

	, m_pWeapon(nullptr)
{
	AssertMember();

	CGameObject::SetObjectKey(L"Player");

	SetAnimation(OBJECT_STATUS::IDLE, 5);
	SetAnimation(OBJECT_STATUS::MOVE, 8);
	SetAnimation(OBJECT_STATUS::JUMP, 1);
	SetAnimation(OBJECT_STATUS::SKILL, 0);
	SetAnimation(OBJECT_STATUS::ATTACK, 0);
	SetAnimation(OBJECT_STATUS::DIE, 1);

	m_tJumpCount.SetInitial();
	m_tJumpCount.SetMaxCount(1);

	m_tDashCount.SetInitial();
	m_tDashCount.SetCurCount(2);
	m_tDashCount.SetMaxCount(2);

	SetSpeed(DEFAULT_PLAYER_SPEED);

	InitializeHP(80);

	m_tInfo.SetLook(UP_LOOK_VECTOR);
	m_tInfo.SetSize(D3DXVECTOR3(DEFAULT_PLAYER_SIZE_X, DEFAULT_PLAYER_SIZE_Y, 0.f));
	m_tInfo.SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
}

CPlayer::~CPlayer()
{
	AssertMember();
}

CPlayer* CPlayer::Create(const D3DXVECTOR3& vPos)
{
	static CPlayer pInstance;

	pInstance.m_tInfo.SetPos(vPos);
			
	return &pInstance;
}

int CPlayer::Update()
{
	CMoveObject::HitCheck();

	CPlayer::CheckDashCount();


	if (CSINGLETON::pInventory->GetActivate())
	{
		return NO_EVENT;
	}

	m_pWeapon = dynamic_cast<CWeapon*>(CSINGLETON::pInventory->GetEquipWeapon());

	if (m_pWeapon)
	{
		m_pWeapon->Update();
	}

	if (m_tDashCount.bIsAction)
	{
		CPlayer::ContinueDash();
		return NO_EVENT;
	}

	CPlayer::KeyInput();
	CPlayer::ChangeStatus();
	CPlayer::CheckWay();

	CGameObject::Animate();

	return 0;
}

void CPlayer::LateUpdate()
{
	if (m_pWeapon)
	{
		m_pWeapon->LateUpdate();
	}

	m_tInfo.SetDir(m_tMove);
	// 이동
	m_tInfo.SetPos(m_tInfo.vPos + m_tInfo.vDir);

	CMoveObject::CheckMapOutside();

	UpdateRect();

	CSINGLETON::pPhysicMgr->IntersectObjToTile(this);

	CPlayer::UpdateRect();

	// 월드행렬 적용
	CSINGLETON::pMathMgr->CalculateMove
	(
		m_tInfo.matWorld,
		m_tInfo.vPos,
		m_tInfo.vSize,
		m_fAngle
	);

}

void CPlayer::Render()
{
	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrObjectKey,
		m_wStrObjectStatus,
		static_cast<WORD>(m_tFrame.fCurFrame)
	);
	assert(nullptr != pTexInfo);
	NULL_CHECK(pTexInfo);

	D3DXVECTOR3	vecCenter{ pTexInfo->tImgInfo.Width TO_HALF, pTexInfo->tImgInfo.Height * PLAYER_PIVOT_HEIGHT, 0.f };
	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CSINGLETON::pDirectMgr->GetSprite()->Draw
	(
		pTexInfo->pTexture,
		nullptr,
		&vecCenter,
		nullptr,
		m_tInfo.iColorValue
	);

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

	if (m_pWeapon)
	{
		m_pWeapon->Render();
	}
}

void CPlayer::ChangeJump()
{
	m_tJumpCount.SetAction(false);
}

void CPlayer::UpdateRect()
{
	float fWidth = PLAYER_WIDTH_HALF;
	float fHeight = PLAYER_HEIGHT_HALF;

	m_tMainRect.left = static_cast<LONG>(m_tInfo.vPos.x - fWidth);
	m_tMainRect.right = static_cast<LONG>(m_tInfo.vPos.x + fWidth);
	m_tMainRect.top = static_cast<LONG>(m_tInfo.vPos.y - fHeight);
	m_tMainRect.bottom = static_cast<LONG>(m_tInfo.vPos.y + fHeight);
}

void CPlayer::KeyInput()
{
	CMoveObject::SetPreStatus();
	CMoveObject::SetCurStatus(OBJECT_STATUS::IDLE);

	CMoveObject::InitializeMove();

	if (CSINGLETON::pInventory->GetActivate())
	{
		return;
	}

	// 이동
	if (CSINGLETON::pKeyMgr->KeyPressing(KEY_LEFT))
	{
		Move(-m_fSpeed * CSINGLETON::pTimeMgr->GetDelta());

		static float fDeltaTime = 0.f;
		fDeltaTime += CSINGLETON::pTimeMgr->GetDelta();
		
		if (fDeltaTime >= WALK_TIME)
		{
			fDeltaTime -= WALK_TIME;
			if (m_bGround)
			{
				CSINGLETON::pSoundMgr->PlaySound(L"Step.wav", CSoundMgr::CHANNEL_ID::EFFECT);
				CSINGLETON::pObjectMgr->AddObject
				(
					OBJECT_TYPE::OBJECT_EFFECT,
					CEffect::Create(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 30.f, 0.f), D3DXVECTOR3(30.f, 30.f, 0.f), EFFECT_TYPE::EFFECT_MOVE)
				);
			}
		}
	}
	if (CSINGLETON::pKeyMgr->KeyPressing(KEY_RIGHT))
	{
		Move(m_fSpeed * CSINGLETON::pTimeMgr->GetDelta());

		static float fDeltaTime = 0.f;
		fDeltaTime += CSINGLETON::pTimeMgr->GetDelta();

		if (fDeltaTime >= WALK_TIME)
		{
			fDeltaTime -= WALK_TIME;
			if (m_bGround)
			{
				CSINGLETON::pSoundMgr->PlaySound(L"Step.wav", CSoundMgr::CHANNEL_ID::EFFECT);
				CSINGLETON::pObjectMgr->AddObject
				(
					OBJECT_TYPE::OBJECT_EFFECT,
					CEffect::Create(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 30.f, 0.f), D3DXVECTOR3(30.f, 30.f, 0.f), EFFECT_TYPE::EFFECT_MOVE)
				);
			}
		}
	}

	// 점프 코드
	if (CSINGLETON::pKeyMgr->KeyUp(KEY_UP))
	{
		Jump();

	}

	// 자유낙하
	if (!CSINGLETON::pPhysicMgr->IsGround(this))
	{
		CMoveObject::FreeDownObject();
		m_bGround = false;
	}
	else
	{
		m_bGround = true;
	}

	// y값이 변형된 뒤에 처리해야 대쉬 처리가 제대로 됨.
	if (CSINGLETON::pKeyMgr->KeyDown(KEY_RBUTTON))
	{
		CPlayer::Dash();
	}

	if (CSINGLETON::pKeyMgr->KeyPressing(KEY_DOWN) && CSINGLETON::pKeyMgr->KeyDown(KEY_SPACE))
	{
		m_tInfo.vPos.y += 10;
		UpdateRect();
	}
}

void CPlayer::CheckWay()
{
	D3DXVECTOR3 vecMouse(CSINGLETON::pMouseMgr->GetMousePos() + CSINGLETON::pCameraMgr->GetPos() - m_tInfo.vPos);

	if (vecMouse.x >= 0.f)
	{
		m_tInfo.SetSize(D3DXVECTOR3(DEFAULT_PLAYER_SIZE_X, DEFAULT_PLAYER_SIZE_Y, 0.f));
	}
	else
	{
		m_tInfo.SetSize(D3DXVECTOR3(-DEFAULT_PLAYER_SIZE_X, DEFAULT_PLAYER_SIZE_Y, 0.f));
	}
}

void CPlayer::CheckDashCount()
{
	m_fDashDelta += CSINGLETON::pTimeMgr->GetDelta();
	if (m_fDashDelta >= DASH_REFILL_TIME)
	{
		m_fDashDelta = 0.f;
		if (m_tDashCount.iMaxCount > m_tDashCount.iCurCount)
		{
			m_tDashCount.SetCurCount(m_tDashCount.iCurCount + 1);
		}
	}
}

void CPlayer::Dash()
{
	if (0 < m_tDashCount.iCurCount)
	{
		m_tMove = CSINGLETON::pMouseMgr->GetMousePos() + CSINGLETON::pCameraMgr->GetPos() - m_tInfo.vPos;

		D3DXVec3Normalize(&m_tMove, &m_tMove);

		m_tMove *= static_cast<FLOAT>(m_fSpeed * CSINGLETON::pTimeMgr->GetDelta() * 5);
		CMoveObject::SetCurStatus(OBJECT_STATUS::JUMP);

		m_tDashCount.SetCurCount(m_tDashCount.iCurCount - 1);
		m_tDashCount.SetAction(true);

		m_tGravityInfo.SetAcc(0.f);
		m_tGravityInfo.SetPower(0.f);

		CSINGLETON::pSoundMgr->PlaySound(L"Dash.wav", CSoundMgr::CHANNEL_ID::EFFECT);
	}
}

void CPlayer::ContinueDash()
{
	m_fDashContinue += CSINGLETON::pTimeMgr->GetDelta();
	m_tGravityInfo.SetAcc(0.f);

	// 잔상 이펙트 호출.
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_EFFECT, 
		CDashEffect::Create
		(
			m_tInfo.vPos, 
			m_tInfo.vSize, 
			m_wStrObjectKey, 
			m_wStrObjectStatus, 
			static_cast<WORD>(m_tFrame.fCurFrame)
		)
	);

	if (m_fDashContinue >= DASH_TIME)
	{
		m_fDashContinue = 0.f;
		m_tDashCount.SetAction(false);
	}
}

void CPlayer::AssertMember()
{
	m_bGround = false;

	ZeroMemory(&m_tMove, sizeof(D3DXVECTOR3));
	m_tJumpCount.SetInitial();
	m_tDashCount.SetInitial();

	m_fDashDelta = 0.f;
	m_fDashContinue = 0.f;

	m_pWeapon = nullptr;

	assert(false == m_bGround);

	assert(fabsf(m_tMove.x) < FLT_EPSILON);

	assert(D3DXVECTOR3(0.f, 0.f, 0.f) == m_tMove);

	assert(0 == m_tJumpCount.iCurCount);
	assert(0 == m_tJumpCount.iMaxCount);
	assert(false == m_tJumpCount.bIsAction);

	assert(0 == m_tDashCount.iCurCount);
	assert(0 == m_tDashCount.iMaxCount);
	assert(false == m_tDashCount.bIsAction);

	assert(0.f == m_fDashDelta);
	assert(0.f == m_fDashContinue);
}