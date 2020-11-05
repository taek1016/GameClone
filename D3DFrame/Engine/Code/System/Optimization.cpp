#include "Optimization.h"

#include "Frustum.h"

USING(Engine)
IMPLEMENT_SINGLETON(COptimizationMgr)

COptimizationMgr::COptimizationMgr(void)
	: CBase()
	, m_pGraphicDev(nullptr)
{
}

COptimizationMgr::~COptimizationMgr(void)
{
	Free();
}

void COptimizationMgr::Set_GraphicDev(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
	m_pGraphicDev->AddRef();

	m_pFrustum = CFrustum::Create(m_pGraphicDev);
}

_bool COptimizationMgr::Is_InFrustum_Object(const _vec3 * pWorldPos, _float fRadius)
{
	return m_pFrustum->Is_InFrustum_ForObject(pWorldPos, fRadius);
}

inline void COptimizationMgr::Free(void)
{
	Safe_Release(m_pGraphicDev);
}
