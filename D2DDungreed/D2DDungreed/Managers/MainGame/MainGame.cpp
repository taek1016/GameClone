#include "stdafx.h"
#include "MainGame.h"

#include "../../Object/Player.h"

IMPLEMENT_SINGLETON(CMainGame)

CMainGame::CMainGame()
	: m_iEvent(0)
{
	Initialize();
}

CMainGame::~CMainGame()
{
}

void CMainGame::Update()
{
	CSINGLETON::pSoundMgr->UpdateSound();

	CSINGLETON::pTimeMgr->Update();
	CSINGLETON::pKeyMgr->Update();
	CSINGLETON::pMouseMgr->Update();

	CSINGLETON::pSceneMgr->Update();

	CSINGLETON::pHitScreen->Update();
}

void CMainGame::LateUpdate()
{
	CSINGLETON::pSceneMgr->LateUpdate();
	CSINGLETON::pMouseMgr->LateUpdate();
	CSINGLETON::pCameraMgr->LateUpdate();
	CSINGLETON::pHitScreen->LateUpdate();
}

void CMainGame::Render()
{
	CSINGLETON::pDirectMgr->Render_Begin();
	CSINGLETON::pSceneMgr->Render();

#ifdef _DEBUG
	CSINGLETON::pFrameMgr->RenderFPS();
#endif // _DEBUG
	
	CSINGLETON::pHitScreen->Render();

	CSINGLETON::pMouseMgr->Render();
	CSINGLETON::pDirectMgr->Render_End();
}

HRESULT CMainGame::Initialize()
{
	CSINGLETON::pSoundMgr->Initialize();
	CSINGLETON::pSceneMgr->SceneChange(SCENE_TYPE::SCENE_END, SCENE_TYPE::SCENE_LOGO);

	return S_OK;
}