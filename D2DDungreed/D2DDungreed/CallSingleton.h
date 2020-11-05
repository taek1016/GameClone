#ifndef __CALL_MGR_H__

#include "Managers\MainGame\MainGame.h"
#include "Managers\TimeMgr\TimeMgr.h"
#include "Managers\FrameMgr\FrameMgr.h"
#include "Managers\Window\MyWindow.h"	
#include "Managers\DeviceMgr\DirectMgr.h"
#include "Managers\KeyMgr\KeyMgr.h"
#include "Managers\TextureMgr\TextureMgr.h"
#include "Managers\SceneMgr\SceneMgr.h"
#include "Managers\MathMgr\MathMgr.h"
#include "Managers\MouseMgr\MouseMgr.h"
#include "Managers\PhysicMgr\Physic.h"
#include "Managers\ObjectMgr\ObjectMgr.h"
#include "Managers\CameraMgr\CameraMgr.h"
#include "Managers\InventoryMgr\Inventory.h"
#include "Object\UI\PlayerUI.h"
#include "Managers\HitScreen\HitScreen.h"
#include "SoundMgr.h"

class CSINGLETON
{
private:
	static int	m_iHeight;
	static int	m_iWidth;
	static HWND	m_hWnd;

public:
	static void InitializeSingletons();
	static void DestroySingletons();
	
	static void SetWidth(int iWidth)
	{
		m_iWidth = iWidth;
	}
	static void SetHeight(int iHeight)
	{
		m_iHeight = iHeight;
	}
	static void SetHWND(HWND hWnd)
	{
		m_hWnd = hWnd;
	}
	static int GetHeight()
	{
		return m_iHeight;
	}
	static int GetWidth()
	{
		return m_iWidth;
	}
	static HWND GetHwnd()
	{
		return m_hWnd;
	}

private:
	static void AssertSingleton();

public:
	static	CMyWindow*		pWindow;

	static	CMainGame*		pMainGame;
	static	CTimeMgr*		pTimeMgr;
	static	CFrameMgr*		pFrameMgr;
	static	CDirectMgr*		pDirectMgr;
	static	CKeyMgr*		pKeyMgr;
	static	CTextureMgr*	pTextureMgr;
	static	CSceneMgr*		pSceneMgr;
	static	CMathMgr*		pMathMgr;
	static	CMouseMgr*		pMouseMgr;
	static	CPhysicMgr*		pPhysicMgr;
	static	CObjectMgr*		pObjectMgr;
	static	CCamera*		pCameraMgr;
	static	CInventory*		pInventory;
	static	CPlayerUI*		pPlayerUI;
	static	CHitScreen*		pHitScreen;
	static	CSoundMgr*		pSoundMgr;
};
#define __CALL_MGR_H__
#endif // !__CALL_MGR_H__