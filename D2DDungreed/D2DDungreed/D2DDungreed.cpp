// D2DDungreed.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
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

	// ����� 4�� ���� �� �� ���� ������� ���� �� ��.
	lpCmdLine;
	// ���⼭ �ʱ�ȭ���� ����
	// ������ ������ �� �Ǽ� nullptr��...
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
