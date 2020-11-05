#include "stdafx.h"
#include "MouseMgr.h"

#include "../../Object/Item/BaseItem.h"

IMPLEMENT_SINGLETON(CMouseMgr)

CMouseMgr::CMouseMgr()
	: m_ptMouse{}

	, m_wstrMouseState()
	, m_wstrObjectKey(L"Cursor")

	, m_eCurMouseType(MOUSE_TYPE::MOUSE_END)
	, m_matWorld()

	, m_hWnd(nullptr)
	, m_pItem(nullptr)
{
	assert(0 == m_ptMouse.x);
	assert(0 == m_ptMouse.y);

	assert(0 == m_wstrMouseState.size());
	assert(MOUSE_END == m_eCurMouseType);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_matWorld.m[i][j] = 0;
		}
	}

	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld._11 = 3.f;
	m_matWorld._22 = 3.f;

	::ShowCursor(false);

	SetMouseType(MOUSE_TYPE::MOUSE_END);
}

CMouseMgr::~CMouseMgr()
{
	m_ptMouse.x = 0;
	m_ptMouse.y = 0;

	SafeDelete(m_pItem);
	::ShowCursor(true);
}

void CMouseMgr::Update()
{
	::GetCursorPos(&m_ptMouse);
	::ScreenToClient(m_hWnd, &m_ptMouse);
}

void CMouseMgr::LateUpdate()
{
	m_matWorld._41 = static_cast<FLOAT>(m_ptMouse.x);
	m_matWorld._42 = static_cast<FLOAT>(m_ptMouse.y);
}

void CMouseMgr::Render()
{
	if (MOUSE_TYPE::MOUSE_END == m_eCurMouseType)
	{
		return;
	}

	if (m_pItem)
	{
		const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_pItem->GetObjectKey(), m_pItem->GetObjectStatus());

		D3DXVECTOR3	vecCenter = { pTexInfo->tImgInfo.Width TO_HALF, pTexInfo->tImgInfo.Height TO_HALF, 0.f };
		CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_matWorld);
		CSINGLETON::pDirectMgr->GetSprite()->Draw(
			pTexInfo->pTexture,
			nullptr,
			&vecCenter,
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}

	if (m_eCurMouseType == MOUSE_TYPE::MOUSE_NORMAL)
	{
		const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wstrObjectKey, m_wstrMouseState);

		D3DXVECTOR3	vecCenter = { pTexInfo->tImgInfo.Width TO_HALF, pTexInfo->tImgInfo.Height TO_HALF, 0.f };
		CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_matWorld);
		CSINGLETON::pDirectMgr->GetSprite()->Draw(
			pTexInfo->pTexture,
			nullptr,
			&vecCenter,
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
	else if (m_eCurMouseType == MOUSE_TYPE::MOUSE_ATTACK)
	{
		const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wstrObjectKey, m_wstrMouseState, 0);

		D3DXVECTOR3	vecCenter = { pTexInfo->tImgInfo.Width TO_HALF, pTexInfo->tImgInfo.Height TO_HALF, 0.f };
		CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_matWorld);
		CSINGLETON::pDirectMgr->GetSprite()->Draw(
			pTexInfo->pTexture,
			nullptr,
			&vecCenter,
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);

		pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wstrObjectKey, m_wstrMouseState, 1);

		vecCenter = { pTexInfo->tImgInfo.Width TO_HALF, pTexInfo->tImgInfo.Height TO_HALF, 0.f };
		CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_matWorld);
		CSINGLETON::pDirectMgr->GetSprite()->Draw(
			pTexInfo->pTexture,
			nullptr,
			&vecCenter,
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
}

D3DXVECTOR3 CMouseMgr::GetMousePos()
{
	return D3DXVECTOR3(static_cast<FLOAT>(m_ptMouse.x), static_cast<FLOAT>(m_ptMouse.y), 0.f);
}

void CMouseMgr::SetMouseType(MOUSE_TYPE eType)
{
	m_eCurMouseType = eType;

	switch (m_eCurMouseType)
	{
	case MOUSE_NORMAL:
		m_wstrMouseState = L"MouseNormal";
		break;

	case MOUSE_ATTACK:
		m_wstrMouseState = L"MouseAttack";
		break;
	}
}

void CMouseMgr::Init(HWND hWnd)
{
	m_hWnd = hWnd;
}