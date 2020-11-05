#ifndef PoolMgr_h__
#define PoolMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CPoolMgr : public CBase
{
	DECLARE_SINGLETON(CPoolMgr)

private:
	explicit									CPoolMgr(void) = default;
	virtual										~CPoolMgr(void);

public:
	HRESULT										Add_Pool(const _tchar* pKey, CGameObject* pObj);
	HRESULT										Back_Pool(const _tchar* pKey, CGameObject* pObj);
	CGameObject*								Get_Pool(const _tchar* pKey);

private:
	CGameObject*								find_Pool(const _tchar* pKey);
	list<CGameObject*>*							find_List(const _tchar* pKey);

	const _int									m_iPoolSize = 100;
	map<const _tchar*, list<CGameObject*>*>		m_mapPool;
	map<const _tchar*, CGameObject*>			m_mapOriginalPool;

private:
	inline virtual void							Free();
};

END
#endif // PoolMgr_h__