#include "stdafx.h"
#include "PlayerUI.h"

#include "PlayerHP.h"
#include "PlayerDash.h"

IMPLEMENT_SINGLETON(CPlayerUI)

CPlayerUI::CPlayerUI()
	: m_pPlayerHP(nullptr)
	, m_pPlayerDash(nullptr)
{
	m_pPlayerHP = CPlayerHP::Create(D3DXVECTOR3(PLAYER_UI_SIZE_X - 50.f, PLAYER_UI_SIZE_Y, 0.f));
	m_pPlayerDash = CPlayerDash::Create(D3DXVECTOR3(PLAYER_UI_SIZE_X - 50.f, PLAYER_UI_SIZE_Y + 40.f, 0.f));
}


CPlayerUI::~CPlayerUI()
{
	SafeDelete(m_pPlayerDash);
	SafeDelete(m_pPlayerHP);
}

void CPlayerUI::Update()
{
	if (m_pPlayerHP)
	{
		m_pPlayerHP->Update();
	}

	if (m_pPlayerDash)
	{
		m_pPlayerDash->Update();
	}
}

void CPlayerUI::LateUpdate()
{
	if (m_pPlayerHP)
	{
		m_pPlayerHP->LateUpdate();
	}
	if (m_pPlayerDash)
	{
		m_pPlayerDash->LateUpdate();
	}

}

void CPlayerUI::Render()
{
	if (m_pPlayerHP)
	{
		m_pPlayerHP->Render();
	}
	if (m_pPlayerDash)
	{
		m_pPlayerDash->Render();
	}
}
