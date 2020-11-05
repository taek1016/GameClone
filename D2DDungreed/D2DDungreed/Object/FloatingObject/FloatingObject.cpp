#include "stdafx.h"
#include "FloatingObject.h"


CFloatingObject::CFloatingObject()
	: m_bCollide(true)
	, m_fCurTime(0.f)
{
	SetObjectKey(L"Object");
	SetObjectStatus(L"FloatingObject");

	m_tFrame.SetInitial();
}


CFloatingObject::~CFloatingObject()
{
}

CFloatingObject * CFloatingObject::Create(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3& vecSize)
{
	CFloatingObject* pInstance = new CFloatingObject;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 120.f, vecSize.y / 35.f, vecSize.z));

	return pInstance;
}

int CFloatingObject::Update()
{
	if (!m_bCollide)
	{
		m_fCurTime += CSINGLETON::pTimeMgr->GetDelta();
		if (m_fCurTime >= 0.5f)
		{
			m_fCurTime = 0.f;
			m_bCollide = true;
		}
	}
	return NO_EVENT;
}

void CFloatingObject::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);
	UpdateRect();

	CGameObject* pPlayer = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front();
	RECT rc{};

	// 플레이어만 충돌검사
	if (!m_bCollide && IntersectRect(&rc, &m_tMainRect, &pPlayer->GetRect()))
	{
		return;
	}

	// 키 입력으로 한 오브젝트만 무력화.
	// 충돌 가능 상태이면서 플레이어와 충돌일 때

	if (m_bCollide && IntersectRect(&rc, &m_tMainRect, &pPlayer->GetRect()))
	{
		if (CSINGLETON::pKeyMgr->KeyPressing(KEY_DOWN) && CSINGLETON::pKeyMgr->KeyDown(KEY_SPACE))
		{
			m_bCollide = false;
		}
		else
		{
			float fMove = static_cast<float>(rc.bottom) - rc.top;
			const D3DXVECTOR3& playerPos = pPlayer->GetPos();
			pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y - fMove, playerPos.z));
		}
	}
}

void CFloatingObject::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CFloatingObject::UpdateRect()
{
	float fHalfX = m_tInfo.vSize.x * 120.f;
	float fHalfY = m_tInfo.vSize.y * 35.f;

	m_tMainRect.left	= static_cast<LONG>(m_tInfo.vPos.x - fHalfX);
	m_tMainRect.right	= static_cast<LONG>(m_tInfo.vPos.x + fHalfX);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.vPos.x - fHalfY);
	m_tMainRect.bottom	= static_cast<LONG>(m_tInfo.vPos.x + fHalfY);
}
