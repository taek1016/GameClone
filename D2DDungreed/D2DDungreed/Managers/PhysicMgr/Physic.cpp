#include "stdafx.h"
#include "Physic.h"

#include "../D2DDungreed/Object/Terrain/Terrain.h"
#include "../D2DDungreed/Object/MoveObject.h"

IMPLEMENT_SINGLETON(CPhysicMgr)

CPhysicMgr::CPhysicMgr()
{
}

CPhysicMgr::~CPhysicMgr()
{
}

bool CPhysicMgr::IntersectMouseToRect(const RECT& rc, const D3DXVECTOR3& pt)
{
	POINT point{ static_cast<LONG>(pt.x), static_cast<LONG>(pt.y) };
	if (PtInRect(&rc, point))
	{
		return true;
	}
	return false;
}

void CPhysicMgr::IntersectObjToTile(CMoveObject* pObj)
{
	// 타일 인덱스 가져오기.
	// 타일 인덱스 위, 아래, 양 옆을 검사
	// 검사하고 난 뒤 updateRect
	RECT rc{};
	CTerrain* pTerrain = dynamic_cast<CTerrain*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_TERRAIN)->front());
	int iIndex = pTerrain->FindTile(pObj->GetPos());

	const TILE_INFO* pUpTile = pTerrain->GetTileInfo(iIndex - CTerrain::g_TileCountX);
	const TILE_INFO* pDownTile = pTerrain->GetTileInfo(iIndex + CTerrain::g_TileCountX);
	const TILE_INFO* pLeftTile = pTerrain->GetTileInfo(iIndex - 1);
	const TILE_INFO* pRightTile = pTerrain->GetTileInfo(iIndex + 1);

	const D3DXVECTOR3& ObjPos = pObj->GetPos();

	float fMove = 0.f;

	fMove = static_cast<float>(pObj->GetRect().bottom) - pDownTile->tRect.top;
	if ((0 <= fMove) && (fMove < OBJECT_TILE_DOWN_MARGIN) && pDownTile->byOption == UP_TO_DOWN)
	{
		if (pObj->GetRect().bottom >= pDownTile->tRect.top)
		{
			pObj->SetPosition(D3DXVECTOR3(ObjPos.x, ObjPos.y - fMove, 0.f));
			pObj->SetCollideGround();
		}
		return;
	}

	// 아래 충돌 - 위로 올림
	if (IntersectRect(&rc, &pObj->GetRect(), &pDownTile->tRect) && pDownTile->byOption != NO_COLLIDE)
	{
		switch (pDownTile->byOption)
		{
		case SQUARE_COLLIDE:
			fMove = static_cast<float>(rc.bottom - rc.top);
			pObj->SetPosition(D3DXVECTOR3(ObjPos.x, ObjPos.y - fMove, 0.f));
			pObj->SetCollideGround();
			break;
		}

	}
	// 위 충돌 - 밑으로 밀어냄
	else if (IntersectRect(&rc, &pObj->GetRect(), &pUpTile->tRect) && pUpTile->byOption != NO_COLLIDE)
	{
		switch (pUpTile->byOption)
		{
		case SQUARE_COLLIDE:
			fMove = static_cast<float>(rc.bottom - rc.top);
			pObj->SetPosition(D3DXVECTOR3(ObjPos.x, ObjPos.y + fMove, 0.f));
			break;
		}
	}

	if (IntersectRect(&rc, &pObj->GetRect(), &pLeftTile->tRect) && pLeftTile->byOption != NO_COLLIDE)
	{
		switch (pLeftTile->byOption)
		{
		case SQUARE_COLLIDE:
			fMove = static_cast<float>(rc.right - rc.left);
			pObj->SetPosition(D3DXVECTOR3(ObjPos.x + fMove, ObjPos.y, 0.f));
			break;
		}
	}
	else if (IntersectRect(&rc, &pObj->GetRect(), &pRightTile->tRect) && pRightTile->byOption != NO_COLLIDE)
	{
		switch (pRightTile->byOption)
		{
		case SQUARE_COLLIDE:
			fMove = static_cast<float>(rc.right - rc.left);
			pObj->SetPosition(D3DXVECTOR3(ObjPos.x - fMove, ObjPos.y, 0.f));
			break;
		}
	}
	pObj->ForceUpdateRect();
}

bool CPhysicMgr::CollideWithObject(const RECT* pObjRC, const OBJECT_LIST& pTo)
{
	RECT rc{};

	for (auto iter : pTo)
	{
		if (IntersectRect(&rc, pObjRC, &iter->GetRect()))
		{
			return true;
		}
	}
	return false;
}

bool CPhysicMgr::CollideWithObject(const RECT * pRect, float fDamage, const OBJECT_LIST & pTo)
{
	bool bCollided = false;
	RECT rc{};

	for (auto iter : pTo)
	{
		if (IntersectRect(&rc, pRect, &iter->GetRect()))
		{
			dynamic_cast<CMoveObject*>(iter)->GetDamage(fDamage);
			bCollided = true;
		}
	}

	return bCollided;
}

bool CPhysicMgr::CollideWithTile(const RECT* pObjRC, const OBJECT_LIST& pTo)
{
	RECT rc{};

	auto& pTile = dynamic_cast<CTerrain*>(pTo.front())->GetTerrain();
	for (auto iter : pTile)
	{
		if (TILE_OPTION::NO_COLLIDE == iter->byOption)
		{
			continue;
		}

		if (IntersectRect(&rc, pObjRC, &iter->tRect))
		{
			return true;
		}
	}
	return false;
}

bool CPhysicMgr::IsGround(CMoveObject* pObj)
{
	bool bIsGround = false;
	RECT rc{};
	CTerrain* pTerrain = dynamic_cast<CTerrain*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_TERRAIN)->front());
	int iIndex = pTerrain->FindTile(pObj->GetPos());

	const TILE_INFO* pDownTile = pTerrain->GetTileInfo(iIndex + CTerrain::g_TileCountX);

	if (pDownTile->byOption != NO_COLLIDE && pObj->GetRect().bottom - pDownTile->tRect.top == 0)
	{
		bIsGround = true;
	}
	return bIsGround;
}

bool CPhysicMgr::CollideWithTile(const CGameObject* pObj)
{
	RECT rc{};
	CTerrain* pTerrain = dynamic_cast<CTerrain*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_TERRAIN)->front());
	size_t iIndex = pTerrain->FindTile(pObj->GetPos());

	if (0 > iIndex || iIndex >= pTerrain->GetTerrain().size())
	{
		return false;
	}
	const TILE_INFO* pUpTile = pTerrain->GetTileInfo(iIndex - CTerrain::g_TileCountX);
	const TILE_INFO* pDownTile = pTerrain->GetTileInfo(iIndex + CTerrain::g_TileCountX);
	const TILE_INFO* pLeftTile = pTerrain->GetTileInfo(iIndex - 1);
	const TILE_INFO* pRightTile = pTerrain->GetTileInfo(iIndex + 1);

	// 아래 충돌
	if (IntersectRect(&rc, &pObj->GetRect(), &pDownTile->tRect))
	{
		switch (pDownTile->byOption)
		{
		case SQUARE_COLLIDE:
			return true;
			break;
		}
	}
	else if (IntersectRect(&rc, &pObj->GetRect(), &pUpTile->tRect))
	{
		switch (pUpTile->byOption)
		{
		case SQUARE_COLLIDE:
			return true;
			break;
		}
	}

	if (IntersectRect(&rc, &pObj->GetRect(), &pLeftTile->tRect))
	{
		switch (pLeftTile->byOption)
		{
		case SQUARE_COLLIDE:
			return true;
			break;
		}
	}
	else if (IntersectRect(&rc, &pObj->GetRect(), &pRightTile->tRect))
	{
		switch (pRightTile->byOption)
		{
		case SQUARE_COLLIDE:
			return true;
			break;
		}
	}

	return false;
}
