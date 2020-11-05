#include "NaviMesh.h"

USING(Engine)

Engine::CNaviMesh::CNaviMesh(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMesh(pGraphicDev)
	, m_dwIndex(0)
{

}

Engine::CNaviMesh::CNaviMesh(const CNaviMesh& rhs)
	: CMesh(rhs)
	, m_vecCell(rhs.m_vecCell)
	, m_dwIndex(rhs.m_dwIndex)
{
	for (auto& iter : m_vecCell)
		iter->AddRef();
}

Engine::CNaviMesh::~CNaviMesh(void)
{

}

HRESULT Engine::CNaviMesh::initialize_NaviMesh(void)
{
	return S_OK;
}

CCell* CNaviMesh::Add_Cell(const _vec3* pStart, const _vec3* pCenter, const _vec3* pEnd)
{
	CCell* pCell = nullptr;

	static _int iCount = 0;
	pCell = CCell::Create(m_pGraphicDev, iCount++, pStart, pCenter, pEnd);

	m_vecCell.push_back(pCell);

	return pCell;
}

void CNaviMesh::Render_NaviMesh(void)
{
	for (auto& iter : m_vecCell)
	{
		iter->Render_Cell();
	}
}

_vec3 CNaviMesh::Move_OnNaviMesh(const _vec3 * pTargetPos, const _vec3 * pTargetDir)
{
	_vec3	vEndPos = *pTargetPos + *pTargetDir;

	D3DXPLANE tPlane;
	D3DXPlaneFromPoints(&tPlane, m_vecCell[m_dwIndex]->Get_Point(CCell::POINT_A), m_vecCell[m_dwIndex]->Get_Point(CCell::POINT_B), m_vecCell[m_dwIndex]->Get_Point(CCell::POINT_C));

	_float fYPos = -(tPlane.a * vEndPos.x + tPlane.c * vEndPos.z + tPlane.d) / tPlane.b;

	vEndPos.y = fYPos;

	if (CCell::COMPARE_MOVE == m_vecCell[m_dwIndex]->Compare(&vEndPos, m_dwIndex))
	{
		return vEndPos;
	}

	else if (CCell::COMPARE_STOP == m_vecCell[m_dwIndex]->Compare(&vEndPos, m_dwIndex))
	{
		return *pTargetPos;
	}

	return *pTargetPos;
}

HRESULT Engine::CNaviMesh::Link_Cell(void)
{
	_ulong	dwSize = static_cast<_ulong>(m_vecCell.size());

	for (_ulong i = 0; i < dwSize; ++i)
	{
		for (_ulong j = 0; j < dwSize; ++j)
		{
			if (i == j)
				continue;

			if (nullptr == m_vecCell[i]->Get_Neighbor(CCell::NEIGHBOR_AB) &&
				true == m_vecCell[j]->Compare_Point(m_vecCell[i]->Get_Point(CCell::POINT_A),
					m_vecCell[i]->Get_Point(CCell::POINT_B),
					m_vecCell[i]))
			{
				m_vecCell[i]->Set_Neighbor(CCell::NEIGHBOR_AB, m_vecCell[j]);
				continue;
			}

			if (nullptr == m_vecCell[i]->Get_Neighbor(CCell::NEIGHBOR_BC) &&
				true == m_vecCell[j]->Compare_Point(m_vecCell[i]->Get_Point(CCell::POINT_B),
					m_vecCell[i]->Get_Point(CCell::POINT_C),
					m_vecCell[i]))
			{
				m_vecCell[i]->Set_Neighbor(CCell::NEIGHBOR_BC, m_vecCell[j]);
				continue;
			}


			if (nullptr == m_vecCell[i]->Get_Neighbor(CCell::NEIGHBOR_CA) &&
				true == m_vecCell[j]->Compare_Point(m_vecCell[i]->Get_Point(CCell::POINT_C),
					m_vecCell[i]->Get_Point(CCell::POINT_A),
					m_vecCell[i]))
			{
				m_vecCell[i]->Set_Neighbor(CCell::NEIGHBOR_CA, m_vecCell[j]);
				continue;
			}
		}
	}

	return S_OK;
}

const vector<CCell*>* CNaviMesh::Get_Vec(void) const
{
	return &m_vecCell;
}

Engine::CNaviMesh* Engine::CNaviMesh::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNaviMesh*	pInstance = new CNaviMesh(pGraphicDev);

	if (FAILED(pInstance->initialize_NaviMesh()))
		Safe_Release(pInstance);

	return pInstance;
}

Engine::CResources* Engine::CNaviMesh::Clone(void)
{
	return new CNaviMesh(*this);
}

void Engine::CNaviMesh::Free(void)
{
	for_each(m_vecCell.begin(), m_vecCell.end(), CDeleteObj());
	m_vecCell.clear();

	CMesh::Free();
}