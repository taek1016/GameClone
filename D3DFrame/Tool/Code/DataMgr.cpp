#include "stdafx.h"
#include "DataMgr.h"

IMPLEMENT_SINGLETON(CDataMgr)

CDataMgr::CDataMgr(void)
	: CBase()
	, m_iFileCount(0)
{
}

CDataMgr::~CDataMgr(void)
{
	Free();
}

void CDataMgr::Load_Mesh_Path(void)
{
	// Load StaticMesh
	list<FILE_INFO*>*	pList = new list<FILE_INFO*>;
	extractPathInfo(L"../../Resources/StaticMesh", L"\\*.X", *pList);

	m_mapLoadData.insert(make_pair(L"StaticMesh", pList));
	pList = nullptr;

	// Load Map
	pList = new list<FILE_INFO*>;
	extractPathInfo(L"../../Resources/Map", L"\\*.X", *pList);

	m_mapLoadData.insert(make_pair(L"MapMeshes", pList));
	pList = nullptr;

	// Load Map
	pList = new list<FILE_INFO*>;
	extractPathInfo(L"../../Resources/DynamicMesh", L"\\*.X", *pList);

	m_mapLoadData.insert(make_pair(L"DynamicMesh", pList));
	pList = nullptr;

}

void CDataMgr::Load_Texture_Path(void)
{
	list<FILE_INFO*>*	pList = new list<FILE_INFO*>;
	extractPathInfo(L"../../Resources/Textures", L"\\*.png", *pList);

	m_mapLoadData.insert(make_pair(L"Textures", pList));
	pList = nullptr;

	pList = new list<FILE_INFO*>;
	extractFontInfo(L"../../Resources/Font", L"\\*.png", *pList);

	m_mapLoadData.insert(make_pair(L"Font", pList));
	pList = nullptr;

}

list<FILE_INFO*>* CDataMgr::Get_DataList(const Engine::_tchar * pKey)
{
	auto iter = find_if(m_mapLoadData.begin(), m_mapLoadData.end(), Engine::CTag_Finder(pKey));

	if (m_mapLoadData.end() == iter)
	{
		return nullptr;
	}

	return m_mapLoadData[pKey];
}

void CDataMgr::Save_Data(const Engine::_tchar * pPath, void(pFunc)(HANDLE hFile))
{
	HANDLE hFile = CreateFile(pPath, GENERIC_WRITE, 0, nullptr,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}

	pFunc(hFile);

	CloseHandle(hFile);
}

void CDataMgr::Load_Data(const Engine::_tchar * pPath, void(pFunc)(HANDLE hFile))
{
	HANDLE hFile = CreateFile(pPath, GENERIC_READ, 0, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}

	pFunc(hFile);

	CloseHandle(hFile);
}

CString CDataMgr::convertRelativePath(const TCHAR* pFullPath)
{
	const int iMaxStr = 256;
	
	TCHAR szCurrent[iMaxStr]{};
	TCHAR szRelative[iMaxStr]{};

	::GetCurrentDirectory(iMaxStr, szCurrent);
	::PathRelativePathTo(szRelative, szCurrent, FILE_ATTRIBUTE_DIRECTORY, pFullPath, FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelative);
}

void CDataMgr::extractPathInfo(const TCHAR* pFullPath, const TCHAR* pExtension, list<FILE_INFO*>& rPathInfoList)
{
	wstring wStrFindPath = wstring(pFullPath) + L"\\*.*";

	CFileFind	find;

	BOOL bIsFind = find.FindFile(wStrFindPath.c_str());

	while (bIsFind)
	{
		bIsFind = find.FindNextFile();

		if (find.IsDots())
		{
			continue;
		}
		else if (find.IsDirectory())
		{
			extractPathInfo(find.GetFilePath(), pExtension, rPathInfoList);
		}
		else
		{
			if (find.IsSystem())
			{
				continue;
			}

			FILE_INFO* pFileInfo = new FILE_INFO;

			const int iMaxStr = 256;
			TCHAR szFilePath[iMaxStr]{};
			lstrcpy(szFilePath, find.GetFilePath());

			CString strExtract = ::PathFindExtension(szFilePath);
			CString strExtension = ::PathFindExtension(pExtension);

			if (strExtension.GetLength() != strExtract.GetLength())
			{
				Engine::Safe_Delete(pFileInfo);
				continue;
			}
			else
			{
				int iStrLength = strExtract.GetLength();
				bool bNotSame = false;
				for (int i = 0; i < iStrLength; ++i)
				{
					if (tolower(strExtract[i]) != tolower((strExtension[i])))
					{
						Engine::Safe_Delete(pFileInfo);
						bNotSame = true;
						break;
					}
				}
				if (bNotSame)
				{
					Engine::Safe_Delete(pFileInfo);
					continue;
				}
			}
			::PathRemoveFileSpec(szFilePath);

			pFileInfo->iResourceCount = getFileCount(pFullPath, pExtension);

			// 개수, 파일이름, 호출이름.
			m_iFileCount += pFileInfo->iResourceCount;

			CString strName = find.GetFileTitle();
			strName.Replace(L"0", L"");
			pFileInfo->wStrName = strName.GetString();

			// 상대 경로 추출
			CString wstrRelative = find.GetFileName();
			wstrRelative.Replace(L"0.", L"%d."); // (old, new)
			pFileInfo->wStrFileName = wstrRelative.GetString();

			wstrRelative = convertRelativePath(find.GetFilePath());
			lstrcpy(szFilePath, wstrRelative);
			::PathRemoveExtension(szFilePath);

			::PathRemoveFileSpec(szFilePath);
			lstrcat(szFilePath, L"\\");
			pFileInfo->wStrFilePath = szFilePath;

			rPathInfoList.push_back(pFileInfo);

			if (strExtension == L".png")
			{
				break;
			}
		}
	}
}

void CDataMgr::extractFontInfo(const TCHAR * pFullPath, const TCHAR * pExtension, list<FILE_INFO*>& rPathInfoList)
{
	wstring wStrFindPath = wstring(pFullPath) + L"\\*.*";

	CFileFind	find;

	BOOL bIsFind = find.FindFile(wStrFindPath.c_str());

	while (bIsFind)
	{
		bIsFind = find.FindNextFile();

		if (find.IsDots())
		{
			continue;
		}
		else if (find.IsDirectory())
		{
			extractPathInfo(find.GetFilePath(), pExtension, rPathInfoList);
		}
		else
		{
			if (find.IsSystem())
			{
				continue;
			}

			FILE_INFO* pFileInfo = new FILE_INFO;

			const int iMaxStr = 256;
			TCHAR szFilePath[iMaxStr]{};
			lstrcpy(szFilePath, find.GetFilePath());

			CString strExtract = ::PathFindExtension(szFilePath);
			CString strExtension = ::PathFindExtension(pExtension);

			//if (strExtension.GetLength() != strExtract.GetLength())
			//{
			//	Engine::Safe_Delete(pFileInfo);
			//	continue;
			//}
			//else
			//{
			//	int iStrLength = strExtract.GetLength();
			//	bool bNotSame = false;
			//	for (int i = 0; i < iStrLength; ++i)
			//	{
			//		if (tolower(strExtract[i]) != tolower((strExtension[i])))
			//		{
			//			Engine::Safe_Delete(pFileInfo);
			//			bNotSame = true;
			//			break;
			//		}
			//	}
			//	if (bNotSame)
			//	{
			//		Engine::Safe_Delete(pFileInfo);
			//		continue;
			//	}
			//}
			::PathRemoveFileSpec(szFilePath);

			pFileInfo->iResourceCount = 1;

			// 개수, 파일이름, 호출이름.
			m_iFileCount += pFileInfo->iResourceCount;

			CString strName = find.GetFileTitle();
			pFileInfo->wStrName = strName.GetString();

			if (0 == wcscmp(pFileInfo->wStrName.c_str(), L"equal"))
			{
				pFileInfo->wStrName = L"=";
			}
			else if (0 == wcscmp(pFileInfo->wStrName.c_str(), L"space"))
			{
				pFileInfo->wStrName = L" ";
			}
			else if (0 == wcscmp(pFileInfo->wStrName.c_str(), L"question"))
			{
				pFileInfo->wStrName = L"?";
			}
			else if (0 == wcscmp(pFileInfo->wStrName.c_str(), L"slash"))
			{
				pFileInfo->wStrName = L"/";
			}
			else if (0 == wcscmp(pFileInfo->wStrName.c_str(), L"semicolon"))
			{
				pFileInfo->wStrName = L":";
			}
			else if (0 == wcscmp(pFileInfo->wStrName.c_str(), L"dot"))
			{
				pFileInfo->wStrName = L".";
			}
			// 상대 경로 추출
			CString wstrRelative = find.GetFileName();
			pFileInfo->wStrFileName = wstrRelative.GetString();

			wstrRelative = convertRelativePath(find.GetFilePath());
			lstrcpy(szFilePath, wstrRelative);
			::PathRemoveExtension(szFilePath);

			::PathRemoveFileSpec(szFilePath);
			lstrcat(szFilePath, L"\\");
			pFileInfo->wStrFilePath = szFilePath;

			rPathInfoList.push_back(pFileInfo);
		}
	}
}

int CDataMgr::getFileCount(const TCHAR * pFullPath, const TCHAR* pExtension)
{
	wstring wstrFindPath = wstring(pFullPath) + pExtension;

	CFileFind find;
	int iCount = 0;

	BOOL bIsFind = find.FindFile(wstrFindPath.c_str());

	while (bIsFind)
	{
		bIsFind = find.FindNextFile();

		if (find.IsDots() || find.IsDirectory() || find.IsSystem())
		{
			continue;
		}

		++iCount;
	}

	return iCount;
}

void CDataMgr::find_Path(void)
{

}

HRESULT CDataMgr::Initialize_Texture(void)
{
	return S_OK;
}

HRESULT CDataMgr::Initialize_MapMeshes(void)
{
	list<FILE_INFO*>* pList = find_if(m_mapLoadData.begin(), m_mapLoadData.end(), Engine::CTag_Finder(L"MapMeshes"))->second;

	for (auto iter : *pList)
	{
		DLL::pResourcesMgr->Initialize_Meshes(DLL::pGraphicDev->GetDevice(),
			0,
			iter->wStrName.c_str(),
			Engine::MESHTYPE::TYPE_STATIC,
			iter->wStrFilePath.c_str(),
			iter->wStrFileName.c_str()
		);
	}

	return S_OK;
}

HRESULT CDataMgr::Initialize_StaticMeshes(void)
{
#pragma region LoadStaticMeshes
	list<FILE_INFO*>*pList = find_if(m_mapLoadData.begin(), m_mapLoadData.end(), Engine::CTag_Finder(L"StaticMesh"))->second;

	for (auto iter : *pList)
	{
		DLL::pResourcesMgr->Initialize_Meshes(DLL::pGraphicDev->GetDevice(),
			0,
			iter->wStrName.c_str(),
			Engine::MESHTYPE::TYPE_STATIC,
			iter->wStrFilePath.c_str(),
			iter->wStrFileName.c_str()
		);
	}
#pragma endregion


	return S_OK;
}

HRESULT CDataMgr::Initialize_DynamicMeshes(void)
{
#pragma region LoadDynamicMeshes
	list<FILE_INFO*>* pList = find_if(m_mapLoadData.begin(), m_mapLoadData.end(), Engine::CTag_Finder(L"DynamicMesh"))->second;

	auto pGraphicDev = DLL::pGraphicDev->GetDevice();
	for (auto iter : *pList)
	{
		DLL::pResourcesMgr->Initialize_Meshes(pGraphicDev,
			0,
			iter->wStrName.c_str(),
			Engine::MESHTYPE::TYPE_DYNAMIC,
			iter->wStrFilePath.c_str(),
			iter->wStrFileName.c_str()
		);
	}
#pragma endregion

	return S_OK;
}

inline void CDataMgr::Free(void)
{
	for (auto iterList : m_mapLoadData)
	{
		for (auto iter : *iterList.second)
		{
			Engine::Safe_Delete(iter);
		}
		Engine::Safe_Delete(iterList.second);
	}
	m_mapLoadData.clear();
}
