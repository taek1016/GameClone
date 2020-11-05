#include "stdafx.h"
#include "Door.h"


CDoor::CDoor()
	: m_bClosed(false)
	, m_bAlreadyIn(false)
{
	SetObjectKey(L"Dungeon");
	SetObjectStatus(L"Door");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(10.f);

	m_tInfo.SetSize(D3DXVECTOR3(150.f / 57.f, 200.f / 65.f, 0.f));
}


CDoor::~CDoor()
{
}

CDoor * CDoor::Create(const D3DXVECTOR3 & vecPos, const bool bAlreadyIn)
{
	CDoor* pInstance = new CDoor;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->SetIn(bAlreadyIn);
	pInstance->UpdateRect();


	return pInstance;
}

int CDoor::Update()
{
	// 플레이어가 F키 눌러야 하는 객체일 때.
	if (!m_bAlreadyIn)
	{
		if (CSINGLETON::pKeyMgr->KeyDown(KEY_F))
		{
			m_bAlreadyIn = true;
		}
		else
		{
			return NO_EVENT;
		}
	}

	// 플레이어가 서 있으면 반응없고
	// 플레이어가 충돌반경에서 벗어나면 닫힘.
	if (!m_bClosed)
	{
		CGameObject* pPlayer = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front();

		RECT rc{};
		if (IntersectRect(&rc, &pPlayer->GetRect(), &m_tMainRect))
		{
			m_bClosed = true;
		}
	}
	else
	{
		m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta();
		if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
		{
			m_tFrame.fCurFrame = m_tFrame.fMaxFrame - 1;
		}
	}


	return 0;
}

void CDoor::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);
}

void CDoor::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 0, 255, 0));
#endif // _DEBUG

}

void CDoor::UpdateRect()
{
	float fHalfX = 50.f;
	float fHalfY = 100.f;
	m_tMainRect.left	= static_cast<LONG>(m_tInfo.vPos.x - fHalfX);
	m_tMainRect.right	= static_cast<LONG>(m_tInfo.vPos.x + fHalfX);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.vPos.y - fHalfY);
	m_tMainRect.bottom	= static_cast<LONG>(m_tInfo.vPos.y + fHalfY);
}