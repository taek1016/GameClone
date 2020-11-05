#ifndef CollisionMgr_h__
#define CollisionMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CCollisionMgr : public CBase
{
	DECLARE_SINGLETON(CCollisionMgr)

private:
	explicit															CCollisionMgr(void);
	virtual																~CCollisionMgr(void);

public:
	void																Add_ColFunc(const Engine::_tchar* pKey, _bool(ptr)(CGameObject* pFrom, CGameObject* pTo));
	_bool																Collide_Each(const Engine::_tchar* pKey, CGameObject* pFrom, CGameObject* pTo);

private:
	map<const Engine::_tchar*, _bool(*)(CGameObject*, CGameObject*)>	m_mapColFunc;

private:
	inline virtual void													Free(void) override;
};

END
#endif // CollisionMgr_h__