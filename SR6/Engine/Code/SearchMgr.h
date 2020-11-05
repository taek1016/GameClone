#ifndef SearchMgr_h__
#define SearchMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CSearch;
class CGameObject;
class CObjectMgr;

class ENGINE_DLL CSearchMgr : public CBase
{
	DECLARE_SINGLETON(CSearchMgr)

private:
	explicit			CSearchMgr(void);
	virtual				~CSearchMgr(void);

public:
	HRESULT				Set_CurMap(const _int& iCurMap);
	const _vec3*		Get_Pos(const _tchar* pTag);
	HRESULT				Initialize_SearchMgr(const _int& iSearchMgrSize);
	CGameObject*		Get_Object(const _tchar* pObjTag);
	HRESULT				Add_Object(const _tchar* pObjTag, CGameObject* pObj);
	HRESULT				Delete_Object(const _tchar* pObjTag);
	CGameObject*		Find_NearObj(CGameObject* pObj, list<CGameObject*>* pList, const _float fDistance = 1.f);

private:
	_int				m_iCurMap;
	_int				m_iVecMaxIdx;
	vector<CSearch*>	m_vecSearch;
	CObjectMgr*			m_pObjMgr;

private:
	virtual void		freeMem(void);
};

END


#endif // SearchMgr_h__
