#ifndef ObjectMgr_h__
#define ObjectMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;
class CPoolMgr;

class ENGINE_DLL CObjectMgr : public CBase
{
	DECLARE_SINGLETON(CObjectMgr)

private:
	explicit										CObjectMgr(void);
	virtual											~CObjectMgr(void);

public:
	_int											Update_Objects(const _float& fTimeDelta);

	HRESULT											Add_GameObject(const _tchar* pContainerKey, CGameObject* pObj);
	void											Clear_List(void);

	list<CGameObject*>*								Get_ObjList(const _tchar* pKey) const;
	HRESULT											Set_PoolMgr(CPoolMgr* pPool);

private:
	list<CGameObject*>*								find_Layer(const _tchar* pLayerKey) const;

	list<pair<const _tchar*, list<CGameObject*>*>>	m_ObjList;
	CPoolMgr*										m_pPoolMgr = nullptr;

private:
	inline virtual void								Free(void);
};

END

#endif // ObjectMgr_h__