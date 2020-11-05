#include "CalculateMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CCalculateMgr)

CCalculateMgr::CCalculateMgr(void)
	: m_hWnd(nullptr)
	, m_pGraphicDev(nullptr)
	, m_dwWinCX(0)
	, m_dwWinCY(0)
{

}

CCalculateMgr::~CCalculateMgr(void)
{
	Free();
}

HRESULT CCalculateMgr::Initialize_Calculate(LPDIRECT3DDEVICE9 pGraphicDev, HWND hWnd, const _ulong& dwWinCX, const _ulong& dwWinCY)
{
	m_pGraphicDev = pGraphicDev;
	NULL_CHECK_RETURN(m_pGraphicDev, E_FAIL);

	m_dwWinCX = dwWinCX;
	m_dwWinCY = dwWinCY;

	m_hWnd = hWnd;
	NULL_CHECK_RETURN(m_hWnd, E_FAIL);

	return S_OK;
}

void CCalculateMgr::ViewPortToProj(_vec3* pOut)
{
#pragma region GetClientPos
	POINT			ptMouse{};
	_vec2			vPos;
	// 윈도우 영역 == 뷰포트 영역
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);
	vPos.x = static_cast<_float>(ptMouse.x);
	vPos.y = static_cast<_float>(ptMouse.y);
#pragma endregion

#pragma region GetViewPort
	D3DVIEWPORT9			ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	m_pGraphicDev->GetViewport(&ViewPort);
#pragma endregion

#pragma region ViewPortToProj
	static const _float fToHalf = 0.5f;
	static const _float fHalfViewPort = 1.f;

	pOut->x = ptMouse.x / (ViewPort.Width * fToHalf) - fHalfViewPort;
	pOut->y = -ptMouse.y / (ViewPort.Height * fToHalf) + fHalfViewPort;
	pOut->z = 1.f;
#pragma endregion
}

void CCalculateMgr::ProjToView(_vec3* pOut, const _matrix * pmatProj, const _vec3* pOriginalPos)
{
	_matrix		matProj;

	D3DXMatrixInverse(&matProj, 0, pmatProj);
	D3DXVec3TransformCoord(pOut, pOriginalPos, &matProj);
}

void CCalculateMgr::ViewToWorld(_vec3* pOut, const _matrix * pmatView, const _vec3* pOriginalPos)
{
	_matrix		matView;

	D3DXMatrixInverse(&matView, 0, pmatView);
	D3DXVec3TransformCoord(pOut, pOriginalPos, &matView);
}

void CCalculateMgr::CrossPointForLineToPlane(_vec3 * pOut, const _vec3 * pPoint1, const _vec3 * pPoint2, const D3DXPLANE * pPlane)
{
	LINE3D tLine3D;
	LinearEquationFromPoints(&tLine3D, pPoint2, pPoint1);

	CrossPointForLineToPlane(pOut, &tLine3D, pPlane);
}

void CCalculateMgr::CrossPointForLineToPlane(_vec3 * pOut, const LINE3D * pLine, const D3DXPLANE * pPlane)
{
	_vec3 N = { pPlane->a, pPlane->b, pPlane->c };

	_vec3 PlaneP = { 1.f, 1.f, 1.f };

	if (0 != pPlane->a)
		PlaneP.x = -(pPlane->b + pPlane->c + pPlane->d) / pPlane->a;

	else if (0 != pPlane->b)
		PlaneP.y = -(pPlane->a + pPlane->c + pPlane->d) / pPlane->b;

	else if (0 != pPlane->c)
		PlaneP.z = -(pPlane->a + pPlane->b + pPlane->d) / pPlane->c;

	else
	{
		ZeroMemory(pOut, sizeof(_vec3));
		return;
	}

	if (0.f == D3DXVec3Dot(&pLine->vDir, &N))
	{
		ZeroMemory(pOut, sizeof(_vec3));
		return;
	}

	_float parameter = (D3DXVec3Dot(&(PlaneP - pLine->vPos), &N) / D3DXVec3Dot(&pLine->vDir, &N));

	*pOut = pLine->vPos + parameter * pLine->vDir;
}

void CCalculateMgr::LinearEquationFromPoints(LINE3D * pOut, const _vec3 * pPos1, const _vec3 * pPos2)
{
	_vec3 vDir = *pPos1 - *pPos2;

	pOut->vDir = vDir;
	pOut->vPos = *pPos1;
}

void CCalculateMgr::PickingOnPlane(_vec3 * pOut, const _matrix * pmatProj, const _matrix * pmatView, const D3DXPLANE* pPlane)
{
	CCalculateMgr::ViewPortToProj(pOut);
	CCalculateMgr::ProjToView(pOut, pmatProj, pOut);
	CCalculateMgr::ViewToWorld(pOut, pmatView, pOut);

	_vec3 vRayOrigin(0.f, 0.f, 0.f);
	CCalculateMgr::ViewToWorld(&vRayOrigin, pmatView, &vRayOrigin);

	CrossPointForLineToPlane(pOut, &vRayOrigin, pOut, pPlane);
}

_bool CCalculateMgr::IsCWYZero(const _vec3* pV1, const _vec3* pV2, const _vec3* pV3)
{
	_float iResult = (pV1->x * pV2->z + pV2->x * pV3->z + pV3->x * pV1->z) - (pV1->x * pV3->z + pV2->x * pV1->z + pV3->x* pV2->z);
	if (iResult < 0.f)
	{
		return true;
	}
	return false;
}

void CCalculateMgr::Swap(_vec3 * pV1, _vec3 * pV2)
{
	_vec3 vTemp = *pV1;

	*pV1 = *pV2;
	*pV2 = vTemp;
}

void CCalculateMgr::CrossVec2(_vec2* pOut, const _vec2* pIn)
{
	static const _float fReverse = -1.f;
	_vec2 vCopy = *pIn;

	*pOut = _vec2(vCopy.y * fReverse, vCopy.x);
}

_float CCalculateMgr::GetVec2Dot(const _vec2* pV1, const _vec2* pV2)
{
	return (pV1->x * pV2->x + pV1->y * pV2->y);
}

inline void CCalculateMgr::Free(void)
{
	Safe_Release(m_pGraphicDev);
}