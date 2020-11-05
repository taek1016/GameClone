#ifndef __CALL_MANAGERS_H__

#include "../D2DDungreed/Managers/CameraMgr/CameraMgr.h"
#include "../D2DDungreed/Managers/DeviceMgr/DirectMgr.h"
#include "../D2DDungreed/Managers/TimeMgr/TimeMgr.h"
#include "../D2DDungreed/Managers/FrameMgr/FrameMgr.h"
#include "../D2DDungreed/Managers/MathMgr/MathMgr.h"
#include "../D2DDungreed/Managers/KeyMgr/KeyMgr.h"
#include "../D2DDungreed/Managers/TextureMgr/TextureMgr.h"
#include "../D2DDungreed/Managers/MouseMgr/MouseMgr.h"

class CSINGLETON
{
private:
	static int	m_iHeight;
	static int	m_iWidth;
	static HWND	m_hWnd;

public:
	static CCameraMgr*		pCameraMgr;
	static CDirectMgr*		pDirectMgr;
	static CTimeMgr*		pTimeMgr;
	static CFrameMgr*		pFrameMgr;
	static CMathMgr*		pMathMgr;
	static CKeyMgr*			pKeyMgr;
	static CTextureMgr*		pTextureMgr;
	static CMouseMgr*		pMouseMgr;

public:
	static void InitializeManagers();
	static void DestroyManagers();

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

};
#define __CALL_MANAGERS_H__
#endif // !__CALL_MANAGERS_H__