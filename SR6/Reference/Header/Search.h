#ifndef Search_h__
#define Search_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)
class CGameObject;

class ENGINE_DLL CSearch : public CBase
{
private:
	explicit	CSearch(void);

public:
	virtual		~CSearch(void);

public:
	CGameObject*							Get_Object(const _tchar* pObjTag);
	HRESULT									Add_Object(const _tchar* pObjTag, CGameObject* pObj);
	HRESULT									Delete_Object(const _tchar* pObjTag);
	CGameObject*							Get_NearList(CGameObject* pObj, list<CGameObject*>* pList, const _float fDistance);

private:
	multimap<const _tchar*, CGameObject*>	m_mapSearch;
	_float									m_fNearLength;

public:
	static CSearch*							Create(void);

private:
	virtual void							freeMem(void);
};

END

#endif // Search_h__