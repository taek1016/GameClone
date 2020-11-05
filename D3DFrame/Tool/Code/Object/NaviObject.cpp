#include "stdafx.h"
#include "NaviObject.h"

#include "Line.h"
#include "Object/ToolTerrainTex.h"
#include "Object/ToolNaviCtrl.h"
#include "Tool/TerrainTool.h"
#include "ToolTerrain.h"
#include "Transform.h"

CToolNavi::CToolNavi(LPDIRECT3DDEVICE9 pGraphicDev)
	: CNaviMesh(pGraphicDev)
	, m_iCurCnt(0)
	, m_pMesh(nullptr)
	, m_pNavi(nullptr)
	, m_pCurMadeCell(nullptr)
	, m_pTerrainTex(nullptr)
{
	::ZeroMemory(m_vPos, sizeof(Engine::_vec2) * 3);
}

CToolNavi::~CToolNavi(void)
{
	m_pMesh = nullptr;
}


void CToolNavi::KeyInput(void)
{
	CToolTerrain* pTerrain = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain");
	m_pTerrainTex = pTerrain->Get_Component<CToolTerrainTex>(L"Buffer", Engine::ID_STATIC);

	CToolNaviCtrl*	pNaviCtrl = pTerrain->Get_NaviCtrl();
#pragma region GetWorldMouse
	m_pCurMadeCell = nullptr;
	Engine::_vec3	vPos(0.f, 0.f, 0.f);

	Engine::_matrix matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

	// 네비게이션 객체 주소 찾아다 박아서 먼저 픽업
	if (m_pNavi)
	{
		Engine::_bool bIsPicked = false;
		if (DLL::pInputMgr->KeyPressing(DIK_LSHIFT))
		{
			list<Engine::_vec3> cellList;

			Engine::_vec3 vRayPos, vRayDir, vResult, vMousePos;
			Engine::_float fU, fV, fDist;
			Engine::_matrix matView, matProj, matViewInv;

			auto pGraphicDev = DLL::pGraphicDev->GetDevice();

			pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

			DLL::pCalculate->ViewPortToProj(&vMousePos);

			pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
			::D3DXMatrixInverse(&matViewInv, nullptr, &matView);

			vRayPos = Engine::_vec3(0.f, 0.f, 0.f);
			vRayDir = vMousePos - vRayPos;

			D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matViewInv);
			D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matViewInv);

			DLL::pCalculate->ProjToView(&vMousePos, &matProj, &vMousePos);
			DLL::pCalculate->ViewToWorld(&vMousePos, &matView, &vMousePos);

			auto pVector = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Navi()->Get_Vec();

			for (auto iter : *pVector)
			{
				auto pPos1 = iter->Get_Point(Engine::CCell::POINT::POINT_A);
				auto pPos2 = iter->Get_Point(Engine::CCell::POINT::POINT_B);
				auto pPos3 = iter->Get_Point(Engine::CCell::POINT::POINT_C);

				Engine::_float fLength1 = 10000000.f;
				Engine::_vec3 vPosition;

				if (D3DXIntersectTri(pPos1, pPos2, pPos3,
					&vRayPos, &vRayDir, &fU, &fV, &fDist))
				{
					vResult = vRayPos + (fDist * vRayDir);
					// 위치 1
					Engine::_float fLength2 = fabsf(D3DXVec3Length(&(*pPos1 - vResult)));

					if (fLength1 >= fLength2)
					{
						fLength1 = fLength2;
						vPosition = *pPos1;
					}

					fLength2 = fabsf(D3DXVec3Length(&(*pPos2 - vResult)));

					if (fLength1 >= fLength2)
					{
						fLength1 = fLength2;
						vPosition = *pPos2;
					}

					fLength2 = fabsf(D3DXVec3Length(&(*pPos3 - vResult)));

					if (fLength1 >= fLength2)
					{
						fLength1 = fLength2;
						vPosition = *pPos3;
					}

					cellList.push_back(vPosition);
				}
			}
			// 정렬해야 함.
			cellList.sort(NAVI_SORT(vMousePos));

			if (!cellList.empty())
			{
				bIsPicked = true;
				vPos = cellList.front();
				printf("네비게이션 메쉬 픽업 : %f %f %f\n", vPos.x, vPos.y, vPos.z);
			}
		}

		if (false == bIsPicked && !m_pNavi->PickOnNavi(&vPos))
		{
			m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
			m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

			D3DXPLANE tPlane(0.f, 1.f, 0.f, 0.f);

			DLL::pCalculate->PickingOnPlane(&vPos, &matProj, &matView, &tPlane);
			vPos.y = DLL::pToolContainer->Get_Tool<CTerrainTool>(L"TerrainTool")->Get_DefaultYValue();
			Find_NearPos(&vPos, &vPos);
		}
	}

	m_vPos[m_iCurCnt++] = vPos;
#pragma endregion

#pragma region MakeNaviMesh
	static const Engine::_int	iCellMakeCnt = 3;
	if (m_iCurCnt >= iCellMakeCnt)
	{
		if (!DLL::pCalculate->IsCWYZero(&m_vPos[0], &m_vPos[1], &m_vPos[2]))
		{
			DLL::pCalculate->Swap(&m_vPos[0], &m_vPos[2]);
		}
		m_pCurMadeCell = CNaviMesh::Add_Cell(&m_vPos[0], &m_vPos[1], &m_vPos[2]);

		for (int i = 0; i < 3; ++i)
		{
			pNaviCtrl->Add_Guide(m_pCurMadeCell->Get_Point(static_cast<Engine::CCell::POINT>(i)));
		}

#pragma region ClearLastOption
		::ZeroMemory(m_vPos, sizeof(Engine::_vec3) * 3);
		m_iCurCnt = 0;
#pragma endregion
	}
#pragma endregion
}

void CToolNavi::Set_Objects(Engine::CStaticMesh* pTex, CToolNaviCtrl* pNavi)
{
	m_pMesh = pTex;
	m_pNavi = pNavi;
}

HRESULT CToolNavi::Delete_Cell(const Engine::_ulong& dwIdx)
{
	if (-1 == dwIdx)
	{
		return E_FAIL;
	}

	Engine::Safe_Release(m_vecCell[dwIdx]);
	m_vecCell.erase(m_vecCell.begin() + dwIdx);

	return S_OK;
}

const Engine::CCell* CToolNavi::Get_Cell(const Engine::_ulong & dwIdx)
{
	Engine::CCell* pCell = nullptr;
	for (auto& iter : m_vecCell)
	{
		if (dwIdx == *iter->Get_Index())
		{
			pCell = iter;
			break;
		}
	}

	return pCell;
}

Engine::_ulong CToolNavi::Find_Index(const Engine::_vec3* pPos)
{
	Engine::_ulong dwIdx = -1;

	static const Engine::_float fNear = 0.5f;

	Engine::_vec3 vPos;
	for (auto& iter : m_vecCell)
	{
		vPos = *iter->Get_Point(Engine::CCell::POINT_A);
		if (fNear >= D3DXVec3Length(&(vPos - *pPos)))
		{
			dwIdx = *iter->Get_Index();
			break;
		}

		vPos = *iter->Get_Point(Engine::CCell::POINT_B);
		if (fNear >= D3DXVec3Length(&(vPos - *pPos)))
		{
			dwIdx = *iter->Get_Index();
			break;
		}

		vPos = *iter->Get_Point(Engine::CCell::POINT_C);
		if (fNear >= D3DXVec3Length(&(vPos - *pPos)))
		{
			dwIdx = *iter->Get_Index();
			break;
		}
	}

	return dwIdx;
}

Engine::CCell * CToolNavi::Get_MadeCell(void) const
{
	return m_pCurMadeCell;
}

void CToolNavi::Move_Pos(const Engine::_vec3 * pPos, const Engine::_vec3 * pDir)
{
	Engine::_vec3*	pMyPos;

	static const Engine::_float fNear = 0.5f;
	for (auto iter : m_vecCell)
	{
		pMyPos = iter->Get_Point(Engine::CCell::POINT::POINT_A);
		if (fNear >= D3DXVec3Length(&(*pMyPos - *pPos)))
		{
			iter->Move_Pos(Engine::CCell::POINT::POINT_A, pDir);
		}

		pMyPos = iter->Get_Point(Engine::CCell::POINT::POINT_B);
		if (fNear >= D3DXVec3Length(&(*pMyPos - *pPos)))
		{
			iter->Move_Pos(Engine::CCell::POINT::POINT_B, pDir);
		}

		pMyPos = iter->Get_Point(Engine::CCell::POINT::POINT_C);
		if (fNear >= D3DXVec3Length(&(*pMyPos - *pPos)))
		{
			iter->Move_Pos(Engine::CCell::POINT::POINT_C, pDir);
		}
	}
}

void CToolNavi::Set_Pos(const Engine::_vec3 * pPos, const Engine::_vec3 * pDir)
{
	Engine::_vec3*	pMyPos;

	static const Engine::_float fNear = 0.5f;
	for (auto iter : m_vecCell)
	{
		pMyPos = iter->Get_Point(Engine::CCell::POINT::POINT_A);
		if (fNear >= D3DXVec3Length(&(*pMyPos - *pPos)))
		{
			iter->Set_Pos(Engine::CCell::POINT::POINT_A, pDir);
		}

		pMyPos = iter->Get_Point(Engine::CCell::POINT::POINT_B);
		if (fNear >= D3DXVec3Length(&(*pMyPos - *pPos)))
		{
			iter->Set_Pos(Engine::CCell::POINT::POINT_B, pDir);
		}

		pMyPos = iter->Get_Point(Engine::CCell::POINT::POINT_C);
		if (fNear >= D3DXVec3Length(&(*pMyPos - *pPos)))
		{
			iter->Set_Pos(Engine::CCell::POINT::POINT_C, pDir);
		}
	}

}

Engine::_bool CToolNavi::collide_PointToMouse(const Engine::_vec3 * pMouseViewspace, const Engine::_vec3* pTargetPos)
{
	Engine::_bool bCollide = false;

	Engine::_vec3 vRayPos, vRayDir;
	vRayPos = { 0.f, 0.f, 0.f };
	vRayDir = *pMouseViewspace - vRayPos;

	Engine::_matrix matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, nullptr, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	D3DXVec3Normalize(&vRayDir, &vRayDir);


	Engine::_float fDistance = D3DXVec3Length(&(*pTargetPos - vRayPos));

	Engine::_vec3 vFinalPos = vRayPos + vRayDir * fDistance;
	printf("FinalPos %f %f %f\t", vFinalPos.x, vFinalPos.y, vFinalPos.z);
	printf("targetPos %f %f %f\n", pTargetPos->x, pTargetPos->y, pTargetPos->z);

	Engine::_float fFinalToSphereLength = fabsf(D3DXVec3Length(&(vFinalPos - *pTargetPos)));

	if (fFinalToSphereLength <= 1.f)
	{
		bCollide = true;
	}

	return bCollide;

}

void CToolNavi::pickUp_OnMesh(Engine::_vec3 * pPos)
{
	*pPos = { 0.f, 0.f, 0.f };

	Engine::_vec3	vMousePos;
	DLL::pCalculate->ViewPortToProj(&vMousePos);
	DLL::pCalculate->ProjToView(&vMousePos, DLL::pCameraMgr->Get_Projection(), &vMousePos);

	Engine::_float fGap = 100000.f;

	Engine::_vec3	vRayPos, vRayDir;

	vRayPos = Engine::_vec3(0.f, 0.f, 0.f);
	vRayDir = vMousePos - vRayPos;

	Engine::_matrix		matView;

	DLL::pGraphicDev->GetDevice()->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	auto pTerrain = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain");
	Engine::_matrix matTerrainToLocal = *pTerrain->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC)->Get_World();
	::D3DXMatrixInverse(&matTerrainToLocal, nullptr, &matTerrainToLocal);

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matTerrainToLocal);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matTerrainToLocal);

	struct MESH_VERTEX
	{
		Engine::_vec3 vPos, vNormal;
		Engine::_float fU, fV;
	};

	Engine::_vec3 vPos, vNormal;
	Engine::_float fDist;

	MESH_VERTEX*	pVertices;
	WORD*			pIndcies;

	LPD3DXMESH	pMesh = pTerrain->Get_Buffer()->Get_Mesh();

	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;
	LPDIRECT3DINDEXBUFFER9 pIB = nullptr;

	pMesh->GetVertexBuffer(&pVB);
	pMesh->GetIndexBuffer(&pIB);

	pVB->Lock(0, 0, (void**)&pVertices, 0);
	pIB->Lock(0, 0, (void**)&pIndcies, 0);

	DWORD dwSize = pMesh->GetNumFaces();

	Engine::_vec3 v01, v02, v03;
	Engine::_float fU, fV;

	for (DWORD i = 0; i < dwSize; ++i)
	{
		v01 = pVertices[pIndcies[3 * i + 0]].vPos;
		v02 = pVertices[pIndcies[3 * i + 1]].vPos;
		v03 = pVertices[pIndcies[3 * i + 2]].vPos;


		if (D3DXIntersectTri(&v01, &v02, &v03, &vRayPos, &vRayDir, &fU, &fV, &fDist))
		{
			*pPos = vRayPos + (vRayDir * fDist);
			break;
		}
	}

	pVB->Unlock();
	pIB->Unlock();

	Engine::Safe_Release(pVB);
	Engine::Safe_Release(pIB);

}

Engine::_ulong CToolNavi::find_Index(const Engine::_vec3 * pStart, const Engine::_vec3 * pCenter, const Engine::_vec3 * pEnd)
{
	Engine::_ulong dwIdx = -1;

	static const Engine::_float fNear = 0.5f;

	Engine::_vec3 vPos;
	Engine::_bool bIsNear[3]{ false };

	for (auto& iter : m_vecCell)
	{
		vPos = *iter->Get_Point(Engine::CCell::POINT_A);
		if (fNear >= D3DXVec3Length(&(vPos - *pStart)))
		{
			bIsNear[0] = true;
		}

		vPos = *iter->Get_Point(Engine::CCell::POINT_B);
		if (fNear >= D3DXVec3Length(&(vPos - *pCenter)))
		{
			bIsNear[1] = true;
		}

		vPos = *iter->Get_Point(Engine::CCell::POINT_C);
		if (fNear >= D3DXVec3Length(&(vPos - *pEnd)))
		{
			bIsNear[2] = true;
		}

		if (bIsNear[0] && bIsNear[1] && bIsNear[2])
		{
			dwIdx = *iter->Get_Index();
			break;
		}
		else
		{
			bIsNear[0] = false;
			bIsNear[1] = false;
			bIsNear[2] = false;
		}
	}

	return dwIdx;
}

Engine::_bool CToolNavi::Find_NearPos(Engine::_vec3* pOut, const Engine::_vec3* pIn)
{
	Engine::_vec3 vTemp;
	static const Engine::_float fNear = 1.f;
	for (auto& iter : m_vecCell)
	{
		vTemp = *iter->Get_Point(Engine::CCell::POINT_A);

		if (fNear >= D3DXVec3Length(&(vTemp - *pIn)))
		{
			*pOut = vTemp;
			return true;
		}

		vTemp = *iter->Get_Point(Engine::CCell::POINT_B);
		if (fNear >= D3DXVec3Length(&(vTemp - *pIn)))
		{
			*pOut = vTemp;
			return true;
		}

		vTemp = *iter->Get_Point(Engine::CCell::POINT_C);
		if (fNear >= D3DXVec3Length(&(vTemp - *pIn)))
		{
			*pOut = vTemp;
			return true;
		}
	}
	return false;
}

HRESULT CToolNavi::SaveNaviMesh(HANDLE hFile)
{
	if (m_vecCell.empty())
	{
		return E_FAIL;
	}

	DWORD			dwBytes = 0;
	const int iMaxBufferSize = 3;
	Engine::_vec3	vBuffer[iMaxBufferSize];

	for (auto iter : m_vecCell)
	{
		vBuffer[0] = *iter->Get_Point(Engine::CCell::POINT::POINT_A);
		vBuffer[1] = *iter->Get_Point(Engine::CCell::POINT::POINT_B);
		vBuffer[2] = *iter->Get_Point(Engine::CCell::POINT::POINT_C);

		WriteFile(hFile,
			vBuffer,
			sizeof(Engine::_vec3) * iMaxBufferSize,
			&dwBytes,
			nullptr);
	}

	return S_OK;
}

HRESULT CToolNavi::LoadNaviMesh(HANDLE hFile)
{
	if (!m_vecCell.empty())
	{
		for_each(m_vecCell.begin(), m_vecCell.end(), Engine::Safe_Release<Engine::CCell*>);
		m_vecCell.clear();
	}

	DWORD			dwBytes = 0;
	const int		iMaxBufferSize = 3;
	Engine::_vec3	vBuffer[iMaxBufferSize]{};

	while (true)
	{
		ReadFile(hFile, vBuffer, sizeof(Engine::_vec3) * iMaxBufferSize, &dwBytes, nullptr);

		if (dwBytes == 0)
		{
			break;
		}

		m_vecCell.push_back(Engine::CCell::Create(m_pGraphicDev, static_cast<Engine::_ulong>(m_vecCell.size()), &vBuffer[0], &vBuffer[1], &vBuffer[2]));
		auto pNaviCtrl = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_NaviCtrl();

		pNaviCtrl->Add_Guide(&vBuffer[0]);
		pNaviCtrl->Add_Guide(&vBuffer[1]);
		pNaviCtrl->Add_Guide(&vBuffer[2]);
	}

	return S_OK;
}

CToolNavi * CToolNavi::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CToolNavi* pInstance = new CToolNavi(pGraphicDev);

	if (FAILED(pInstance->initialize_NaviMesh()))
	{
		Engine::Safe_Release(pInstance);
	}

	return pInstance;
}