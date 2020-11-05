// D2DDungreed.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "D2DDungreed.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#include <crtdbg.h>

#endif

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

	// 경고레벨 4라 참조 안 된 변수 경고때문에 참조 한 번.
	lpCmdLine;
	// 여기서 초기화해준 이유
	// 윈도우 생성이 안 되서 nullptr임...
	CSINGLETON::pWindow = CMyWindow::GetInstance();

	CSINGLETON::pWindow->SetWindowSize(800, 600);
	CSINGLETON::pWindow->SetWindowData(hPrevInstance, nCmdShow);

	TCHAR dungreed[128] = TEXT("D2DDungreed");

	if (!CSINGLETON::pWindow->CreateWin(dungreed, dungreed, hInstance))
	{
		return static_cast<int>(CSINGLETON::pWindow->GetMsg().message);
	}
	
	CSINGLETON::SetWidth(CSINGLETON::pWindow->GetWindowWidth());
	CSINGLETON::SetHeight(CSINGLETON::pWindow->GetWindowHeight());
	CSINGLETON::SetHWND(CSINGLETON::pWindow->GetHWND());

	CSINGLETON::InitializeSingletons();
	
	CSINGLETON::pWindow->Run();

	int iMsg = static_cast<int>(CSINGLETON::pWindow->GetMsg().message);

	CSINGLETON::DestroySingletons();

    return iMsg;
}
