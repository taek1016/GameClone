// PathTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "PathTool.h"

#include "DirectoryMgr.h"
// CPathTool

IMPLEMENT_DYNAMIC(CPathTool, CDialog)

CPathTool::CPathTool(CWnd* pParent)
	: CDialog(IDD_PATHTOOL, pParent)
{

}

CPathTool::~CPathTool()
{
	for_each(m_PathInfoList.begin(), m_PathInfoList.end(), SafeDelete<PATH_INFO*>);
	m_PathInfoList.clear();
}

void CPathTool::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}

void CPathTool::SettingHorizontalScrollSize()
{
	CString strName = L"";

	int iSrcCX = 0, iDstCX = 0;

	CDC* pDC = m_ListBox.GetDC();

	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);

		// 현재 문자열의 길이를 픽셀 단위로 환산.
		iSrcCX = pDC->GetTextExtent(strName).cx;

		if (iDstCX < iSrcCX)
			iDstCX = iSrcCX;
	}

	m_ListBox.ReleaseDC(pDC);

	// 현재 리스트박스가 가지고 있는 수평 스크롤 범위보다 클 때
	if (iDstCX > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iDstCX); // 수평 스크롤
}

BEGIN_MESSAGE_MAP(CPathTool, CWnd)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_PATH_SAVE, &CPathTool::OnBnClickedPathSave)
	ON_BN_CLICKED(IDC_PATH_LOAD, &CPathTool::OnBnClickedPathLoad)
END_MESSAGE_MAP()

void CPathTool::OnDropFiles(HDROP hDropInfo)
{
	int iCount = ::DragQueryFile(hDropInfo, -1, nullptr, 0);

	TCHAR szFileName[MAX_STR] = L"";

	for (int i = 0; i < iCount; ++i)
	{
		::DragQueryFile(hDropInfo, i, szFileName, MAX_STR);
		CDirectoryMgr::ExtractPathInfo(szFileName, m_PathInfoList);
	}

	std::wstring wstrCombined = L"";
	TCHAR szCount[MIN_STR] = L"";

	for (auto pPathInfo : m_PathInfoList)
	{
		// 정수 -> 문자
		_itow_s(pPathInfo->iImgCount, szCount, 10);

		wstrCombined = pPathInfo->wstrObjectKey + L"|" + pPathInfo->wstrStateKey + L"|"
			+ szCount + L"|" + pPathInfo->wstrRelative;

		m_ListBox.AddString(wstrCombined.c_str());
	}

	SettingHorizontalScrollSize();

	CDialog::OnDropFiles(hDropInfo);
}

void CPathTool::OnBnClickedPathSave()
{
	CFileDialog Dlg(
		FALSE,
		L".txt",
		L"PathInfo.txt",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Text Files(*.txt)|*.txt|Data Files(*.dat)|*.dat||",
		this);

	TCHAR szCurrentDir[MAX_STR] = L"";

	::GetCurrentDirectory(MAX_STR, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	if (IDOK == Dlg.DoModal())
	{
		std::wofstream fout;

		fout.open(Dlg.GetPathName());

		if (fout.fail())
			return;

		std::wstring wstrCombined = L"";
		TCHAR szCount[MIN_STR] = L"";

		for (auto pPathInfo : m_PathInfoList)
		{
			// 정수 -> 문자
			_itow_s(pPathInfo->iImgCount, szCount, 10);

			wstrCombined = pPathInfo->wstrObjectKey + L"|" + pPathInfo->wstrStateKey + L"|"
				+ szCount + L"|" + pPathInfo->wstrRelative;

			fout << wstrCombined << std::endl;
		}

		fout.close();

		// 윈도우 기본 응용 프로그램 실행하는 시스템 함수.
		WinExec("notepad.exe ../Data/PathInfo.txt", SW_SHOW);
	}
}

void CPathTool::OnBnClickedPathLoad()
{
	CFileDialog Dlg(TRUE, L".txt", L"제목 없음.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Text Files(*.txt)|*.txt|Data Files(*.dat)|*.dat||", this);

	TCHAR szCurrentDir[MAX_STR] = L"";

	::GetCurrentDirectory(MAX_STR, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	if (IDOK == Dlg.DoModal())
	{
		std::wifstream fin;

		fin.open(Dlg.GetPathName());

		if (fin.fail())
			return;

		if (!m_PathInfoList.empty())
		{
			for_each(m_PathInfoList.begin(), m_PathInfoList.end(), SafeDelete<PATH_INFO*>);
			m_PathInfoList.clear();

			m_ListBox.ResetContent();
		}

		TCHAR szObjectKey[MAX_STR] = L"";
		TCHAR szStateKey[MAX_STR] = L"";
		TCHAR szCount[MAX_STR] = L"";
		TCHAR szRelative[MAX_STR] = L"";

		PATH_INFO* pPathInfo = nullptr;

		while (true)
		{
			fin.getline(szObjectKey, MAX_STR, '|');
			fin.getline(szStateKey, MAX_STR, '|');
			fin.getline(szCount, MAX_STR, '|');
			fin.getline(szRelative, MAX_STR);

			if (fin.eof())
				break;

			pPathInfo = new PATH_INFO;
			pPathInfo->wstrObjectKey = szObjectKey;
			pPathInfo->wstrStateKey = szStateKey;
			pPathInfo->iImgCount = _ttoi(szCount);
			pPathInfo->wstrRelative = szRelative;

			m_PathInfoList.push_back(pPathInfo);
		}

		fin.close();

		std::wstring wstrCombined = L"";

		for (auto pPathInfo : m_PathInfoList)
		{
			// 정수 -> 문자
			_itow_s(pPathInfo->iImgCount, szCount, 10);

			wstrCombined = pPathInfo->wstrObjectKey + L"|" + pPathInfo->wstrStateKey + L"|"
				+ szCount + L"|" + pPathInfo->wstrRelative;

			m_ListBox.AddString(wstrCombined.c_str());
		}

		SettingHorizontalScrollSize();
	}
}