#include "CollisionMgr.h"

#include "Engine_Entry.h"
#include "GameObject.h"
#include "Transform.h"
#include "Collider.h"

USING(Engine)
IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr(void)
{

}

CCollisionMgr::~CCollisionMgr(void)
{
	freeMem();
}

void CCollisionMgr::Clear_List()
{
	m_ColMap.clear();
}

void CCollisionMgr::Add_Obj(CGameObject* pObj)
{
	auto iter = find_if(m_ColMap.begin(), m_ColMap.end(), CTag_Finder(pObj->Get_Name()));

	if (iter != m_ColMap.end())
	{
		return;
	}

	m_ColMap[pObj->Get_Name()] = pObj;
}

void CCollisionMgr::Delete_Obj(const _tchar* pObjTag)
{
	auto iter = find_if(m_ColMap.begin(), m_ColMap.end(), CTag_Finder(pObjTag));

	if (iter == m_ColMap.end())
	{
		return;
	}

	m_ColMap.erase(iter);
}

void CCollisionMgr::Collide_Range_Attack(CGameObject * pFrom, const _float & fCheck)
{
	CTransform* pTransform = nullptr;
	_float		fDistance = 0.f;

	CCollider* pTo = nullptr;
	CCollider* pFromCol = pFrom->Get_Component<CCollider>(COLLIDER, ID_DYNAMIC);

	for (auto iter : m_ColMap)
	{
		pTo = iter.second->Get_Component<CCollider>(COLLIDER, ID_DYNAMIC);
		fDistance = D3DXVec3Length(&(*pTo->Get_Pos() - *pFromCol->Get_Pos()));

		if (fDistance > fCheck)
		{
			continue;
		}

		if (pFromCol->Is_Collide(pTo))
		{
			iter.second->Take_Damage(pFrom->Get_Damage());
			pFrom->Set_Dead();
			break;
		}
	}

}

void CCollisionMgr::Collide_Melee_Attack(CGameObject * pFrom, const _float & fCheck)
{
	CTransform* pTransform = nullptr;
	_float		fDistance = 0.f;

	CCollider* pTo = nullptr;
	CCollider* pFromCol = pFrom->Get_Component<CCollider>(COLLIDER, ID_DYNAMIC);

	for (auto iter : m_ColMap)
	{
		pTo = iter.second->Get_Component<CCollider>(COLLIDER, ID_DYNAMIC);
		fDistance = D3DXVec3Length(&(*pTo->Get_Pos() - *pFromCol->Get_Pos()));

		if (fDistance > fCheck)
		{
			continue;
		}

		if (pFromCol->Is_Collide(pTo))
		{
			iter.second->Take_Damage(pFrom->Get_Damage());
			pFrom->Set_Dead();
		}
	}
}

_bool CCollisionMgr::Collide_Ray_To_Sphere(const _vec3 * pOrigin, CGameObject* pTarget)
{
	_vec3 vDir;

	list<CGameObject*> objList;
	for (auto iter : m_ColMap)
	{
		objList.push_back(iter.second);
	}

	// 앞에서부터 체크해야 충돌처리가 제대로 될 수 있음.
	objList.sort([](CGameObject* pFirst, CGameObject* pSecond)->bool 
	{
		const _vec3* pFirstVec = pFirst->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_Info(INFO_POS);
		const _vec3* pSecondVec = pSecond->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_Info(INFO_POS);

		return pFirstVec->z < pSecondVec->z;	// z값 따라 오름차순 정렬.
	});

	_float fPointT = 0.f;
	_float fRadius = 0.f;
	_float fX = 0.f;
	_float fY = 0.f;

	_vec3 vPointP;
	_vec3 vSphereCenter;

	for (auto iter : objList)
	{
		vSphereCenter = *iter->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_Info(INFO_POS);
		vDir = vSphereCenter - *pOrigin;

		fPointT = D3DXVec3Dot(&(vSphereCenter - *pOrigin), &vDir);

		vPointP = *pOrigin + vDir * fPointT;
		fY = D3DXVec3Length(&(vSphereCenter - vPointP));

		if (0.f > fY)
		{
			continue;
		}
		else
		{
			pTarget = iter;
			return true;
		}
	}

	return false;
}

void CCollisionMgr::Collide_Push_Obj(CGameObject * pFrom, const _float & fCheck)
{
	_float		fDistance = 0.f;

	CCollider* pTo = nullptr;
	CCollider* pFromCol = pFrom->Get_Component<CCollider>(COLLIDER, ID_DYNAMIC);

	for (auto iter : m_ColMap)
	{
		if (iter.second == pFrom)
		{
			continue;
		}
		pTo = iter.second->Get_Component<CCollider>(COLLIDER, ID_DYNAMIC);
		fDistance = D3DXVec3Length(&(*pTo->Get_Pos() - *pFromCol->Get_Pos()));

		if (fDistance > fCheck)
		{
			continue;
		}

		_float	fOverlapped = 0.f;
		if (pFromCol->Is_Collide(pTo, &fOverlapped))
		{
			// 밀치기
			CTransform* pFromTransform = pFrom->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
			CTransform* pToTransform = iter.second->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
			_vec3 vOverlapDir = *pToTransform->Get_Info(INFO_POS) - *pFromTransform->Get_Info(INFO_POS);
			pFromTransform->Move_Pos(&(*D3DXVec3Normalize(&vOverlapDir, &vOverlapDir) * -fOverlapped));
			break;
		}
	}
}

_bool CCollisionMgr::Collision_Mouse_To_Rect(const RECT * pRc, const _vec3 * pPos)
{
	POINT point{ static_cast<LONG>(pPos->x), static_cast<LONG>(pPos->y) };
	if (PtInRect(pRc, point))
	{
		return true;
	}
	return false;
}


void CCollisionMgr::freeMem()
{
	Clear_List();
}