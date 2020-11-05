#ifndef __WINDOW_H__
#define __WINDOW_H__

class CMyWindow
{
	DECLARE_SINGLETON(CMyWindow)

private:
	CMyWindow();
	~CMyWindow();

public:
	static	LRESULT	WINAPI	MsgProc				(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT		WindowMsgProc			(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
			HWND		CreateWin				(TCHAR* pStrTitleName = TEXT("Default"), 
													TCHAR* pStrAppName = TEXT("Default"), 
													HINSTANCE hInst = 0, 
													WNDPROC WndProc = MsgProc,
													DWORD dwStyle = WS_OVERLAPPEDWINDOW);
			void		CenterWindow			(HWND hWnd);
			void		SetWindowSize			(int iX, int iY);
			void		SetWindowData			(HINSTANCE hParentInstance, int iCmdShow);

	const	HWND		GetHWND()				const;
	const	HINSTANCE	GetHInstance()			const;
	const	MSG&		GetMsg()				const;

	const	int			GetWindowWidth()		const;
	const	int			GetWindowHeight()		const;

			void		Run();
private:
			ATOM		MyRegisterClass();
			void		SetRect(DWORD dwStyle);
			bool		GetWindow();

private:
	HWND				m_hWnd;
	HINSTANCE			m_hInst;
	HINSTANCE			m_hParentInst;

	WNDPROC				m_WndProc;
	MSG					m_Msg;

	TCHAR*				m_pWStrAppName;
	TCHAR*				m_pWStrTitleName;

	RECT				m_rcWindowSize;

	int					m_iWindowWidthSize;
	int					m_iWindowHeightSize;
	int					m_iCmdShow;
};

#endif // !__WINDOW_H__
