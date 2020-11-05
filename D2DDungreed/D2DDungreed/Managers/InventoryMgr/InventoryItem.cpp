#include "stdafx.h"
#include "InventoryItem.h"

#include "../../Object/Item/BaseItem.h"

CInventoryItem::CInventoryItem()
	: m_bClicked(false)
	
	, m_matWorld{}
	
	, m_vecPos{}
	, m_vecSize{}

	, m_tRECT{}
	, m_tFrame{}

	, m_wStrObjectKey()
	, m_wStrObjectStatus()
	
	, m_pItem(nullptr)
{
}

CInventoryItem::~CInventoryItem()
{
	SafeDelete(m_pItem);

	m_tRECT = {};
	m_tFrame = {};

	m_matWorld = {};

	m_wStrObjectKey.clear();
	m_wStrObjectStatus.clear();
}

CInventoryItem* CInventoryItem::Create
(
	const D3DXVECTOR3 vecPos, 
	const D3DXVECTOR3 vecSize,
	const std::wstring&	wStrObjectKey,
	const std::wstring& wStrObjectStatus
)
{
	CInventoryItem* pInstance = new CInventoryItem;

	D3DXMATRIX matMove, matScale;

	pInstance->m_vecPos = vecPos;
	pInstance->m_vecSize = vecSize;

	pInstance->m_tFrame.SetMaxFrame(1.f);

	pInstance->SetKey(wStrObjectKey);
	pInstance->SetStatus(wStrObjectStatus);
	
	pInstance->UpdateRect();

	return pInstance;
}

int CInventoryItem::Update()
{
	m_tFrame.SetCurFrame(0.f);

	if (CSINGLETON::pPhysicMgr->IntersectMouseToRect(m_tRECT, CSINGLETON::pMouseMgr->GetMousePos()))
	{
		m_tFrame.SetCurFrame(1.f);
		if (CSINGLETON::pKeyMgr->KeyDown(KEY_LBUTTON))
		{
			CSINGLETON::pSoundMgr->PlaySound(L"Equip.wav", CSoundMgr::CHANNEL_ID::EFFECT);
			CBaseItem* pItem = CSINGLETON::pMouseMgr->GetItem();
			CSINGLETON::pMouseMgr->SetItem(m_pItem);
			m_pItem = pItem;
		}
	}

	return 0;
}

void CInventoryItem::Render()
{
	const TEX_INFO*	pTexInfo = nullptr;

	if (0 != m_wStrObjectKey.size() && 0 != m_wStrObjectStatus.size())
	{
		pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
		(
			m_wStrObjectKey,
			m_wStrObjectStatus, 
			static_cast<WORD>(m_tFrame.fCurFrame)
		);

		CSINGLETON::pMathMgr->CalculateMove(m_matWorld, m_vecPos, m_vecSize, 0.f, false);

		CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_matWorld, D3DCOLOR_ARGB(255, 255, 255, 255));

#ifdef _DEBUG
		CSINGLETON::pDirectMgr->RenderRect(m_tRECT, D3DCOLOR_ARGB(255, 0, 255, 0), false);
#endif // _DEBUG

	}

	if (m_pItem)
	{
		pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
		(
			m_pItem->GetObjectKey(),
			m_pItem->GetObjectStatus()
		);

		CSINGLETON::pMathMgr->CalculateMove(m_matWorld, m_vecPos, m_pItem->GetSize(), 0.f, false);

		CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_matWorld, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CInventoryItem::UpdateRect()
{
	float xHalf = INVENTORY_ITEM_SIZE_X TO_HALF;
	float yHalf = INVENTORY_ITEM_SIZE_Y TO_HALF;

	m_tRECT.left = static_cast<LONG>(m_vecPos.x - xHalf);
	m_tRECT.top = static_cast<LONG>(m_vecPos.y - yHalf);

	m_tRECT.right = static_cast<LONG>(m_vecPos.x + xHalf);
	m_tRECT.bottom = static_cast<LONG>(m_vecPos.y + yHalf);
}