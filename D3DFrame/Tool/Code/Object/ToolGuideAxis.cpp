#include "stdafx.h"
#include "ToolGuideAxis.h"

CToolGuideAxis::CToolGuideAxis(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine)
	: CBase()
	, m_pGraphicDev(pGraphicDev)
	, m_pLine(pLine)
{
	::ZeroMemory(m_vAxis, sizeof(Engine::_vec3) * AXIS_END * POINT_END);
	::ZeroMemory(m_bActivateAxis, sizeof(Engine::_bool) * AXIS_END);

	m_pGraphicDev->AddRef();
	m_pLine->AddRef();

	// Up은 초록, Look은 파랑, Right는 빨강 
	m_tColor[AXIS_RIGHT] = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	m_tColor[AXIS_UP] = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	m_tColor[AXIS_LOOK] = D3DXCOLOR(0.f, 0.5f, 0.5f, 1.f);
}

CToolGuideAxis::~CToolGuideAxis(void)
{
}

void CToolGuideAxis::KeyInput(void)
{
	::ZeroMemory(m_bActivateAxis, sizeof(Engine::_bool) * AXIS_END);

	// 1) 각 끝점과 pPos를 투영 상태에서 비교.
	Engine::_vec3	vMousePos;
	Engine::_matrix matWorldToProj;
	Engine::_matrix matView, matProj;

	DLL::pCalculate->ViewPortToProj(&vMousePos);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	vMousePos.z = 0.f;

	static const Engine::_float fNear = 0.2f;

	Engine::_vec3 vAxisPos;
	for (Engine::_int i = 0; i < AXIS_END; ++i)
	{
		vAxisPos = m_vAxis[i][END_LINE];

		D3DXVec3TransformCoord(&vAxisPos, &vAxisPos, &matView);
		D3DXVec3TransformCoord(&vAxisPos, &vAxisPos, &matProj);
		vAxisPos.z = 0.f;
		if (fNear >= D3DXVec3Length(&(vMousePos - vAxisPos)))
		{
			m_bActivateAxis[i] = true;
			break;
		}
	}
}

void CToolGuideAxis::Render_Axis(void)
{
	Engine::_vec3 vAxis[AXIS_END];
	Engine::_float fLength = 10.f;
	vAxis[AXIS_RIGHT] = Engine::_vec3(fLength, 0.f, 0.f);
	vAxis[AXIS_UP] = Engine::_vec3(0.f, fLength, 0.f);
	vAxis[AXIS_LOOK] = Engine::_vec3(0.f, 0.f, fLength);

	for (Engine::_int i = 0; i < AXIS_END; ++i)
	{
		m_vAxis[i][START_LINE] = *m_pOriPos;
		m_vAxis[i][END_LINE] = *m_pOriPos + vAxis[i];
	}

#pragma region InitializeMatrix
	Engine::_matrix matViewProj;
	::ZeroMemory(&matViewProj, sizeof(Engine::_matrix));
	Engine::_matrix matView, matProj;
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

	matViewProj = matView * matProj;
#pragma endregion

#pragma region RenderAxis
	static const Engine::_float fThin = 2.f;
	static const Engine::_float fThick = 4.f;

	for (Engine::_int i = 0; i < AXIS_END; ++i)
	{
		if (m_bActivateAxis[i])
		{
			m_pLine->SetWidth(fThick);
		}
		else
		{
			m_pLine->SetWidth(fThin);
		}
		m_pLine->DrawTransform(m_vAxis[i], POINT_END, &matViewProj, m_tColor[i]);
	}
#pragma endregion

}

Engine::_bool CToolGuideAxis::Get_Activated(const ACTIVATED_AXIS & eAxis)
{
	return m_bActivateAxis[eAxis];
}

Engine::_bool CToolGuideAxis::Is_Same(const Engine::_vec3 * pPos)
{
	static const Engine::_float fNear = 0.5f;

	if (fNear >= D3DXVec3Length(&(*m_pOriPos - *pPos)))
	{
		return true;
	}

	return false;
}

Engine::_vec3 * CToolGuideAxis::Get_CenterPos(void)
{
	return m_pOriPos;
}

void CToolGuideAxis::Move_Pos(const Engine::_vec3 * pDir)
{
	*m_pOriPos += *pDir;
}

void CToolGuideAxis::initialize_Pos(Engine::_vec3 * pPos)
{
	m_pOriPos = pPos;

	Engine::_vec3 vAxis[AXIS_END];
	vAxis[AXIS_RIGHT] = Engine::_vec3(1.f, 0.f, 0.f);
	vAxis[AXIS_UP] = Engine::_vec3(0.f, 1.f, 0.f);
	vAxis[AXIS_LOOK] = Engine::_vec3(0.f, 0.f, 1.f);

	for (Engine::_int i = 0; i < AXIS_END; ++i)
	{
		m_vAxis[i][START_LINE] = *m_pOriPos;
		m_vAxis[i][END_LINE] = *m_pOriPos + vAxis[i];
	}
}

CToolGuideAxis * CToolGuideAxis::Create(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine, Engine::_vec3* pPos)
{
	CToolGuideAxis* pInstance = new CToolGuideAxis(pGraphicDev, pLine);

	pInstance->initialize_Pos(pPos);

	return pInstance;
}

inline void CToolGuideAxis::Free(void)
{
	Engine::Safe_Release(m_pGraphicDev);
	Engine::Safe_Release(m_pLine);
}
