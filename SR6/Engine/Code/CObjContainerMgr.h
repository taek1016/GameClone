#ifndef CObjContainerMgr_h__
#define CObjContainerMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;
class CObjectMgr;
class CSearchMgr;

class ENGINE_DLL CObjContainerMgr : public CBase
{
	DECLARE_SINGLETON(CObjContainerMgr)

private:
	explicit							CObjContainerMgr(void);
	virtual								~CObjContainerMgr(void);

public:
	HRESULT								Initialize_Managers(const _int& iMapNum, const _int& iObjType, const _float& fDistance = 1.f);

	template<typename T>
	T*									Add_Obj(const _tchar* pKey)
	{
		T* pInstance = T::Create();

		m_mapContainer.insert(make_pair(pKey, pInstance));

		return pInstance;
	}
	HRESULT                             Add_Objects(const _tchar* pKey, CGameObject* pObj);

	CGameObject*						Clone(const _int iMapNum, const _int& iObjTag, const _tchar* pKey, const _vec3* pPos = nullptr);

private:
	map<const _tchar*, CGameObject*>	m_mapContainer;
	CObjectMgr*							m_pObjMgr;
	CSearchMgr*							m_pSearchMgr;

private:
	inline virtual void					freeMem();
};

END
#endif // CObjContainerMgr_h__