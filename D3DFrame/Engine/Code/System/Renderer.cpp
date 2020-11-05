#include "Renderer.h"

#include "GameObject.h"
#include "Shader.h"

#include "RenderTargetMgr.h"
#include "LightMgr.h"
#include "ShaderMgr.h"
USING(Engine)

IMPLEMENT_SINGLETON(CRenderer)

CRenderer::CRenderer(void)
	: m_pRenderTargetMgr(nullptr)
	, m_pVB(nullptr)
	, m_pIB(nullptr)
	, m_pLightMgr(nullptr)
	, m_pShaderMgr(nullptr)
{
}

CRenderer::~CRenderer(void)
{
	Free();
}

HRESULT CRenderer::Initialize_Renderer(CRenderTargetMgr* pRenderTargetMgr, CLightMgr* pLightMgr, CShaderMgr* pShaderMgr, LPDIRECT3DDEVICE9 & pGraphicDev)
{
	FAILED_CHECK_RETURN(pGraphicDev->CreateVertexBuffer(sizeof(VTXSCREEN) * 4,
		0,
		FVF_SCREEN,
		D3DPOOL_MANAGED,
		&m_pVB,
		NULL),
		E_FAIL);


	FAILED_CHECK_RETURN(pGraphicDev->CreateIndexBuffer(sizeof(INDEX16) * 2,	// 생성할 인덱스 버퍼의 크기
		0,					// 버퍼의 종류(숫자가 0인 경우 정적 버퍼)
		D3DFMT_INDEX16,			// 생성하는 인덱스의 속성값
		D3DPOOL_MANAGED,	// 메모리 풀의 설정
		&m_pIB,
		NULL),
		E_FAIL);

	D3DVIEWPORT9		ViewPort;
	pGraphicDev->GetViewport(&ViewPort);

	VTXSCREEN*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPos = _vec4(0.f, 0.f, 0.f, 1.f);
	pVertex[0].vTexUV = _vec2(0.f, 0.f);

	pVertex[1].vPos = _vec4(_float(ViewPort.Width), 0.f, 0.f, 1.f);
	pVertex[1].vTexUV = _vec2(1.f, 0.f);

	pVertex[2].vPos = _vec4(_float(ViewPort.Width), _float(ViewPort.Height), 0.f, 1.f);
	pVertex[2].vTexUV = _vec2(1.f, 1.f);

	pVertex[3].vPos = _vec4(0.f, _float(ViewPort.Height), 0.f, 1.f);
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

	m_pLightMgr = pLightMgr;
	m_pLightMgr->AddRef();
		
	m_pRenderTargetMgr = pRenderTargetMgr;
	m_pRenderTargetMgr->AddRef();

	m_pShaderMgr = pShaderMgr;
	m_pShaderMgr->AddRef();

	return S_OK;
}

void CRenderer::Add_RenderGroup(RENDERID eGroup, CGameObject * pGameObject)
{
	if (RENDER_END <= eGroup)
		return;

	m_RenderGroup[eGroup].push_back(pGameObject);

	pGameObject->AddRef();
}

void CRenderer::Render_GameObject(const _bool& bRenderDebug, LPDIRECT3DDEVICE9 & pGraphicDev)
{
	render_Priority(pGraphicDev);
	render_PreUI(pGraphicDev);

	render_Defferd(pGraphicDev);
	render_LightAcc(pGraphicDev);

	render_Blend(pGraphicDev);

	render_Alpha(pGraphicDev);
	render_UI(pGraphicDev);

	if (true == bRenderDebug)
	{
		m_pRenderTargetMgr->Render_DebugBuffer(L"MRT_Defferd");
		m_pRenderTargetMgr->Render_DebugBuffer(L"MRT_LightAcc");
	}

	Clear_RenderGroup();
}

void CRenderer::render_Priority(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (auto& iter : m_RenderGroup[RENDER_PRIORITY])
		iter->Render_GameObject();

	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void CRenderer::render_PreUI(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	for (auto& iter : m_RenderGroup[RENDER_PREUI])
		iter->Render_GameObject();

	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void CRenderer::render_NonAlpha(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	for (auto& iter : m_RenderGroup[RENDER_NONALPHA])
		iter->Render_GameObject();
}

_bool	Compare_Z(CGameObject* pDest, CGameObject* pSour)
{
	return pDest->Get_ViewZ() > pSour->Get_ViewZ();
}

void CRenderer::render_Alpha(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_RenderGroup[RENDER_ALPHA].sort(Compare_Z);

	for (auto& iter : m_RenderGroup[RENDER_ALPHA])
		iter->Render_GameObject();

	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void CRenderer::render_UI(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	_float fNear = 0.f;
	_float fFar = 1.f;
	
	_matrix matProj, matView;
	_matrix matOldProj, matOldView;

	pGraphicDev->GetTransform(D3DTS_VIEW, &matOldView);
	pGraphicDev->GetTransform(D3DTS_PROJECTION, &matOldProj);

	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	D3DXMatrixOrthoLH(&matProj, m_fWidth, m_fHeight, fNear, fFar);
	
	pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
	
	pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	for (auto& iter : m_RenderGroup[RENDER_UI])
		iter->Render_GameObject();

	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);

	pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	pGraphicDev->SetTransform(D3DTS_VIEW, &matOldView);
	pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOldProj);

}

void Engine::CRenderer::render_Blend(LPDIRECT3DDEVICE9& pGraphicDev)
{
	CShader*	pShader = dynamic_cast<Engine::CShader*>(m_pShaderMgr->Clone_Shader(L"Shader_Blend"));
	NULL_CHECK(pShader);

	LPD3DXEFFECT pEffect = pShader->Get_EffectHandle();
	pEffect->AddRef();

	m_pRenderTargetMgr->SetUp_OnShader(pEffect, L"Target_Albedo", "g_AlbedoTexture");
	m_pRenderTargetMgr->SetUp_OnShader(pEffect, L"Target_Light", "g_LightTexture");
	m_pRenderTargetMgr->SetUp_OnShader(pEffect, L"Target_Specular", "g_SpecularTexture");

	pEffect->Begin(NULL, 0);
	pEffect->BeginPass(0);

	pGraphicDev->SetStreamSource(0, m_pVB, 0, sizeof(VTXSCREEN));
	pGraphicDev->SetFVF(FVF_SCREEN);
	pGraphicDev->SetIndices(m_pIB);
	pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	pEffect->EndPass();
	pEffect->End();


	Safe_Release(pEffect);
	Safe_Release(pShader);
}

void Engine::CRenderer::render_LightAcc(LPDIRECT3DDEVICE9& pGraphicDev)
{
	m_pRenderTargetMgr->Begin_MRT(L"MRT_LightAcc");

	CShader*	pShader = dynamic_cast<Engine::CShader*>(m_pShaderMgr->Clone_Shader(L"Shader_Light"));
	NULL_CHECK(pShader);

	LPD3DXEFFECT pEffect = pShader->Get_EffectHandle();
	pEffect->AddRef();

	m_pRenderTargetMgr->SetUp_OnShader(pEffect, L"Target_Normal", "g_NormalTexture");
	m_pRenderTargetMgr->SetUp_OnShader(pEffect, L"Target_Depth", "g_DepthTexture");

	pEffect->Begin(NULL, 0);

	m_pLightMgr->Render_Light(pEffect);

	pEffect->End();

	m_pRenderTargetMgr->End_MRT(L"MRT_LightAcc");

	Safe_Release(pEffect);
	Safe_Release(pShader);
}

void Engine::CRenderer::render_Defferd(LPDIRECT3DDEVICE9& pGraphicDev)
{
	m_pRenderTargetMgr->Begin_MRT(L"MRT_Defferd");

	render_NonAlpha(pGraphicDev);

	m_pRenderTargetMgr->End_MRT(L"MRT_Defferd");
}

//void CRenderer::Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev)
//{
//	for (_uint i = 0; i < RENDER_END; ++i)
//	{
//		for (auto& iter : m_RenderGroup[i])
//		{
//			switch (i)
//			{
//			//case RENDER_PRIORITY:
//			//	ready_Priority();
//			//	break;
//			//case RENDER_ALPHA:
//			//	ready_Alpha();
//			//	break;
//
//			case RENDER_UI:
//				ready_UI();
//				break;
//
//			default:
//				break;
//			}
//
//			iter->Render_GameObject();
//			Safe_Release(iter);
//
//			switch (i)
//			{
//			//case RENDER_PRIORITY:
//			//	end_Priority();
//			//	break;
//			//case RENDER_ALPHA:
//			//	end_Alpha();
//			//	break;
//
//			case RENDER_UI:
//				end_UI();
//				break;
//			}
//		}
//
//		m_RenderGroup[i].clear();
//	}
//}
//void CRenderer::ready_Priority(void)
//{
//	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
//	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
//	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
//}
//
//void CRenderer::end_Priority(void)
//{
//	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
//	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
//}
//
//void CRenderer::ready_UI(void)
//{
//	_float fNear = 0.f;
//	_float fFar = 1.f;
//
//	_matrix matProj, matView;
//
//	D3DXMatrixIdentity(&matView);
//	D3DXMatrixIdentity(&matProj);
//	D3DXMatrixOrthoLH(&matProj, m_fWidth, m_fHeight, fNear, fFar);
//
//	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
//	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
//
//	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
//
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
//
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
//}
//
//void CRenderer::end_UI(void)
//{
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
//
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
//	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
//}
//
//void CRenderer::ready_Alpha(void)
//{
//	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
//
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
//
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
//}
//
//void CRenderer::end_Alpha(void)
//{
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
//
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
//	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
//}

void CRenderer::Clear_RenderGroup(void)
{
	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for_each(m_RenderGroup[i].begin(), m_RenderGroup[i].end(), CDeleteObj());
		m_RenderGroup[i].clear();
	}
}

void CRenderer::Free(void)
{
	Clear_RenderGroup();

	Safe_Release(m_pRenderTargetMgr);
	Safe_Release(m_pLightMgr);
	Safe_Release(m_pShaderMgr);
}
