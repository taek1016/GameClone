#include "stdafx.h"
#include "Inventory.h"

#include "../../Object/Button/MyButton.h"
#include "InventoryItem.h"
#include "../../Object/MoveBackgroundObject/MoveBackgroundObject.h"
#include "InventoryRender.h"
#include "../../Object/Item/BasicSword.h"

IMPLEMENT_SINGLETON(CInventory)

CInventory::CInventory()
	: m_iColor(D3DCOLOR_ARGB(255, 255, 255, 255))
	, m_iItemCount(20)
	, m_iEquipCount(2)
	, m_iAccessoryCount(4)

	, m_bActivate(false)
	, m_bTapClicked(false)

	, m_wStrKey(L"Inventory")
	, m_wStrStatus(L"Base")

	, m_matWorld{}

	, m_pButton(nullptr)
	, m_pItem(nullptr)

	, m_pEquipLeftHand(nullptr)
	, m_pEquipRightHand(nullptr)
	, m_pAccessory(nullptr)
	, m_pRender(nullptr)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_matWorld.m[i][j] = 0;
		}
	}
	Initialize();
}

CInventory::~CInventory()
{
	m_bActivate = false;

	SafeDelete(m_pButton);
	SafeDelete(m_pRender);

	for (int i = 0; i < m_iItemCount; ++i)
	{
		SafeDelete(m_pItem[i]);
	}
	SafeDelete(m_pItem);

	for (int i = 0; i < m_iEquipCount; ++i)
	{
		SafeDelete(m_pEquipLeftHand[i]);
		SafeDelete(m_pEquipRightHand[i]);
	}

	SafeDelete(m_pEquipLeftHand);
	SafeDelete(m_pEquipRightHand);

	for (int i = 0; i < m_iAccessoryCount; ++i)
	{
		SafeDelete(m_pAccessory[i]);
	}

	SafeDelete(m_pAccessory);

}

void CInventory::Initialize()
{
	// 인벤토리 초기 설정
	D3DXMATRIX	matMove, matRotate, matScale;
	D3DXMatrixIdentity(&matMove);
	D3DXMatrixIdentity(&matRotate);
	D3DXMatrixIdentity(&matScale);

	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrKey,
		m_wStrStatus
	);

	float fScaleX = 300.f / pTexInfo->tImgInfo.Width;
	float fScaleY = 500.f / pTexInfo->tImgInfo.Height;

	float fNone = 0.f;

	D3DXMatrixScaling(&matScale, fScaleX, fScaleY, fNone);

	D3DXMatrixRotationZ(&matRotate, fNone);

	float iWorld = CSINGLETON::GetWidth() TO_HALF + 100;
	float iHeight = 100.f;

	D3DXVECTOR3 inventoryPos(iWorld, iHeight, 0.f);

	D3DXMatrixTranslation(&matMove, inventoryPos.x, inventoryPos.y, inventoryPos.z);

	m_matWorld = matScale * matRotate * matMove;

	// Exit 버튼 생성
	float fMargin = 50.f;
	m_pButton = CMyButton::Create
	(
		L"Inventory",
		L"InventoryExit",
		D3DXVECTOR3(inventoryPos.x - fMargin + 10, inventoryPos.y + fMargin, inventoryPos.z),
		D3DXVECTOR3(50.f / 22.f, 50.f / 19.f, 0.f)
	);

	// 아이템 칸 20개 만들기
	m_pItem = new CInventoryItem*[m_iItemCount];

	float fX = 0.f, fY = 0.f;
	for (int i = 0; i < m_iItemCount; ++i)
	{
		fX = 5 + (i % 5) * (INVENTORY_ITEM_SIZE_X + 10);
		fY = (i / 5) * INVENTORY_ITEM_SIZE_Y;
		m_pItem[i] = CInventoryItem::Create
		(
			D3DXVECTOR3(540.f + fX, 365.f + fY, 0.f),
			D3DXVECTOR3(INVENTORY_ITEM_SIZE_X / 34.f, INVENTORY_ITEM_SIZE_Y / 24.f, 0.f),
			L"Inventory",
			L"ItemBase"
		);
	}

	// 랜더링용 사각형 만들기
	m_pRender = CInventoryRender::Create
	(
		D3DXVECTOR3(650.f, 300.f, 0.f),
		D3DXVECTOR3(1.f, 1.f, 0.f),
		2,
		L"Inventory",
		L"AccessoryZone"
	);

	// 왼손 장비, 오른손 장비 만들기
	m_pEquipLeftHand = new CInventoryItem*[m_iEquipCount];

	fY = iHeight + 120.f;
	for (int i = 0; i < m_iEquipCount; ++i)
	{
		fX = 60 + i * (INVENTORY_ITEM_SIZE_X + 15);
		m_pEquipLeftHand[i] = CInventoryItem::Create
		(
			D3DXVECTOR3(iWorld + fX, fY, 0.f),
			D3DXVECTOR3(INVENTORY_ITEM_SIZE_X / 19.f, INVENTORY_ITEM_SIZE_Y / 19.f, 0.f),
			L"Inventory",
			L"Weapon"
		);
	}

	m_pEquipRightHand = new CInventoryItem*[m_iEquipCount];

	for (int i = 0; i < m_iEquipCount; ++i)
	{
		fX = 60 + i * (INVENTORY_ITEM_SIZE_X + 15);
		m_pEquipRightHand[i] = CInventoryItem::Create
		(
			D3DXVECTOR3(iWorld + 130.f + fX, fY, 0.f),
			D3DXVECTOR3(INVENTORY_ITEM_SIZE_X / 19.f, INVENTORY_ITEM_SIZE_Y / 19.f, 0.f),
			L"Inventory",
			L"Weapon"
		);
	}

	// 액세서리 칸 생성
	m_pAccessory = new CInventoryItem*[m_iAccessoryCount];

	fY = iHeight + 200.f;
	for (int i = 0; i < m_iAccessoryCount; ++i)
	{
		fX = 60 + i * (INVENTORY_ITEM_SIZE_X + 15);
		m_pAccessory[i] = CInventoryItem::Create
		(
			D3DXVECTOR3(iWorld + fX, fY, 0.f),
			D3DXVECTOR3(INVENTORY_ITEM_SIZE_X / 19.f, INVENTORY_ITEM_SIZE_Y / 19.f, 0.f),
			L"Inventory",
			L"Accesory"
		);
	}

	m_pEquipLeftHand[0]->SetItem(CBasicSword::Create(1.5f, D3DXVECTOR3(30.f, 70.f, 0.f)));
}

void CInventory::Update()
{
	if (CSINGLETON::pKeyMgr->KeyDown(KEY_V))
	{
		CSINGLETON::pInventory->ChangeActivate();
	}

	if (CSINGLETON::pKeyMgr->KeyDown(KEY_TAB))
	{
		CSINGLETON::pSoundMgr->PlaySound(L"ItemSwap.wav", CSoundMgr::CHANNEL_ID::EFFECT);
		m_bTapClicked = !m_bTapClicked;
	}
	if (!m_bActivate)
	{
		return;
	}

	if (m_pButton->GetClicked())
	{
		ChangeActivate();
		m_pButton->SetButtonNonClicked();
		return;
	}

	m_pButton->Update();
	for (int i = 0; i < m_iItemCount; ++i)
	{
		m_pItem[i]->Update();
	}

	for (int i = 0; i < m_iEquipCount; ++i)
	{
		m_pEquipLeftHand[i]->Update();
		m_pEquipRightHand[i]->Update();
	}

	for (int i = 0; i < m_iAccessoryCount; ++i)
	{
		m_pAccessory[i]->Update();
	}
}

void CInventory::Render()
{
	if (!m_bActivate)
	{
		return;
	}

	static const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrKey,
		m_wStrStatus
	);
	m_pButton->Render();

	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_matWorld);

	CSINGLETON::pDirectMgr->GetSprite()->Draw
	(
		pTexInfo->pTexture,
		nullptr,
		nullptr,
		nullptr,
		m_iColor
	);

	m_pRender->Render();

	for (int i = 0; i < m_iItemCount; ++i)
	{
		m_pItem[i]->Render();
	}
	for (int i = 0; i < m_iEquipCount; ++i)
	{
		m_pEquipLeftHand[i]->Render();
		m_pEquipRightHand[i]->Render();
	}
	for (int i = 0; i < m_iAccessoryCount; ++i)
	{
		m_pAccessory[i]->Render();
	}

}

void CInventory::ChangeActivate()
{
	{
		m_bActivate = (!m_bActivate);
		if (m_bActivate)
		{
			CSINGLETON::pSoundMgr->PlaySound(L"OpenInventory.wav", CSoundMgr::CHANNEL_ID::EFFECT);
			CSINGLETON::pMouseMgr->SetMouseType(MOUSE_TYPE::MOUSE_NORMAL);
		}
		else
		{
			CSINGLETON::pMouseMgr->SetMouseType(MOUSE_TYPE::MOUSE_ATTACK);
		}
	}
}

bool CInventory::SetItem(CBaseItem * pObj)
{
	for (int i = 0; i < m_iItemCount; ++i)
	{
		if (m_pItem[i]->IsEmpty())
		{
			m_pItem[i]->SetItem(pObj);
			return true;
		}
	}

	return false;
}

CBaseItem * CInventory::GetEquipWeapon()
{
	if (!m_bTapClicked)
	{
		return m_pEquipLeftHand[0]->GetItem();
	}
	else
	{
		return m_pEquipRightHand[0]->GetItem();
	}
}

CBaseItem * CInventory::GetEquipShield()
{
	if (!m_bTapClicked)
	{
		return m_pEquipLeftHand[1]->GetItem();
	}
	else
	{
		return m_pEquipRightHand[1]->GetItem();
	}
}
