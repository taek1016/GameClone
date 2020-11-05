#ifndef LoadMgr_h__
#define LoadMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

class CDataMgr : public CBase
{
	DECLARE_SINGLETON(CDataMgr)


private:
	explicit										CDataMgr(void);
	virtual											~CDataMgr(void);

public:
	HRESULT											Initialize_Texture(void);
	HRESULT											Initialize_MapMeshes(void);
	HRESULT											Initialize_StaticMeshes(void);
	HRESULT											Initialize_DynamicMeshes(void);

	void											Load_Mesh_Path(void);
	void											Load_Texture_Path(void);
	
	list<FILE_INFO*>*								Get_DataList(const Engine::_tchar* pKey);

	void											Save_Data(const Engine::_tchar* pPath, void(pFunc)(HANDLE hFile));
	void											Load_Data(const Engine::_tchar* pPath, void(pFunc)(HANDLE hFile));
private:
	CString											convertRelativePath(const TCHAR* pFullPath);
	void											extractPathInfo(const TCHAR* pFullPath, const TCHAR* pExtension, list<FILE_INFO*>& rPathInfoList);
	void											extractFontInfo(const TCHAR* pFullPath, const TCHAR* pExtension, list<FILE_INFO*>& rPathInfoList);
	int												getFileCount(const TCHAR* pFullPath, const TCHAR* pExtension);
	void											find_Path(void);


	Engine::_int									m_iFileCount;
	map<const Engine::_tchar*, list<FILE_INFO*>*>	m_mapLoadData;

private:
	inline virtual void								Free(void);
};

#endif // LoadMgr_h__
