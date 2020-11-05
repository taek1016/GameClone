#include "stdafx.h"
#include "Sword.h"

#include "../Effect/NormalAttackEffect.h"

CSword::CSword()
	: CWeapon()
	, m_bSwing(false)
	, m_vecZ(D3DXVECTOR3(0.f, 0.f, 1.f))
	, m_vecStartDir{}
{
	m_tInfo.SetLook(D3DXVECTOR3(0.f, -1.f, 0.f));
}


CSword::~CSword()
{
}

int CSword::Update()
{
	if (CSINGLETON::pInventory->GetActivate())
	{
		return NO_EVENT;
	}

	if (CSINGLETON::pKeyMgr->KeyDown(KEY_LBUTTON))
	{
		m_bSwing = !m_bSwing;
		if (m_bSwing)
		{
			CSINGLETON::pSoundMgr->PlaySound(L"Swing0.wav", CSoundMgr::CHANNEL_ID::PLAYER);
		}
		else
		{
			CSINGLETON::pSoundMgr->PlaySound(L"Swing1.wav", CSoundMgr::CHANNEL_ID::PLAYER);
		}

		// 이펙트를 만듦.
		CreateEffect();
	}

	// 칼 시작점 정해줌. 
	CSword::SetStartPos();
	// 무기 각도 정함.
	CSword::SetAngle();

	return NO_EVENT;
}

void CSword::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fAngle);

	CSword::UpdateRect();
}

void CSword::UpdateRect()
{
}

void CSword::Render()
{
	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrObjectKey,
		m_wStrObjectStatus,
		0
	);
	NULL_CHECK(pTexInfo);

	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);

	D3DXVECTOR3 vecCenter(pTexInfo->tImgInfo.Width TO_HALF, static_cast<FLOAT>(pTexInfo->tImgInfo.Height), 0.f);
	CSINGLETON::pDirectMgr->GetSprite()->Draw
	(
		pTexInfo->pTexture,
		nullptr,
		&vecCenter,
		nullptr,
		m_tInfo.iColorValue
	);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect);
#endif // _DEBUG
}

void CSword::SetStartPos()
{
	const D3DXVECTOR3& mousePos = CSINGLETON::pCameraMgr->GetPos() + CSINGLETON::pMouseMgr->GetMousePos();
	const D3DXVECTOR3& playerPos = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front()->GetPos();

	// 플레이어 위치에서 마우스 위치로 가는 방향벡터
	m_tInfo.SetDir(mousePos - playerPos);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	m_tInfo.vDir *= 20.f;

	// 시작위치 정해줌.
	m_tInfo.vPos = playerPos + m_tInfo.vDir;
}

void CSword::SetAngle()
{
	float fWay = 1.f;

	D3DXVECTOR3 dirCopy = m_tInfo.vDir;

	if (dirCopy.x < 0.f)
	{
		fWay = -1.f;
	}

	D3DXVec3Normalize(&dirCopy, &dirCopy);

	m_fAngle = acosf(D3DXVec3Dot(&m_tInfo.vLook, &dirCopy));

	m_fAngle *= fWay;

	if (!m_bSwing)
	{
		m_fAngle -= D3DXToRadian(60) * fWay;
	}
	else
	{
		m_fAngle += D3DXToRadian(40) * fWay;
	}
}
