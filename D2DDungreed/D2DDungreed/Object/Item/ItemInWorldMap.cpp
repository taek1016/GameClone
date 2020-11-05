#include "stdafx.h"
#include "ItemInWorldMap.h"

#include "../Item/BaseItem.h"

CItemInWorldMap::CItemInWorldMap()
	: CGameObject()

	, m_pItem(nullptr)

	, m_fYDir(50.f)

	, m_bDown(true)

	, m_bSpawn(true)
{
	m_tGravity.SetInitial();
	m_tGravity.SetPower(-3.f);
}


CItemInWorldMap::~CItemInWorldMap()
{
	if (m_pItem)
	{
		SafeDelete(m_pItem);
	}
}

CItemInWorldMap * CItemInWorldMap::Create(const D3DXVECTOR3& vecPos, const D3DXVECTOR3& vecSizeDefault, CBaseItem* pItem)
{
	CItemInWorldMap* pInstance = new CItemInWorldMap;

	pInstance->m_tInfo.SetPos(vecPos);

	pInstance->m_tInfo.SetSize(vecSizeDefault);
	pInstance->SetItem(pItem);

	pInstance->SetObjectKey(pItem->GetObjectKey());
	pInstance->SetObjectStatus(pItem->GetObjectStatus());

	return pInstance;
}

int CItemInWorldMap::Update()
{
	float fDelta = CSINGLETON::pTimeMgr->GetDelta();

	if (m_bSpawn)
	{
		m_tInfo.vPos.y += m_fYDir * fDelta;

		CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0);

		if (CSINGLETON::pPhysicMgr->CollideWithTile(&m_tMainRect, *CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_TERRAIN)))
		{
			m_bSpawn = false;
		}
		return NO_EVENT;
	}

	if (CSINGLETON::pPhysicMgr->CollideWithObject(&m_tMainRect, *CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)))
	{
		CSINGLETON::pSoundMgr->PlaySound(L"GetItem.wav", CSoundMgr::CHANNEL_ID::EFFECT);
		CSINGLETON::pInventory->SetItem(m_pItem);

		m_pItem = nullptr;

		return DEAD_OBJ;
	}

	return 0;
}

void CItemInWorldMap::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0);

	UpdateRect();
}

void CItemInWorldMap::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 0, 255, 0));
#endif // _DEBUG
}

void CItemInWorldMap::UpdateRect()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus);

	float fHalfX = m_tInfo.matWorld._11 * pTexInfo->tImgInfo.Width TO_HALF;
	float fHalfY = m_tInfo.matWorld._22 * pTexInfo->tImgInfo.Height TO_HALF;

	m_tMainRect.left = static_cast<LONG>(m_tInfo.vPos.x - fHalfX);
	m_tMainRect.right = static_cast<LONG>(m_tInfo.vPos.x + fHalfX);
	m_tMainRect.top = static_cast<LONG>(m_tInfo.vPos.y - fHalfY);
	m_tMainRect.bottom = static_cast<LONG>(m_tInfo.vPos.y + fHalfY);
}