#include "stdafx.h"
#include "Menu.h"

#include "..\..\Object\Button\MyButton.h"
#include "..\..\Object\Layer\MyLayer.h"
#include "..\..\Object\MoveBackgroundObject\MoveBackgroundObject.h"

CMenu::CMenu()
	: CScene()

	, m_cExitButton			(nullptr)
	, m_cPlayButton			(nullptr)

	, m_cFrontLayerFront	(nullptr)
	, m_cFrontLayerBack		(nullptr)

	, m_cMiddleCloud		(nullptr)

	, m_cBackLayerFront		(nullptr)
	, m_cBackLayerBack		(nullptr)

	, m_cBird				(nullptr)
	, m_cGroupBird			(nullptr)
{ 
	SetSceneName(L"Menu");
	SetStatus(L"MainLogo");

	CSINGLETON::pInventory = CInventory::GetInstance();
	CSINGLETON::pSoundMgr->PlayBGM(L"BGM_Title.wav");
}

CMenu::~CMenu()
{
	Release();
}

void CMenu::UpdateButton()
{
	m_cExitButton->Update();
	m_cPlayButton->Update();

	if (m_cExitButton->GetClicked())
	{
		CSINGLETON::pSoundMgr->StopAll();
		DestroyWindow(CSINGLETON::pWindow->GetHWND());
	}
	else if (m_cPlayButton->GetClicked())
	{
		CSINGLETON::pSoundMgr->StopAll();
		CSINGLETON::pSceneMgr->SceneChange(SCENE_MENU, SCENE_STAGE_0);
		m_iEvent = SCENE_CHANGE;
	}
}

void CMenu::UpdateLayer()
{
	if (SCENE_CHANGE == m_iEvent)
	{
		return;
	}

	m_cBackLayerFront	->Update();
	m_cBackLayerBack	->Update();

	m_cBird->Update();

	for (int i = 0; i < 5; ++i)
	{
		m_cGroupBird[i]->Update();
	}
	m_cFrontLayerFront	->Update();
	m_cFrontLayerBack	->Update();
}


int CMenu::Update()
{
	UpdateLayer();
	UpdateButton();

	return m_iEvent;
}

void CMenu::MoveLayerTo(CGameObject* pObj, const D3DXVECTOR3& vecPos, const bool bLeft /*= true*/)
{
	if (bLeft)
	{
		if (pObj->GetPos().x + CSINGLETON::pWindow->GetWindowWidth() - 10 <= 0)
		{
			pObj->SetPosition(vecPos);
		}

	}
	else
	{
		if (pObj->GetPos().x - CSINGLETON::pWindow->GetWindowWidth() >= 50)
		{
			pObj->SetPosition(vecPos);
		}
	}
}

void CMenu::LateUpdate()
{
	float windowWidth = static_cast<FLOAT>(CSINGLETON::pWindow->GetWindowWidth());
	D3DXVECTOR3	vecMove(windowWidth, 0.f, 0.f);

	m_cBackLayerBack->LateUpdate();
	m_cBackLayerFront->LateUpdate();

	MoveLayerTo(m_cBackLayerFront, vecMove);
	MoveLayerTo(m_cBackLayerBack, vecMove);

	float random = static_cast<FLOAT>(rand() % static_cast<int>(windowWidth - 200.f));
	m_cBird->LateUpdate();
	MoveLayerTo(m_cBird, D3DXVECTOR3{ -20.f, random, 0.f }, false);

	for (int i = 0; i < 5; ++i)
	{
		m_cGroupBird[i]->LateUpdate();
	}
	random = (rand() % static_cast<int>(windowWidth - 400.f)) + 200.f;
	for (int i = 0; i < 5; ++i)
	{
		switch (i)
		{
		case 0:
			vecMove = { m_cGroupBird[i + 1]->GetPos().x - 50.f, m_cGroupBird[2]->GetPos().y - 100.f, 0.f };
			break;
		case 1:
			vecMove = { m_cGroupBird[i + 1]->GetPos().x - 50.f, m_cGroupBird[2]->GetPos().y - 50.f, 0.f };
			break;
		case 2:
			vecMove = { -20.f, random, 0.f };
			break;
		case 3:
			vecMove = { m_cGroupBird[i - 1]->GetPos().x - 50.f, m_cGroupBird[2]->GetPos().y + 50.f, 0.f };
			break;
		case 4:
			vecMove = { m_cGroupBird[i - 1]->GetPos().x - 50.f, m_cGroupBird[2]->GetPos().y + 100.f, 0.f };
			break;
		}
		MoveLayerTo(m_cGroupBird[i], vecMove, false);
	}
	vecMove = { windowWidth, 0.f, 0.f };

	m_cFrontLayerFront->LateUpdate();
	m_cFrontLayerBack->LateUpdate();

	MoveLayerTo(m_cFrontLayerFront, vecMove);
	MoveLayerTo(m_cBackLayerBack, vecMove);
}

void CMenu::Render()
{
	m_cBackLayerBack->Render();
	m_cBackLayerFront->Render();

	m_cBird->Render();

	for (int i = 0; i < 5; ++i)
	{
		m_cGroupBird[i]->Render();
	}
	m_cFrontLayerFront->Render();
	m_cFrontLayerBack->Render();

	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wstrName, m_wStrStatus);

	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_tWorld);
	CSINGLETON::pDirectMgr->GetSprite()->Draw(
		pTexInfo->pTexture,
		nullptr,
		nullptr,
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	m_cExitButton->Render();
	m_cPlayButton->Render();
}

HRESULT CMenu::Initialize()
{
	m_tWorld._41 = 200.f;
	m_tWorld._42 = 100.f;

	m_tWorld._11 = 2.5f;
	m_tWorld._22 = 2.5f;

	m_cPlayButton = CMyButton::Create
	(
		L"Menu",
		L"Play",
		D3DXVECTOR3(350.f, 400.f, 0.f),
		D3DXVECTOR3(3.f, 3.f, 0.f)
	);

	m_cExitButton = CMyButton::Create
	(
		L"Menu",
		L"Exit",
		D3DXVECTOR3(375.f, 450.f, 0.f),
		D3DXVECTOR3(3.f, 3.f, 0.f)
	);

	float frontCloudMoveSpeed = -50.f;

	m_cFrontLayerFront = CMyLayer::Create
	(
		L"Cloud",
		L"FrontCloud",
		D3DXVECTOR3(0.f, 0.f, 0.f),
		D3DXVECTOR3(1.f, 1.f, 0.f)
	);
	
	m_cFrontLayerFront->SetSpeed(frontCloudMoveSpeed);

	m_cFrontLayerBack = CMyLayer::Create(
		L"Cloud",
		L"FrontCloud",
		D3DXVECTOR3(CSINGLETON::pWindow->GetWindowWidth() + 200.f, 0.f, 0.f),
		D3DXVECTOR3(1.f, 1.f, 0.f)
	);

	m_cFrontLayerBack->SetSpeed(frontCloudMoveSpeed);

	float middleCloudMoveSpeed = frontCloudMoveSpeed * 1.5f;

	m_cMiddleCloud = CMyLayer::Create(
		L"Cloud",
		L"MidCloud",
		D3DXVECTOR3(
			CSINGLETON::pWindow->GetWindowWidth() + 200.f, 
			CSINGLETON::pWindow->GetWindowHeight() TO_HALF, 
			0.f),
		D3DXVECTOR3(7.5f, 7.5f, 0.f)
	);

	m_cMiddleCloud->SetSpeed(middleCloudMoveSpeed);

	float backCloudMoveSpeed = frontCloudMoveSpeed TO_HALF;

	m_cBackLayerFront = CMyLayer::Create(
		L"Cloud",
		L"BackCloud",
		D3DXVECTOR3(0.f, 0.f, 0.f),
		D3DXVECTOR3(1.02f, 1.f, 0.f)
	);

	m_cBackLayerBack = CMyLayer::Create(
		L"Cloud",
		L"BackCloud",
		D3DXVECTOR3(static_cast<FLOAT>(CSINGLETON::pWindow->GetWindowWidth()), 0.f, 0.f),
		D3DXVECTOR3(1.f, 1.f, 0.f)
	);

	m_cBackLayerFront->SetSpeed(backCloudMoveSpeed);
	m_cBackLayerBack->SetSpeed(backCloudMoveSpeed);

	m_cBird = CMoveBackgroundObject::Create(
		L"Object",
		L"Bird",
		8,
		D3DXVECTOR3(-50.f, CSINGLETON::pWindow->GetWindowWidth() TO_HALF, 0.f),
		D3DXVECTOR3(3.f, 3.f, 0.f),
		100.f
	);

	m_cGroupBird = new CMoveBackgroundObject*[5];
	D3DXVECTOR3	birdPos;

	int pos = 200;
	for (int i = 0; i < 5; ++i)
	{
		switch (i)
		{
		case 0:
			birdPos = { -300.f, pos - 100.f, 0.f };
			break;
		case 1:
			birdPos = { -250.f, pos - 50.f, 0.f };
			break;
		case 2:
			birdPos = { -200.f, static_cast<FLOAT>(pos), 0.f };
			break;
		case 3:
			birdPos = { -250.f, pos + 50.f, 0.f };
			break;
		case 4:
			birdPos = { -300.f, pos + 100.f, 0.f };
			break;
		}
		m_cGroupBird[i] = CMoveBackgroundObject::Create(
			L"Object",
			L"Bird",
			8,
			birdPos,
			D3DXVECTOR3(3.f, 3.f, 0.f),
			100.f
		);
	}

	CSINGLETON::pDirectMgr->SetBackColor(D3DCOLOR_ARGB(255, 121, 185, 255));

	return S_OK;
}

void CMenu::Release()
{
	SafeDelete(m_cExitButton);
	SafeDelete(m_cPlayButton);

	SafeDelete(m_cBackLayerFront);
	SafeDelete(m_cBackLayerBack);
	
	SafeDelete(m_cMiddleCloud);

	SafeDelete(m_cFrontLayerFront);
	SafeDelete(m_cFrontLayerBack);

	SafeDelete(m_cBird);
	for (int i = 0; i < 5; ++i)
	{
		SafeDelete(m_cGroupBird[i]);
	}
	SafeDelete_Array(m_cGroupBird);
}

CMenu * CMenu::Create()
{
	CMenu*	pInstance = new CMenu;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	CSINGLETON::pMouseMgr->SetMouseType(MOUSE_TYPE::MOUSE_NORMAL);

	return pInstance;
}