#include "TriCol.h"

USING(Engine)

CTriCol::CTriCol()
	: CVIBuffer()
{
}

CTriCol::CTriCol(const CTriCol& rhs)
	: CVIBuffer(rhs)
{
}

CTriCol::~CTriCol(void)
{
}

HRESULT CTriCol::Initialize_Buffer(void)
{
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwVtxCnt	= 3;
	m_dwVtxFVF	= FVF_COL;
	m_dwTriCnt	= 1;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt	= D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Initialize_Buffer(), E_FAIL);

	VTXCOL*			pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPos = _vec3(0.f, 0.5f, 0.f);
	pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[1].vPos = _vec3(0.5f, -0.5f, 0.f);
	pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[2].vPos = _vec3(-0.5f, -0.5f, 0.f);
	pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	m_pVB->Unlock();

	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// 0
	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	m_pIB->Unlock();

	return S_OK;
}

CTriCol * CTriCol::Create(void)
{
	CTriCol*	pInstance = new CTriCol();

	if (FAILED(pInstance->Initialize_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CResources * CTriCol::Clone(void)
{
	return new CTriCol(*this);
}

inline void CTriCol::freeMem()
{
	CVIBuffer::freeMem();
}
