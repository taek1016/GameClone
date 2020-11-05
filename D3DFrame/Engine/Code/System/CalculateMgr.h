#ifndef CalculateMgr_h__
#define CalculateMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CCalculateMgr : public CBase
{
	DECLARE_SINGLETON(CCalculateMgr)

private:
	explicit			CCalculateMgr(void);
	virtual				~CCalculateMgr(void);

public:
	HRESULT				Initialize_Calculate(LPDIRECT3DDEVICE9 pGraphicDev, HWND hWnd, const _ulong& dwWinCX, const _ulong& dwWinCY);

	void				ViewPortToProj(_vec3* pOut);
	void				ProjToView(_vec3* pOut, const _matrix * pmatProj, const _vec3* pOriginalPos);
	void				ViewToWorld(_vec3* pOut, const _matrix * pmatView, const _vec3* pOriginalPos);
	void				PickingOnPlane(_vec3 * pOut, const _matrix * pmatProj, const _matrix * pmatView, const D3DXPLANE* pPlane);

	_bool				IsCWYZero(const _vec3* pV1, const _vec3* pV2, const _vec3* pV3);
	void				Swap(_vec3* pV1, _vec3* pV2);

	void				CrossVec2(_vec2* pOut, const _vec2* pIn);
	_float				GetVec2Dot(const _vec2* pV1, const _vec2* pV2);

private:
	void				CrossPointForLineToPlane(_vec3* pOut, const _vec3 * pPoint1, const _vec3 * pPoint2, const D3DXPLANE * pPlane);
	void				CrossPointForLineToPlane(_vec3 * pOut, const LINE3D * pLine, const D3DXPLANE * pPlane);
	void				LinearEquationFromPoints(LINE3D * pOut, const _vec3 * pPos1, const _vec3 * pPos2);

	LPDIRECT3DDEVICE9	m_pGraphicDev;
	HWND				m_hWnd;

	_ulong				m_dwWinCX;
	_ulong				m_dwWinCY;
private:
	inline virtual void	Free(void);
};
END
#endif // CalculateMgr_h__
