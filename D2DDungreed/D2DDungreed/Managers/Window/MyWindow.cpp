#include "stdafx.h"
#include "Resource.h"
#include "MyWindow.h"

IMPLEMENT_SINGLETON(CMyWindow)

CMyWindow::CMyWindow()
	: m_iWindowWidthSize(0)
	, m_iWindowHeightSize(0)
	, m_iCmdShow(SW_SHOW)
	
	, m_Msg{}

	, m_hWnd(nullptr)
	, m_hInst(nullptr)
	, m_hParentInst(nullptr)
	
	, m_WndProc(nullptr)
	, m_pWStrAppName(nullptr)
	, m_pWStrTitleName(nullptr)
	, m_rcWindowSize{}
{
}

CMyWindow::~CMyWindow()
{
}

LRESULT WINAPI CMyWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return CSINGLETON::pWindow->WindowMsgProc(hWnd, msg, wParam, lParam);
}

LRESULT CMyWindow::WindowMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND CMyWindow::CreateWin(TCHAR* pStrTitleName, TCHAR* pStrAppName,
	HINSTANCE hInst, WNDPROC WndProc, DWORD dwStyle)
{
	m_hInst = hInst;
	m_WndProc = (WNDPROC)WndProc;
	m_pWStrAppName = pStrAppName;
	m_pWStrTitleName = pStrTitleName;

	assert(nullptr != m_hInst);
	NULL_CHECK_RETURN(m_hInst, nullptr);

	MyRegisterClass();
	CMyWindow::SetRect(dwStyle);

	bool bMakeWindow = GetWindow();
	assert(bMakeWindow);
	FAILED_CHECK_RETURN(bMakeWindow, nullptr);

	CenterWindow(m_hWnd);

	ShowWindow(m_hWnd, m_iCmdShow);
	UpdateWindow(m_hWnd);

	return m_hWnd;
}

void CMyWindow::CenterWindow(HWND hWnd)
{
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

	int iDestX = static_cast<int>((iScreenWidth - (m_rcWindowSize.right - m_rcWindowSize.left)) TO_HALF);
	int iDestY = static_cast<int>((iScreenHeight - (m_rcWindowSize.bottom - m_rcWindowSize.top)) TO_HALF);

	MoveWindow
	(
		hWnd,
		iDestX,
		iDestY,
		m_rcWindowSize.right - m_rcWindowSize.left,
		m_rcWindowSize.bottom - m_rcWindowSize.top,
		true
	);
}

void CMyWindow::SetWindowSize(int iX, int iY)
{
	m_iWindowWidthSize = iX;
	m_iWindowHeightSize = iY;
}

void CMyWindow::SetWindowData(HINSTANCE hParentInstance, int iCmdShow)
{
	m_hParentInst = hParentInstance;
	m_iCmdShow = iCmdShow;
}

const HWND CMyWindow::GetHWND() const
{
	return m_hWnd;
}

const HINSTANCE CMyWindow::GetHInstance() const
{
	return m_hInst;
}

ATOM CMyWindow::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= m_WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_hInst;
	wcex.hIcon			= LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_D2DDUNGREED));
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= m_pWStrTitleName;
	wcex.lpszClassName	= m_pWStrAppName;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

void CMyWindow::SetRect(DWORD dwStyle)
{
	::SetRect
	(
		&m_rcWindowSize,
		0,
		0,
		m_iWindowWidthSize,
		m_iWindowHeightSize
	);

	::AdjustWindowRect
	(
		&m_rcWindowSize,
		dwStyle,
		FALSE
	);
	assert(m_rcWindowSize.right - m_rcWindowSize.left > m_iWindowWidthSize);
	assert(m_rcWindowSize.bottom - m_rcWindowSize.top > m_iWindowHeightSize);
}

bool CMyWindow::GetWindow()
{
	m_hWnd = CreateWindowW
	(
		m_pWStrAppName, m_pWStrTitleName,
		WS_OVERLAPPEDWINDOW,
		m_rcWindowSize.left,
		m_rcWindowSize.top,
		m_rcWindowSize.right - m_rcWindowSize.left,
		m_rcWindowSize.bottom - m_rcWindowSize.top,
		nullptr,
		nullptr,
		m_hInst,
		nullptr
	);

	if (m_hWnd == NULL)
	{
		return false;
	}

	return true;
}

const MSG & CMyWindow::GetMsg() const
{
	return m_Msg;
}

const int CMyWindow::GetWindowWidth() const
{
	return m_iWindowWidthSize;
}

const int CMyWindow::GetWindowHeight() const
{
	return m_iWindowHeightSize;
}

void CMyWindow::Run()
{
	while (m_Msg.message != WM_QUIT)
	{
		if (PeekMessage(&m_Msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_Msg);
			DispatchMessage(&m_Msg);
		}

		// 여기에 프레임에 맞춰 메인게임 돌리기.

		if (CSINGLETON::pFrameMgr->LimitFrame())
		{
			CSINGLETON::pMainGame->Update();
			CSINGLETON::pMainGame->LateUpdate();
			CSINGLETON::pMainGame->Render();
		}
	}
}

