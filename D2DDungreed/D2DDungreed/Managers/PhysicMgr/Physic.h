#ifndef __PHYSIC_MGR_H__

class CPhysicMgr
{
	DECLARE_SINGLETON(CPhysicMgr)

private:
	CPhysicMgr();
	~CPhysicMgr();

public:
	bool IntersectMouseToRect	(const RECT& rc, const D3DXVECTOR3& pt);
	void IntersectObjToTile		(class CMoveObject* pObj);
	bool CollideWithObject		(const RECT* pObj, const OBJECT_LIST& pTo);
	bool CollideWithObject		(const RECT* pRect, float fDamage, const OBJECT_LIST& pTo);
	bool CollideWithTile		(const RECT* pObjRC, const OBJECT_LIST& pTo);
	bool IsGround				(class CMoveObject* pObj);

	bool CollideWithTile		(const CGameObject* pObj);
};

#define __PHYSIC_MGR_H__
#endif // !__PHYSIC_MGR_H__