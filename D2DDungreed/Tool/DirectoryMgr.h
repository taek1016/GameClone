#ifndef __DIRECTORY_MGR_H__

class CDirectoryMgr
{
public:
	CDirectoryMgr() = delete;
	~CDirectoryMgr() = delete;

	static CString ConvertRelativePath(const TCHAR* pFullPath);
	static void ExtractPathInfo(const TCHAR* pFullPath, std::list<PATH_INFO*>& rPathInfoList);
	static int GetFileCount(const TCHAR* pFullPath);
};

#define __DIRECTORY_MGR_H__
#endif