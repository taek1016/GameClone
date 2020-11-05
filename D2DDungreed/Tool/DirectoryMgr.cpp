#include "stdafx.h"
#include "DirectoryMgr.h"

CString CDirectoryMgr::ConvertRelativePath(const TCHAR * pFullPath)
{
	TCHAR szCurrent[MAX_STR]{};
	TCHAR szRelative[MAX_STR]{};

	::GetCurrentDirectory(MAX_STR, szCurrent);
	::PathRelativePathTo(szRelative, szCurrent, FILE_ATTRIBUTE_DIRECTORY, pFullPath, FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelative);
}

void CDirectoryMgr::ExtractPathInfo(const TCHAR * pFullPath, std::list<PATH_INFO*>& rPathInfoList)
{
	CString strFindPath = CString(pFullPath) + L"\\*.*";

	CFileFind	find;

	BOOL	bIsFind = find.FindFile(strFindPath);

	while (bIsFind)
	{
		bIsFind = find.FindNextFile();

		if (find.IsDots())
		{
			continue;
		}
		else if (find.IsDirectory())
		{
			ExtractPathInfo(find.GetFilePath(), rPathInfoList);
		}
		else
		{
			if (find.IsSystem())
			{
				continue;
			}

			PATH_INFO* pPathInfo = new PATH_INFO;

			TCHAR szFilePath[MAX_STR]{};
			lstrcpy(szFilePath, find.GetFilePath());
			::PathRemoveFileSpec(szFilePath);

			pPathInfo->iImgCount = GetFileCount(szFilePath);

			CString strRelative = ConvertRelativePath(find.GetFilePath());
			strRelative.Replace(L"0.", L"%d."); // (old, new)

			pPathInfo->wstrRelative = strRelative;

			// 스테이트 키 추출
			lstrcpy(szFilePath, strRelative);
			::PathRemoveFileSpec(szFilePath);

			pPathInfo->wstrStateKey = ::PathFindFileName(szFilePath);

			// 오브젝트 키 추출
			::PathRemoveFileSpec(szFilePath);

			pPathInfo->wstrObjectKey = ::PathFindFileName(szFilePath);

			rPathInfoList.push_back(pPathInfo);
			break;
		}
	}
}

int CDirectoryMgr::GetFileCount(const TCHAR * pFullPath)
{
	CString strFindPath = CString(pFullPath) + L"\\*.*";

	CFileFind	find;
	int iCount = 0;

	BOOL bIsFind = find.FindFile(strFindPath);

	while (bIsFind)
	{
		bIsFind = find.FindNextFile();

		if (find.IsDots() || find.IsDirectory() || find.IsSystem())
			continue;

		++iCount;
	}

	return iCount;
}