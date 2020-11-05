#include "stdafx.h"
#include "ToolNaviCtrl.h"

#include "Object/ToolGuideAxis.h"
#include "Object/NaviObject.h"
#include "Object/ToolTerrainTex.h"

CToolNaviCtrl::CToolNaviCtrl(void)
	: m_pNaviObj(nullptr)
	, m_pBuffer(nullptr)
	, m_pActivateGuideLine(nullptr)
	, m_bActivated(false)
	, m_bAxisSelected(false)
{
}

CToolNaviCtrl::~CToolNaviCtrl(void)
{
}

Engine::_int CToolNaviCtrl::Update(const Engine::_float & fTimeDelta)
{
	return Engine::_int();
}

void CToolNaviCtrl::KeyInput(void)
{
	if (!check_ActiveGuideLine())
	{
		m_pActivateGuideLine = nullptr;
	}
}

void CToolNaviCtrl::Render(void)
{
	if (m_pActivateGuideLine)
	{
		m_pActivateGuideLine->Render_Axis();
	}
}

void CToolNaviCtrl::Initialize_Ctrl(CToolNavi* pObj, Engine::CStaticMesh* pBuffer)
{
	if (nullptr != pObj)
	{
		m_pNaviObj = pObj;
		m_pNaviObj->AddRef();
	}

	if (nullptr != pBuffer)
	{
		m_pBuffer = pBuffer;
		m_pBuffer->AddRef();
	}
}

void CToolNaviCtrl::Activate(vector<Engine::CCell*>* pVecCell)
{
	auto	pGraphicDev = DLL::pGraphicDev->GetDevice();
	auto	pLine = DLL::pGraphicDev->GetLine();

	Engine::_vec3*	pPos = nullptr;
	m_pVecCell = pVecCell;
	for (auto iterVec : *pVecCell)
	{
		for (int i = 0; i < Engine::CCell::POINT::POINT_END; ++i)
		{
			pPos = iterVec->Get_Point(static_cast<Engine::CCell::POINT>(i));
			for (auto iterList : m_listGuideLine)
			{
				if (iterList->Is_Same(pPos))
				{
					break;
				}
			}
		}
	}
}

void CToolNaviCtrl::Add_Guide(Engine::_vec3 * pPos)
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();
	auto pLine = DLL::pGraphicDev->GetLine();

	for (auto iter : m_listGuideLine)
	{
		if (::D3DXVec3Length(&(*iter->Get_CenterPos() - *pPos)) < FLT_EPSILON)
		{
			return;
		}
	}
	m_listGuideLine.push_back(CToolGuideAxis::Create(pGraphicDev, pLine, pPos));
}

Engine::_bool CToolNaviCtrl::PickOnNavi(Engine::_vec3 * pOut)
{
	Engine::_vec3	vMousePos;
	DLL::pCalculate->ViewPortToProj(&vMousePos);
	DLL::pCalculate->ProjToView(&vMousePos, DLL::pCameraMgr->Get_Projection(), &vMousePos);

	Engine::_vec3	vRayPos, vRayDir;

	vRayPos = Engine::_vec3(0.f, 0.f, 0.f);
	vRayDir = vMousePos - vRayPos;

	// 뷰 스페이스에서 월드 스페이스로
	Engine::_matrix		matView;

	DLL::pGraphicDev->GetDevice()->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	Engine::_float			fU, fV, fDist;
	Engine::_float			fJudgeDist = 10000.f;
	Engine::_float			fPurposeDist = fJudgeDist;

	Engine::_bool			bIsIntersected = false;
	Engine::_vec3			vResult;
	auto pVecCell = m_pNaviObj->Get_Vec();
	for (auto iter : *pVecCell)
	{
		auto pPos1 = iter->Get_Point(Engine::CCell::POINT_A);
		auto pPos2 = iter->Get_Point(Engine::CCell::POINT_B);
		auto pPos3 = iter->Get_Point(Engine::CCell::POINT_C);

		Engine::_float fLength1 = 10000000.f;

		if (D3DXIntersectTri(pPos1, pPos2, pPos3,
			&vRayPos,
			&vRayDir, &fU, &fV, &fDist))
		{
			vResult = vRayPos + (fDist * vRayDir);
			
			bIsIntersected = true;

			Engine::_float fLength2 = fabsf(D3DXVec3Length(&(*pPos1 - vResult)));
			if (fLength1 >= fLength2)
			{
				fLength1 = fLength2;
				*pOut = *pPos1;
			}

			fLength2 = fabsf(D3DXVec3Length(&(*pPos2 - vResult)));
			if (fLength1 >= fLength2)
			{
				fLength1 = fLength2;
				*pOut = *pPos2;
			}

			fLength2 = fabsf(D3DXVec3Length(&(*pPos3 - vResult)));
			if (fLength1 >= fLength2)
			{
				fLength1 = fLength2;
				*pOut = *pPos3;
			}
// 			if (fPurposeDist > fDist)
// 			{
// 				*pOut = vRayPos + (fDist * vRayDir);
// 				fPurposeDist = fDist;
// 				bIsIntersected = true;
// 			}
			break;
		}
	}

	return bIsIntersected;
}

CToolGuideAxis * CToolNaviCtrl::Get_ActivatedAxis(void)
{
	return m_pActivateGuideLine;
}

Engine::_bool CToolNaviCtrl::check_ActiveGuideLine(void)
{
	Engine::_vec3 vMousePos;

	if (CToolNaviCtrl::PickOnNavi(&vMousePos))
	{
		for (auto iterList : m_listGuideLine)
		{
			if (iterList->Is_Same(&vMousePos))
			{
				m_vMeshPos = vMousePos;
				m_pActivateGuideLine = iterList;
				return true;
			}
		}
	}

	return false;
}

void CToolNaviCtrl::clear_List(void)
{
	for_each(m_listGuideLine.begin(), m_listGuideLine.end(), Engine::Safe_Release<CToolGuideAxis*>);
}

CToolNaviCtrl * CToolNaviCtrl::Create(void)
{
	return new CToolNaviCtrl();
}

inline void CToolNaviCtrl::Free(void)
{
	clear_List();
	Engine::Safe_Release(m_pNaviObj);
	Engine::Safe_Release(m_pBuffer);
}