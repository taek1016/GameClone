#include "stdafx.h"
#include "ToolRenderer.h"

#include "GameObject.h"

IMPLEMENT_SINGLETON(CToolRenderer)

CToolRenderer::CToolRenderer(void)
	: m_wCurRenderName(L"AllSolid")
	, m_pGraphicDev(nullptr)
{
}

CToolRenderer::~CToolRenderer(void)
{
	Free();
}

void CToolRenderer::Initialize_Renderer(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
}

void CToolRenderer::Render(void)
{
	if (L"AllSolid" == m_wCurRenderName)
	{
		CToolRenderer::render_All();
	}
	else if (L"AllWireFrame" == m_wCurRenderName)
	{
		CToolRenderer::render_AllCertainSolid();
	}
	else
	{
		CToolRenderer::render_CertainName();
	}
}

void CToolRenderer::Set_RenderName(const Engine::_tchar* pKey)
{
	m_wCurRenderName = pKey;
}

void CToolRenderer::Set_SolidName(const Engine::_tchar* pKey)
{
	m_wCurSolidName = pKey;
}

void CToolRenderer::Add_RenderObj(const Engine::_tchar * pKey, Engine::CGameObject * pObj)
{
	auto iter = find_if(m_mapRender.begin(), m_mapRender.end(), Engine::CTag_Finder(pKey));

	if (m_mapRender.end() == iter)
	{
		list<Engine::CGameObject*>* pList = nullptr;
		pList = new list<Engine::CGameObject*>;

		pList->push_back(pObj);

		m_mapRender.insert(make_pair(pKey, pList));
	}
	else
	{
		m_mapRender[pKey]->push_back(pObj);
	}
}

void CToolRenderer::render_All(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	for (auto iterList : m_mapRender)
	{
		for (auto iter : (*iterList.second))
		{
			iter->Render_GameObject();
		}
	}
}

void CToolRenderer::render_CertainName(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	for (auto iter : (*m_mapRender[m_wCurRenderName.c_str()]))
	{
		iter->Render_GameObject();
	}
}

void CToolRenderer::render_AllCertainSolid(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	for (auto iterList : m_mapRender)
	{
		for (auto iter : (*iterList.second))
		{
			if (iter->Get_Name() == m_wCurSolidName)
			{
				m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}
			iter->Render_GameObject();

			if (iter->Get_Name() == m_wCurSolidName)
			{
				m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			}
		}
	}
}

inline void CToolRenderer::Free(void)
{
	for (auto iter : m_mapRender)
	{
		iter.second->clear();
		Engine::Safe_Delete(iter.second);
	}
	m_mapRender.clear();
}
