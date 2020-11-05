#ifndef CollisionMgr_h__
#define CollisionMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CCollider;
class CGameObject;

class ENGINE_DLL CCollisionMgr : public CBase
{
	DECLARE_SINGLETON(CCollisionMgr)

private:
	explicit							CCollisionMgr(void);
	virtual								~CCollisionMgr(void);

public:
	void								Clear_List();
	void								Add_Obj(CGameObject* pObj);
	void								Delete_Obj(const _tchar* pObjTag);

	void								Collide_Range_Attack(CGameObject* pFrom, const _float& fCheck);
	void								Collide_Melee_Attack(CGameObject* pFrom, const _float& fCheck);
	
	_bool								Collide_Ray_To_Sphere(const _vec3* pOrigin, CGameObject* pTarget);

	void								Collide_Push_Obj(CGameObject* pFrom, const _float& fCheck);

	_bool								Collision_Mouse_To_Rect(const RECT* pRc, const _vec3* pPos);

private:
	map<const _tchar*, CGameObject*>	m_ColMap;

private:
	inline virtual void					freeMem();
};

END

#endif // CollisionMgr_h__
