#include "stdafx.h"
#include "Box.h"

#include "../Player.h"
#include "../Item/ItemInWorldMap.h"

CBox::CBox()
	: m_bActivate(false)
	, m_pItem(nullptr)
{
	m_tFrame.SetCurFrame(0.f);
	m_tFrame.SetMaxFrame(1.f);
}

CBox::~CBox()
{
	SafeDelete(m_pItem);
}

int CBox::Update()
{
	if (nullptr == m_pItem)
	{
		return NO_EVENT;
	}

	m_bActivate = false;

	CGameObject* pPlayer = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front();

	RECT rc{};
	if (IntersectRect(&rc, &pPlayer->GetRect(), &m_tMainRect))
	{
		
		m_bActivate = true;

		if (CSINGLETON::pKeyMgr->KeyDown(KEY_F))
		{
			m_tFrame.fCurFrame = 1.f;
			CSINGLETON::pSoundMgr->PlaySound(L"ChestOpen.wav", CSoundMgr::CHANNEL_ID::EFFECT);
			CSINGLETON::pObjectMgr->AddObject
			(
				OBJECT_TYPE::OBJECT_ITEM,
				CItemInWorldMap::Create(m_tInfo.vPos, m_pItem->GetSize(), m_pItem)
			);
			m_pItem = nullptr;
		}
	}
	return NO_EVENT;
}

void CBox::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);
}

void CBox::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrObjectKey, 
		m_wStrObjectStatus, 
		static_cast<WORD>(m_tFrame.fCurFrame)
	);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 0, 255, 0));
#endif // _DEBUG

	if (m_bActivate)
	{

	}
}

void CBox::UpdateRect()
{
	float fHalf = 30.f;

	m_tMainRect.left = static_cast<LONG>(m_tInfo.vPos.x - fHalf);
	m_tMainRect.right = static_cast<LONG>(m_tInfo.vPos.x + fHalf);
	m_tMainRect.top = static_cast<LONG>(m_tInfo.vPos.y - fHalf);
	m_tMainRect.bottom = static_cast<LONG>(m_tInfo.vPos.y + fHalf);
}