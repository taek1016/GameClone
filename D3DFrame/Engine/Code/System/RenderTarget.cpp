#include "RenderTarget.h"

USING(Engine)

Engine::CRenderTarget::CRenderTarget(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_pTargetTexture(nullptr)
	, m_pTargetSurface(nullptr)
	, m_pOldTargetSurface(nullptr)
	, m_pVB(nullptr)
	, m_pIB(nullptr)
{
	m_pGraphicDev->AddRef();
}

Engine::CRenderTarget::~CRenderTarget(void)
{

}

HRESULT Engine::CRenderTarget::Ready_RenderTarget(const _uint& iWidth, 
													const _uint& iHeight,
													D3DFORMAT Format, 
													D3DXCOLOR Color)
{
	FAILED_CHECK_RETURN(D3DXCreateTexture(m_pGraphicDev, 
											iWidth, 
											iHeight, 
											1, 
											D3DUSAGE_RENDERTARGET, 
											Format, 
											D3DPOOL_DEFAULT, // ���� Ÿ�� ���� �� �ݵ�� default�� ����� �Ѵ�.
											&m_pTargetTexture), 
											E_FAIL);

	// �ؽ��ķκ��� ����Ÿ�� ������ �����Ͽ� 2���ڿ��� �Ѱ��ش�.
	m_pTargetTexture->GetSurfaceLevel(0, &m_pTargetSurface); // 1���� : miplevel�� ���� �� ������� ���, �� ��°�� ����� ���ΰ�. 
	Safe_Release(m_pTargetTexture);

	m_ClearColor = Color;

	return S_OK;
}

void Engine::CRenderTarget::SetUp_RenderTarget(const _uint& iIndex)
{
	m_pGraphicDev->GetRenderTarget(iIndex, &m_pOldTargetSurface);

	// ��ġ�� ��ũ�Ǿ� �ִ� ���� ����Ÿ�� ������ ������ ���ο� ����Ÿ�� ������ ��ũ��Ű�� ��Ȳ
	m_pGraphicDev->SetRenderTarget(iIndex, m_pTargetSurface);
}

void CRenderTarget::Release_OnGraphicDev(const _uint & iIndex)		// ������ �����ϴ� ���� Ÿ�� ���۵��� m_pTargetSurface�� ������ ����Ǿ� �ְ� m_pOldTargetSurface���� ����۰� �����Ǿ� �ִ�. 
{
	m_pGraphicDev->SetRenderTarget(iIndex, m_pOldTargetSurface);
	Safe_Release(m_pOldTargetSurface);
}



void CRenderTarget::Clear_RenderTarget(void)	// ���� ���ϴ� Ÿ�� ���۸� ����� ���� �����ϴ� �Լ�
{
	m_pGraphicDev->GetRenderTarget(0, &m_pOldTargetSurface);
	m_pGraphicDev->SetRenderTarget(0, m_pTargetSurface);

	m_pGraphicDev->Clear(0, NULL, D3DCLEAR_TARGET, m_ClearColor, 1.f, 0);

	m_pGraphicDev->SetRenderTarget(0, m_pOldTargetSurface);
	Safe_Release(m_pOldTargetSurface);
}


Engine::CRenderTarget* Engine::CRenderTarget::Create(LPDIRECT3DDEVICE9 pGraphicDev,
													const _uint& iWidth, 
													const _uint& iHeight,
													D3DFORMAT Format,
													D3DXCOLOR Color)
{
	CRenderTarget*	pInstance = new CRenderTarget(pGraphicDev);

	if (FAILED(pInstance->Ready_RenderTarget(iWidth, iHeight, Format, Color)))
		Safe_Release(pInstance);

	return pInstance;
}

void Engine::CRenderTarget::Free(void)
{
	Safe_Release(m_pIB);
	Safe_Release(m_pVB);

	Safe_Release(m_pTargetTexture);
	Safe_Release(m_pOldTargetSurface);
	Safe_Release(m_pGraphicDev);
}

HRESULT CRenderTarget::Ready_DebugBuffer(const _float & fX, const _float & fY, const _float & fSizeX, const _float & fSizeY)
{
	FAILED_CHECK_RETURN(m_pGraphicDev->CreateVertexBuffer(sizeof(VTXSCREEN) * 4,
		0,
		FVF_SCREEN,
		D3DPOOL_MANAGED,
		&m_pVB,
		NULL),
		E_FAIL);


	FAILED_CHECK_RETURN(m_pGraphicDev->CreateIndexBuffer(sizeof(INDEX16) * 2,
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIB,
		NULL),
		E_FAIL);

	VTXSCREEN*			pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPos = _vec4(fX, fY, 0.f, 1.f);
	pVertex[0].vTexUV = _vec2(0.f, 0.f);

	pVertex[1].vPos = _vec4(fX + fSizeX, fY, 0.f, 1.f);
	pVertex[1].vTexUV = _vec2(1.f, 0.f);

	pVertex[2].vPos = _vec4(fX + fSizeX, fY + fSizeY, 0.f, 1.f);
	pVertex[2].vTexUV = _vec2(1.f, 1.f);

	pVertex[3].vPos = _vec4(fX, fY + fSizeY, 0.f, 1.f);
	pVertex[3].vTexUV = _vec2(0.f, 1.f);

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

void CRenderTarget::Render_DebugBuffer(void)
{
	m_pGraphicDev->SetTexture(0, m_pTargetTexture);

	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, sizeof(VTXSCREEN));
	m_pGraphicDev->SetFVF(FVF_SCREEN);
	m_pGraphicDev->SetIndices(m_pIB);
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void Engine::CRenderTarget::SetUp_OnShader(LPD3DXEFFECT& pEffect, const char* pContantName)
{
	pEffect->SetTexture(pContantName, m_pTargetTexture);
}
