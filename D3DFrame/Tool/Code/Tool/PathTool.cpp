// D:\Codes\D3DFrame\Tool\Code\Tool\PathTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "D:\Codes\D3DFrame\Tool\Code\Tool\PathTool.h"
#include "afxdialogex.h"


// CPathTool ��ȭ �����Դϴ�.

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


// CPathTool �޽��� ó�����Դϴ�.


void CPathTool::OnBnClickedPathSaveButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.


	const Engine::_tchar* szDataDefaultpath = L"../../Data/Path/";
	const Engine::_tchar* szToken = L"|";

	const int iMaxStr = 256;
	Engine::_tchar szPath[iMaxStr]{};

	Engine::_tchar* szDataType[] = { L"StaticMesh", L"DynamicMesh", L"Textures", L"Font" };
	const int iDataSize = sizeof(szDataType) / sizeof(szDataType[0]);

	// �ѱ� ����
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

	MessageBox(L"../../Data/Path ������ Ȯ���ϼ���.");
}


void CPathTool::OnBnClickedCountSaveButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	printf("�� ���� : %d\n", iData);
	
	CloseHandle(hFile);

	MessageBox(L"../../Data/Path ������ Ȯ���ϼ���.");
}


void CPathTool::OnEnChangeStaticMeshCountEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CPathTool::OnEnChangeDynamicMeshCountEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CPathTool::OnEnChangeTextureCountEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
