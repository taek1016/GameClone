#include "VIBuffer.h"

Engine::CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CResources(pGraphicDev)

	, m_dwVtxSize(0)
	, m_dwVtxCnt(0)
	, m_dwVtxFVF(0)

	, m_dwTriCnt(0)
	, m_dwIdxSize(0)
{
}

Engine::CVIBuffer::CVIBuffer(const CVIBuffer& rhs)
	: CResources(rhs)
	, m_pVB(rhs.m_pVB)
	, m_pIB(rhs.m_pIB)

	, m_dwVtxSize(rhs.m_dwVtxSize)
	, m_dwVtxCnt(rhs.m_dwVtxCnt)
	, m_dwVtxFVF(rhs.m_dwVtxFVF)

	, m_dwTriCnt(rhs.m_dwTriCnt)
	, m_dwIdxSize(rhs.m_dwIdxSize)
{
	if (nullptr != m_pVB)
	{
		m_pVB->AddRef();
	}
	if (nullptr != m_pIB)
	{
		m_pIB->AddRef();
	}
}

Engine::CVIBuffer::~CVIBuffer(void)
{

}

HRESULT Engine::CVIBuffer::Initialize_Buffer(void)
{
	// 버텍스 버퍼
	FAILED_CHECK_RETURN
	(
		m_pGraphicDev->CreateVertexBuffer
		(
			m_dwVtxSize * m_dwVtxCnt, 0,
			m_dwVtxFVF, D3DPOOL_MANAGED,
			&m_pVB, NULL
		),
		E_FAIL
	);

	// 인덱스 버퍼
	FAILED_CHECK_RETURN
	(
		m_pGraphicDev->CreateIndexBuffer
		(
			m_dwIdxSize * m_dwTriCnt, 0,
			m_IdxFmt, D3DPOOL_MANAGED,
			&m_pIB, NULL
		),
		E_FAIL
	);

	return S_OK;
}

void Engine::CVIBuffer::Render_Buffer(LPDIRECT3DVERTEXBUFFER9 pVB)
{
	if (pVB != nullptr)
	{
		m_pGraphicDev->SetStreamSource(0, pVB, 0, m_dwVtxSize);
	}
	else
	{
		m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	}

	m_pGraphicDev->SetFVF(m_dwVtxFVF);
	m_pGraphicDev->SetIndices(m_pIB);

	m_pGraphicDev->DrawIndexedPrimitive
	(
		D3DPT_TRIANGLELIST, 0, 0,
		m_dwVtxCnt, 0, m_dwTriCnt
	);
}

void Engine::CVIBuffer::Free(void)
{
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);

	CResources::Free();
}