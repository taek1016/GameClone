#include "stdafx.h"
#include "PickMgr.h"

#include "Objects/Terrain.h"

USING(Engine)
IMPLEMENT_SINGLETON(CPickMgr)

CPickMgr::CPickMgr(void)
{
}

CPickMgr::~CPickMgr(void)
{
}

void CPickMgr::Update_Debug(void)
{
	if (DLL::pInputMgr->KeyDown(DIK_F1))
	{
		g_bActCol = !g_bActCol;
	}
	if (DLL::pInputMgr->KeyDown(DIK_F2))
	{
		g_bAttackCol = !g_bAttackCol;
	}
	if (DLL::pInputMgr->KeyDown(DIK_F3))
	{
		g_bCollider = !g_bCollider;
	}
	if (DLL::pInputMgr->KeyDown(DIK_F4))
	{
		g_bRenderDebug = !g_bRenderDebug;
	}
	if (DLL::pInputMgr->KeyDown(DIK_F5))
	{
		g_bNaviRender = !g_bNaviRender;
	}
}

_vec3 CPickMgr::SetUp_OnTerrain(_ulong& dwIndex, const _vec3* pPos, const _vec3* pDir)
{
	CTerrain* pTerrain = dynamic_cast<CTerrain*>(DLL::pObjMgr->Get_ObjList(L"Terrain")->front());
	CNaviMesh* pNaviMesh = dynamic_cast<CNaviMesh*>(pTerrain->Get_Component<CNaviMesh>(L"NaviMesh", ID_STATIC));

	pNaviMesh->Set_Index(dwIndex);
	_vec3 vPos = pNaviMesh->Move_OnNaviMesh(pPos, pDir);

	if (D3DXVec3Length(&(vPos - _vec3(0.f, 0.f, 0.f))) < FLT_EPSILON)
	{
		dwIndex = pTerrain->Find_CellIndex(pPos);
	}
	else
	{
		dwIndex = pNaviMesh->Get_Index();
	}
	return vPos;
}

Engine::_float CPickMgr::Get_CertainTerrainHeight(const _ulong dwIdx, const Engine::_vec3 * pPos)
{
	CTerrain* pTerrain = dynamic_cast<CTerrain*>(DLL::pObjMgr->Get_ObjList(L"Terrain")->front());
	CNaviMesh* pNaviMesh = dynamic_cast<CNaviMesh*>(pTerrain->Get_Component<CNaviMesh>(L"NaviMesh", ID_STATIC));

	auto pCell = pNaviMesh->Get_Vec();

	auto pPos1 = pCell->at(dwIdx)->Get_Point(CCell::POINT_A);
	auto pPos2 = pCell->at(dwIdx)->Get_Point(CCell::POINT_B);
	auto pPos3 = pCell->at(dwIdx)->Get_Point(CCell::POINT_C);

	_float fU, fV, fDist;

	_vec3 vDown(0.f, -1.f, 0.f);
	if (D3DXIntersectTri(pPos1, pPos2, pPos3, pPos, &vDown, &fU, &fV, &fDist))
	{
		_vec3 vResult = *pPos + vDown * fDist;
		return vResult.y;
	}
	
	vDown.y = 1.f;
	if (D3DXIntersectTri(pPos1, pPos2, pPos3, pPos, &vDown, &fU, &fV, &fDist))
	{
		_vec3 vResult = *pPos + vDown * fDist;
		return vResult.y;
	}

	return 0.f;
}

Engine::_float CPickMgr::Get_TerrainHeight(const Engine::_vec3 * pPos)
{
	CTerrain* pTerrain = dynamic_cast<CTerrain*>(DLL::pObjMgr->Get_ObjList(L"Terrain")->front());
	CNaviMesh* pNaviMesh = dynamic_cast<CNaviMesh*>(pTerrain->Get_Component<CNaviMesh>(L"NaviMesh", ID_STATIC));

	_ulong dwIndex = Get_Index(pPos);

	auto pCell = pNaviMesh->Get_Vec();

	auto pPos1 = pCell->at(dwIndex)->Get_Point(CCell::POINT_A);
	auto pPos2 = pCell->at(dwIndex)->Get_Point(CCell::POINT_B);
	auto pPos3 = pCell->at(dwIndex)->Get_Point(CCell::POINT_C);

	_float fU, fV, fDist;

	_vec3 vDown(0.f, -1.f, 0.f);
	if (D3DXIntersectTri(pPos1, pPos2, pPos3, pPos, &vDown, &fU, &fV, &fDist))
	{
		_vec3 vResult = *pPos + vDown * fDist;
		return vResult.y;
	}

	return 0.f;
}

Engine::_float CPickMgr::Get_ReverseTerrainHeight(const Engine::_vec3 * pPos)
{
	CTerrain* pTerrain = dynamic_cast<CTerrain*>(DLL::pObjMgr->Get_ObjList(L"Terrain")->front());
	CNaviMesh* pNaviMesh = dynamic_cast<CNaviMesh*>(pTerrain->Get_Component<CNaviMesh>(L"NaviMesh", ID_STATIC));

	_ulong dwIndex = Get_Index(pPos);

	auto pCell = pNaviMesh->Get_Vec();

	auto pPos1 = pCell->at(dwIndex)->Get_Point(CCell::POINT_A);
	auto pPos2 = pCell->at(dwIndex)->Get_Point(CCell::POINT_B);
	auto pPos3 = pCell->at(dwIndex)->Get_Point(CCell::POINT_C);

	_float fU, fV, fDist;

	_vec3 vDown(0.f, 1.f, 0.f);
	if (D3DXIntersectTri(pPos1, pPos2, pPos3, pPos, &vDown, &fU, &fV, &fDist))
	{
		_vec3 vResult = *pPos + vDown * fDist;
		return vResult.y;
	}

	return 0.f;
}

Engine::_ulong CPickMgr::Get_Index(const Engine::_vec3 * pPos)
{
	CTerrain* pTerrain = dynamic_cast<CTerrain*>(DLL::pObjMgr->Get_ObjList(L"Terrain")->front());

	return pTerrain->Find_CellIndex(pPos);
}

Engine::_bool CPickMgr::Select_Mouse(const Engine::_vec3* pMouseWorldPos, const Engine::CSphereCollider * pSphere)
{
	LPDIRECT3DVERTEXBUFFER9	pVB = nullptr;
	LPDIRECT3DINDEXBUFFER9	pIB = nullptr;

	D3DVIEWPORT9 tViewPort;
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();
	pGraphicDev->GetViewport(&tViewPort);

	_vec3 vRayPos, vRayDir;

	_matrix matView, matProj;
	_float fScreenWidth, fScreenHeight;

	DLL::pGraphicDev->GetScreenData(&fScreenWidth, &fScreenHeight);
	pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	static const _float fProjectionFull = 2.f;
	static const _float fProjectionHalf = 2.f;
	vRayDir.x = ((fProjectionFull * fScreenWidth) / tViewPort.Width - fProjectionHalf) / matProj._11;
	vRayDir.y = ((-fProjectionFull * fScreenWidth) / tViewPort.Width + fProjectionHalf) / matProj._22;
	vRayDir.z = 1.f;

	pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, nullptr, &matView);

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);
	D3DXVec3Normalize(&vRayDir, &vRayDir);

	return Engine::_bool();
}

inline void CPickMgr::Free(void)
{
}
