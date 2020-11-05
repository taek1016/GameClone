#include "stdafx.h"
#include "ToolTerrainTex.h"

CToolTerrainTex::CToolTerrainTex(void)
	: CVIBuffer(DLL::pGraphicDev->GetDevice())
	, m_dwCntX(0)
	, m_dwCntZ(0)
	, m_dwVtxItv(0)
	, m_fDetail(0.f)
{
}

CToolTerrainTex::~CToolTerrainTex(void)
{
}

void CToolTerrainTex::Set_UV(const Engine::_float & fDetail)
{
	m_fDetail = fDetail;

	Engine::VTXTEX*	pVertex = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertex, Engine::FVF_TEX);

	m_pVB->Unlock();
}

void CToolTerrainTex::Change_Buffer(const Engine::VTXTEX* pVtxTex, const Engine::_ulong & dwVtxCnt)
{
	Engine::VTXTEX* pVtx = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	memcpy(pVtx, pVtxTex, sizeof(Engine::VTXTEX) * dwVtxCnt);

	m_pVB->Unlock();
}

void CToolTerrainTex::KeyInput()
{
}

Engine::_bool CToolTerrainTex::PickUp_TerrainTex(Engine::_vec3 * pOut)
{
	Engine::_vec3	vMousePos;
	DLL::pCalculate->ViewPortToProj(&vMousePos);
	DLL::pCalculate->ProjToView(&vMousePos, DLL::pCameraMgr->Get_Projection(), &vMousePos);

	Engine::_vec3	vRayPos, vRayDir;

	vRayPos = Engine::_vec3(0.f, 0.f, 0.f);
	vRayDir = vMousePos - vRayPos;

	// 뷰 스페이스에서 월드 스페이스로
	Engine::_matrix		matView;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	Engine::_ulong			dwVtxIdx[3];
	Engine::_float			fU, fV, fDist;

	for (Engine::_ulong i = 0; i < m_dwCntZ - 1; ++i)
	{
		for (Engine::_ulong j = 0; j < m_dwCntX - 1; ++j)
		{
			Engine::_ulong	dwIndex = i * m_dwCntX + j;

			// 오른쪽 위
			dwVtxIdx[0] = dwIndex + m_dwCntX;
			dwVtxIdx[1] = dwIndex + m_dwCntX + 1;
			dwVtxIdx[2] = dwIndex + 1;

			if (D3DXIntersectTri(&m_pLocalPos[dwVtxIdx[1]].vPos,
				&m_pLocalPos[dwVtxIdx[2]].vPos,
				&m_pLocalPos[dwVtxIdx[0]].vPos,
				&vRayPos,
				&vRayDir, &fU, &fV, &fDist))
			{
				*pOut = vRayPos + (fDist * vRayDir);
				return true;
			}


			// 왼쪽 아래
			dwVtxIdx[0] = dwIndex + m_dwCntX;
			dwVtxIdx[1] = dwIndex + 1;
			dwVtxIdx[2] = dwIndex;

			if (D3DXIntersectTri(&m_pLocalPos[dwVtxIdx[2]].vPos,
				&m_pLocalPos[dwVtxIdx[0]].vPos,
				&m_pLocalPos[dwVtxIdx[1]].vPos,
				&vRayPos,
				&vRayDir, &fU, &fV, &fDist))
			{
				*pOut = vRayPos + (fDist * vRayDir);
				return true;
			}
		}
	}

	return false;
}

HRESULT CToolTerrainTex::initialize_TerrainTex(const Engine::_ulong & dwCntX, const Engine::_ulong & dwCntZ, const Engine::_ulong & dwVtxItv, const Engine::_float& fDetail)
{
	set_Data(dwCntX, dwCntZ, dwVtxItv);

	CVIBuffer::Initialize_Buffer();

	m_pLocalPos = new Engine::VTXTEX[m_dwVtxCnt];

	Engine::_ulong dwIndex = 0;
	Engine::_float fXPos = 0.f;
	Engine::_float fZPos = 0.f;

	Engine::_float fUSize = 0.f;
	Engine::_float fVSize = 0.f;

	for (Engine::_ulong z = 0; z < m_dwCntZ; ++z)
	{
		for (Engine::_ulong x = 0; x < m_dwCntX; ++x)
		{
			dwIndex = z * m_dwCntX + x;

			fXPos = static_cast<Engine::_float>(x * m_dwVtxItv);
			fZPos = static_cast<Engine::_float>(z * m_dwVtxItv);

			m_pLocalPos[dwIndex].vPos = Engine::_vec3(fXPos, 0.f, fZPos);
			m_pLocalPos[dwIndex].vNormal = Engine::_vec3(0.f, 0.f, 0.f);

			fUSize = static_cast<Engine::_float>(x) / (m_dwCntX - 1) * fDetail;
			fVSize = static_cast<Engine::_float>(z) / (m_dwCntZ - 1) * fDetail;

			m_pLocalPos[dwIndex].vTexUV = Engine::_vec2(fUSize, fVSize);
		}
	}

	Engine::VTXTEX*	pVtx = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	memcpy(pVtx, m_pLocalPos, sizeof(Engine::VTXTEX) * m_dwVtxCnt);

	m_pIB->Unlock();

	Engine::_ulong	dwTriCnt = 0;

	Engine::INDEX32*	pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	for (Engine::_ulong z = 0; z < m_dwCntZ - 1; ++z)
	{
		for (Engine::_ulong x = 0; x < m_dwCntX - 1; ++x)
		{
			dwIndex = z * m_dwCntX + x;

			// 오른쪽 위
			pIndex[dwTriCnt]._0 = dwIndex + m_dwCntX;
			pIndex[dwTriCnt]._1 = dwIndex + m_dwCntX + 1;
			pIndex[dwTriCnt]._2 = dwIndex + 1;
			dwTriCnt++;

			// 왼쪽 아래
			pIndex[dwTriCnt]._0 = dwIndex + m_dwCntX;
			pIndex[dwTriCnt]._1 = dwIndex + 1;
			pIndex[dwTriCnt]._2 = dwIndex;
			dwTriCnt++;
		}
	}

	m_pVB->Unlock();
	return S_OK;
}

void CToolTerrainTex::set_Data(const Engine::_ulong & dwCntX, const Engine::_ulong & dwCntZ, const Engine::_ulong & dwVtxItv)
{
	m_dwCntX	= dwCntX;
	m_dwCntZ	= dwCntZ;
	m_dwVtxItv	= dwVtxItv;

	m_dwVtxSize = sizeof(Engine::VTXTEX);
	m_dwVtxCnt	= m_dwCntX * m_dwCntZ;
	m_dwVtxFVF	= Engine::FVF_TEX;

	m_dwIdxSize = sizeof(Engine::INDEX32);
	m_dwTriCnt	= (m_dwCntX - 1) * (m_dwCntZ - 1) * 2;
	m_IdxFmt	= D3DFMT_INDEX32;
}

CToolTerrainTex * CToolTerrainTex::Create(const Engine::_ulong & dwCntX, const Engine::_ulong & dwCntZ, const Engine::_ulong & dwVtxItv, const Engine::_float& fDetail)
{
	CToolTerrainTex* pInstance = new CToolTerrainTex;

	if (FAILED(pInstance->initialize_TerrainTex(dwCntX, dwCntZ, dwVtxItv, fDetail)))
	{
		Engine::Safe_Release(pInstance);
	}

	return pInstance;
}

inline void CToolTerrainTex::Free(void)
{
	CVIBuffer::Free();

	Safe_Delete_Array(m_pLocalPos);
}
