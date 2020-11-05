#include "stdafx.h"
#include "GuideLine.h"

#include "Transform.h"

USING(Engine)
CGuideLine::CGuideLine(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine, const Engine::_float & fLineLength)
	: CToolGameObject(pGraphicDev)
	, m_pLine(pLine)
{
	m_pLine->AddRef();
	Engine::_vec3 vGuideLine[3];
	// 0Àº Right
	vGuideLine[0] = { fLineLength, 0.f, 0.f };
	m_tColor[0] = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	// 1Àº Up
	vGuideLine[1] = { 0.f, fLineLength, 0.f };
	m_tColor[1] = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	// 2´Â Look
	vGuideLine[2] = { 0.f, 0.f, fLineLength };
	m_tColor[2] = D3DXCOLOR(0.f, 1.f, 1.f, 1.f);

	Engine::_vec3 vZeroPoint(0.f, 0.f, 0.f);


	for (int i = 0; i < 3; ++i)
	{
		m_vLine[i][0] = vZeroPoint;
		m_vLine[i][1] = vGuideLine[i];
	}
}

CGuideLine::~CGuideLine(void)
{
}

HRESULT CGuideLine::Initialize_GameObject(void)
{
	return S_OK;
}

HRESULT CGuideLine::Late_Initialize(void)
{
	return S_OK;
}

Engine::_int CGuideLine::Update_GameObject(const Engine::_float & fTimeDelta)
{
	return 0;
}

void CGuideLine::Render_GameObject(void)
{
	Engine::_matrix matView, matProj, matViewProj;
	::ZeroMemory(&matView, sizeof(Engine::_matrix));
	::ZeroMemory(&matProj, sizeof(Engine::_matrix));
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	matViewProj = matView * matProj;

	for (int i = 0; i < 3; ++i)
	{
		m_pLine->DrawTransform(m_vLine[i], 2, &matViewProj, m_tColor[i]);
	}
}

CGuideLine * CGuideLine::Create(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine, const Engine::_float fLength)
{
	return new CGuideLine(pGraphicDev, pLine, fLength);
}

CGameObject * CGuideLine::Clone(void)
{
	return nullptr;
}

void CGuideLine::SaveData(HANDLE hFile)
{
}

void CGuideLine::LoadData(HANDLE hFile)
{
}

inline void CGuideLine::Free(void)
{
	CToolGameObject::Free();
}
