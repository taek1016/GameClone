#include "stdafx.h"
#include "ToolLine.h"

CToolLine::CToolLine(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine)
	: m_pLine(pLine)
	, m_pGraphicDev(pGraphicDev)
	, m_tColor(0.f, 1.f, 0.f, 1.f)
{
	m_pLine->AddRef();
	m_pGraphicDev->AddRef();
}

CToolLine::~CToolLine(void)
{
	Engine::Safe_Release(m_pGraphicDev);
	Engine::Safe_Release(m_pLine);
}

void CToolLine::set_Vec2ToVec3(const LINE_POS ePos, const Engine::_vec2 * pPos)
{
	m_vPos[ePos].x = pPos->x;
	m_vPos[ePos].y = 0.f;
	m_vPos[ePos].z = pPos->y;
}

HRESULT CToolLine::initialize_Line(const Engine::_vec2* pStart, const Engine::_vec2* pEnd)
{
	set_Vec2ToVec3(LINE_START, pStart);
	set_Vec2ToVec3(LINE_DEST, pEnd);

	return S_OK;
}

void CToolLine::Update(const Engine::_float & fTimeDelta)
{
	// 충돌시 빨간색
}

void CToolLine::Render(void)
{
	Engine::_matrix matView, matProj, matViewProj;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	
	matViewProj = matView * matProj;

	m_pLine->DrawTransform(m_vPos, 2, &matViewProj, m_tColor);
}

const Engine::_vec3 CToolLine::Get_Line(void)
{
	return m_vPos[LINE_DEST] - m_vPos[LINE_START];
}

CToolLine* CToolLine::Create(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine, const Engine::_vec2* pStart, const Engine::_vec2* pEnd)
{
	CToolLine* pInstance = new CToolLine(pGraphicDev, pLine);

	if (FAILED(pInstance->initialize_Line(pStart, pEnd)))
	{
		Engine::Safe_Delete(pInstance);
	}

	return pInstance;
}
