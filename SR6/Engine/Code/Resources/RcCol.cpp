#include "RcCol.h"

USING(Engine)

CRcCol::CRcCol(void)
	: CVIBuffer()
{
}

CRcCol::CRcCol(const CRcCol& rhs)
	: CVIBuffer(rhs)
{
}

CRcCol::~CRcCol(void)
{
}

HRESULT CRcCol::Initialize_Buffer(void)
{
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwVtxCnt = 4;
	m_dwVtxFVF = FVF_COL;
	m_dwTriCnt = 2;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Initialize_Buffer(), E_FAIL);

	VTXCOL*			pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);	

	pVertex[0].vPos = _vec3(-0.5f, 0.5f, 0.f);
	pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[1].vPos = _vec3(0.5f, 0.5f, 0.f);
	pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[2].vPos = _vec3(0.5f, -0.5f, 0.f);
	pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[3].vPos = _vec3(-0.5f, -0.5f, 0.f);
	pVertex[3].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	m_pVB->Unlock();

	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// 0
	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	// 1
	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIB->Unlock();
	return S_OK;
}

CRcCol* CRcCol::Create(void)
{
	CRcCol* pInstance = new CRcCol();

	if (FAILED(pInstance->Initialize_Buffer()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CResources * CRcCol::Clone(void)
{
	return new CRcCol(*this);
}
