#include "Renderer.h"

#include "Engine_Entry.h"

USING(Engine)
IMPLEMENT_SINGLETON(CRenderer)

CRenderer::~CRenderer(void)
{
	freeMem();
}

void CRenderer::Add_RenderGroup(RENDERID eGroup, CGameObject * pGameObject)
{
	if (RENDER_END <= eGroup)
		return;

	m_RenderGroup[eGroup].push_back(pGameObject);
	pGameObject->AddRef();
}

void CRenderer::Render_GameObject(void)
{
	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for (auto& iter : m_RenderGroup[i])
		{
			switch (i)
			{
			case RENDER_PRIORITY:
				Ready_Priority();
				break;
			case RENDER_ALPHA:
				Ready_Alpha();
				break;

			case RENDER_UI:
				Ready_UI();
				break;

			default:
				break;
			}

			iter->Render_GameObject();
			Safe_Release(iter);

			switch (i)
			{
			case RENDER_PRIORITY:
				End_Priority();
				break;
			case RENDER_ALPHA:
				End_Alpha();
				break;

			case RENDER_UI:
				End_UI();
				break;
			}
		}

		m_RenderGroup[i].clear();
	}
}

void CRenderer::Clear_RenderGroup(void)
{
	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for_each(m_RenderGroup[i].begin(), m_RenderGroup[i].end(), CDeleteObj());
		m_RenderGroup[i].clear();
	}
}

void CRenderer::Ready_Priority(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}

void CRenderer::End_Priority(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CRenderer::Ready_UI(void)
{
	_float fNear = 0.f;
	_float fFar = 1.f;

	_matrix matProj, matView;

	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	D3DXMatrixOrthoLH(&matProj, m_fWidth, m_fHeight, fNear, fFar);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
}

void CRenderer::End_UI(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CRenderer::Ready_Alpha(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
}

void CRenderer::End_Alpha(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CRenderer::freeMem(void)
{
	Clear_RenderGroup();
}

HRESULT CRenderer::Late_Initialize()
{
	return S_OK;
}