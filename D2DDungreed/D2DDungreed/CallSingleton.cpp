#include "stdafx.h"
#include "CallSingleton.h"

CMainGame*		CSINGLETON::pMainGame	= nullptr;
CTimeMgr*		CSINGLETON::pTimeMgr	= nullptr;
CFrameMgr*		CSINGLETON::pFrameMgr	= nullptr;
CDirectMgr*		CSINGLETON::pDirectMgr	= nullptr;
CKeyMgr*		CSINGLETON::pKeyMgr		= nullptr;
CTextureMgr*	CSINGLETON::pTextureMgr = nullptr;
CSceneMgr*		CSINGLETON::pSceneMgr	= nullptr;
CMathMgr*		CSINGLETON::pMathMgr	= nullptr;
CMouseMgr*		CSINGLETON::pMouseMgr	= nullptr;
CPhysicMgr*		CSINGLETON::pPhysicMgr	= nullptr;
CObjectMgr*		CSINGLETON::pObjectMgr	= nullptr;
CCamera*		CSINGLETON::pCameraMgr	= nullptr;
CInventory*		CSINGLETON::pInventory	= nullptr;
CPlayerUI*		CSINGLETON::pPlayerUI	= nullptr;
CHitScreen*		CSINGLETON::pHitScreen	= nullptr;
CMyWindow*		CSINGLETON::pWindow		= nullptr;
CSoundMgr*		CSINGLETON::pSoundMgr	= nullptr;

int	CSINGLETON::m_iHeight	= 0;
int CSINGLETON::m_iWidth	= 0;
HWND CSINGLETON::m_hWnd		= nullptr;

void CSINGLETON::InitializeSingletons()
{
	AssertSingleton();

	pDirectMgr	= CDirectMgr::GetInstance();
	pDirectMgr->SetHwnd(m_hWnd);
	pDirectMgr->SetHeight(m_iHeight);
	pDirectMgr->SetWidth(m_iWidth);
	pDirectMgr->InitDevice(MODE_FULL);

	pTextureMgr = CTextureMgr::GetInstance();

	pKeyMgr		= CKeyMgr::GetInstance();
	pSceneMgr	= CSceneMgr::GetInstance();
	pMathMgr	= CMathMgr::GetInstance();
	pMouseMgr	= CMouseMgr::GetInstance();
	pMouseMgr->Init(m_hWnd);

	pTimeMgr	= CTimeMgr::GetInstance();
	pFrameMgr	= CFrameMgr::GetInstance();
	pPhysicMgr	= CPhysicMgr::GetInstance();
	pObjectMgr	= CObjectMgr::GetInstance();
	pCameraMgr	= CCamera::GetInstance();
	pPlayerUI	= CPlayerUI::GetInstance();
	pHitScreen	= CHitScreen::GetInstance();
	pSoundMgr	= CSoundMgr::GetInstance();
	pMainGame	= CMainGame::GetInstance();
}

void CSINGLETON::DestroySingletons()
{
	pMainGame	->DestroyInstance();
	pTimeMgr	->DestroyInstance();
	pFrameMgr	->DestroyInstance();
	pWindow		->DestroyInstance();
	pDirectMgr	->DestroyInstance();
	pKeyMgr		->DestroyInstance();
	pTextureMgr	->DestroyInstance();
	pSceneMgr	->DestroyInstance();
	pMathMgr	->DestroyInstance();
	pMouseMgr	->DestroyInstance();
	pPhysicMgr	->DestroyInstance();
	pObjectMgr	->DestroyInstance();
	pCameraMgr	->DestroyInstance();
	pInventory	->DestroyInstance();
	pPlayerUI	->DestroyInstance();
	pHitScreen	->DestroyInstance();
	pSoundMgr	->DestroyInstance();

	pWindow		= nullptr;
	pMainGame	= nullptr;
	pTimeMgr	= nullptr;
	pFrameMgr	= nullptr;
	pDirectMgr	= nullptr;
	pKeyMgr		= nullptr;
	pTextureMgr = nullptr;
	pSceneMgr	= nullptr;
	pMathMgr	= nullptr;
	pMouseMgr	= nullptr;
	pPhysicMgr	= nullptr;
	pObjectMgr	= nullptr;
	pCameraMgr	= nullptr;
	pInventory	= nullptr;
	pPlayerUI	= nullptr;
	pHitScreen	= nullptr;
	pSoundMgr	= nullptr;

#ifdef _DEBUG
	assert(nullptr == pWindow);
#endif // _DEBUG
	AssertSingleton();
}

void CSINGLETON::AssertSingleton()
{
	assert(nullptr == pMainGame);
	assert(nullptr == pTimeMgr);
	assert(nullptr == pFrameMgr);
	assert(nullptr == pKeyMgr);
	assert(nullptr == pTextureMgr);
	assert(nullptr == pSceneMgr);
	assert(nullptr == pMathMgr);
	assert(nullptr == pMouseMgr);
	assert(nullptr == pPhysicMgr);
	assert(nullptr == pObjectMgr);
	assert(nullptr == pCameraMgr);
	assert(nullptr == pInventory);
	assert(nullptr == pPlayerUI);
	assert(nullptr == pSoundMgr);
}
