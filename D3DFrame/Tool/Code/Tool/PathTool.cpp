// D:\Codes\D3DFrame\Tool\Code\Tool\PathTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "D:\Codes\D3DFrame\Tool\Code\Tool\PathTool.h"
#include "afxdialogex.h"


// CPathTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPathTool, CDialogEx)

CPathTool::CPathTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PATH_DLG, pParent)
	, m_iStaticMeshCount(0)
	, m_iDynamicMeshCount(0)
	, m_iTextureCount(0)
{

}

CPathTool::~CPathTool()
{
}

void CPathTool::Renew_Data(void)
{
	int iCount = 0;

	m_iStaticMeshCount = static_cast<int>(DLL::pDataMgr->Get_DataList(L"StaticMesh")->size());

	UpdateData(FALSE);
}

void CPathTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_MESH_COUNT_EDIT, m_iStaticMeshCount);
	DDX_Text(pDX, IDC_DYNAMIC_MESH_COUNT_EDIT, m_iDynamicMeshCount);
	DDX_Text(pDX, IDC_TEXTURE_COUNT_EDIT, m_iTextureCount);
}


BEGIN_MESSAGE_MAP(CPathTool, CDialogEx)
	ON_BN_CLICKED(IDC_PATH_SAVE_BUTTON, &CPathTool::OnBnClickedPathSaveButton)
	ON_BN_CLICKED(IDC_COUNT_SAVE_BUTTON, &CPathTool::OnBnClickedCountSaveButton)
	ON_EN_CHANGE(IDC_STATIC_MESH_COUNT_EDIT, &CPathTool::OnEnChangeStaticMeshCountEdit)
	ON_EN_CHANGE(IDC_DYNAMIC_MESH_COUNT_EDIT, &CPathTool::OnEnChangeDynamicMeshCountEdit)
	ON_EN_CHANGE(IDC_TEXTURE_COUNT_EDIT, &CPathTool::OnEnChangeTextureCountEdit)
END_MESSAGE_MAP()


// CPathTool 메시지 처리기입니다.


void CPathTool::OnBnClickedPathSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	const Engine::_tchar* szDataDefaultpath = L"../../Data/Path/";
	const Engine::_tchar* szToken = L"|";

	const int iMaxStr = 256;
	Engine::_tchar szPath[iMaxStr]{};

	Engine::_tchar* szDataType[] = { L"StaticMesh", L"DynamicMesh", L"Textures", L"Font" };
	const int iDataSize = sizeof(szDataType) / sizeof(szDataType[0]);

	// 한글 설정
	std::locale::global(std::locale("Korean"));

	wofstream fOut;
	for (int i = 0; i < iDataSize; ++i)
	{
		::ZeroMemory(szPath, sizeof(Engine::_tchar) * iMaxStr);
		wsprintf(szPath, L"%s%s%s", szDataDefaultpath, szDataType[i], L".txt");

		auto pList = DLL::pDataMgr->Get_DataList(szDataType[i]);

		if (pList == nullptr)
		{
			continue;
		}

		fOut.open(szPath);

		if (fOut.fail())
		{
			continue;
		}

		for (auto iter : *pList)
		{
			fOut << iter->wStrName << szToken << iter->iResourceCount << szToken
				<< iter->wStrFileName << szToken << iter->wStrFilePath << endl;
		}

		fOut.close();
	}

	MessageBox(L"../../Data/Path 폴더를 확인하세요.");
}


void CPathTool::OnBnClickedCountSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Renew_Data();

	const Engine::_tchar* szDataDefaultpath = L"../../Data/Path/";
	const Engine::_tchar* szToken = L"|";

	const int iMaxStr = 256;
	Engine::_tchar szPath[iMaxStr]{};

	HANDLE hFile = nullptr;
	Engine::_tchar* szDataType[] = { L"StaticMesh", L"DynamicMesh", L"Textures", L"Font" };
	const int iDataSize = sizeof(szDataType) / sizeof(szDataType[0]);
	
	Engine::_int iData = 0;

	for (int i = 0; i < iDataSize; ++i)
	{
		auto pList = DLL::pDataMgr->Get_DataList(szDataType[i]);

		iData += static_cast<Engine::_int>(pList->size());
	}

	DWORD dwBytes = 0;
	::ZeroMemory(szPath, sizeof(Engine::_tchar) * iMaxStr);
	wsprintf(szPath, L"%s%s%s", szDataDefaultpath, L"PrefabCount", L".count");

	hFile = CreateFile(szPath, GENERIC_WRITE, 0, nullptr,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		CloseHandle(hFile);
		return;
	}

	WriteFile(hFile, &iData, sizeof(Engine::_int), &dwBytes, NULL);
	printf("총 개수 : %d\n", iData);
	
	CloseHandle(hFile);

	MessageBox(L"../../Data/Path 폴더를 확인하세요.");
}


void CPathTool::OnEnChangeStaticMeshCountEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPathTool::OnEnChangeDynamicMeshCountEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPathTool::OnEnChangeTextureCountEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
