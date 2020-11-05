#include "stdafx.h"
#include "ToolStaticObjectCtrl.h"

#include "ToolStaticObject.h"

USING(Engine)

CToolStaticObjectCtrl::CToolStaticObjectCtrl(void)
	: CBase()
	, m_pSelected(nullptr)
{
}

CToolStaticObjectCtrl::~CToolStaticObjectCtrl(void)
{
}

CToolStaticObject * CToolStaticObjectCtrl::Get_Selected(void)
{
	return m_pSelected;
}

void CToolStaticObjectCtrl::Add_Objects(CToolStaticObject * pObj)
{
	m_ObjList.push_back(pObj);
}

void CToolStaticObjectCtrl::KeyInput(void)
{
	_vec3	vMousePos;
	DLL::pCalculate->ViewPortToProj(&vMousePos);
	DLL::pCalculate->ProjToView(&vMousePos, DLL::pCameraMgr->Get_Projection(), &vMousePos);
	DLL::pCalculate->ViewToWorld(&vMousePos, DLL::pCameraMgr->Get_ViewSpace(), &vMousePos);

	_vec3	vObjPos;
	D3DXPLANE	tPlane;
	for (auto iter : m_ObjList)
	{

		vObjPos = CToolStaticObjectCtrl::worldToProj(iter->Get_Pos());

		if (is_Same(&vMousePos, &vObjPos))
		{
			m_pSelected = iter;
			return;
		}
	}
}

_vec3 CToolStaticObjectCtrl::worldToProj(const Engine::_vec3* pPos)
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	_matrix matView, matProj;
	pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	_vec3 vResult;
	D3DXVec3TransformCoord(&vResult, pPos, &matView);
	D3DXVec3TransformCoord(&vResult, &vResult, &matProj);

	return vResult;
}

Engine::_bool CToolStaticObjectCtrl::is_Same(const Engine::_vec3 * pV1, const Engine::_vec3 * pV2)
{
	static const _float fNear = 0.2f;

	if (fNear >= D3DXVec3Length(&(*pV1 - *pV2)))
	{
		return true;
	}

	return false;
}

CToolStaticObjectCtrl * CToolStaticObjectCtrl::Create(void)
{
	return new CToolStaticObjectCtrl;
}

inline void CToolStaticObjectCtrl::Free(void)
{
}
