#include "stdafx.h"
#include "CallManagers.h"

CCameraMgr*		CSINGLETON::pCameraMgr	= nullptr;
CDirectMgr*		CSINGLETON::pDirectMgr	= nullptr;
CTimeMgr*		CSINGLETON::pTimeMgr	= nullptr;
CFrameMgr*		CSINGLETON::pFrameMgr	= nullptr;
CMathMgr*		CSINGLETON::pMathMgr	= nullptr;
CKeyMgr*		CSINGLETON::pKeyMgr		= nullptr;
CTextureMgr*	CSINGLETON::pTextureMgr	= nullptr;
CMouseMgr*		CSINGLETON::pMouseMgr	= nullptr;

int		CSINGLETON::m_iHeight	= 0;
int		CSINGLETON::m_iWidth	= 0;
HWND	CSINGLETON::m_hWnd		= nullptr;

void CSINGLETON::InitializeManagers()
{
	pCameraMgr	= CCameraMgr::GetInstance();
	pDirectMgr	= CDirectMgr::GetInstance();

	pDirectMgr->SetHeight(m_iHeight);
	pDirectMgr->SetWidth(m_iWidth);
	pDirectMgr->SetHwnd(m_hWnd);
	pDirectMgr->InitDevice(MODE_WIN);

	pTextureMgr = CTextureMgr::GetInstance();

	pMouseMgr	= CMouseMgr::GetInstance();
	pMouseMgr->Init(m_hWnd);

	pTimeMgr	= CTimeMgr::GetInstance();
	pFrameMgr	= CFrameMgr::GetInstance();
	pMathMgr	= CMathMgr::GetInstance();
	pKeyMgr		= CKeyMgr::GetInstance();
}

void CSINGLETON::DestroyManagers()
{
	pCameraMgr->DestroyInstance();
	pDirectMgr->DestroyInstance();
	pTextureMgr->DestroyInstance();
	pMouseMgr->DestroyInstance();
	pTimeMgr->DestroyInstance();
	pFrameMgr->DestroyInstance();
	pMathMgr->DestroyInstance();
	pKeyMgr->DestroyInstance();
}
