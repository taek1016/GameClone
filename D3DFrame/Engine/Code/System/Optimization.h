#ifndef Optimization_h__
#define Optimization_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CFrustum;

class ENGINE_DLL COptimizationMgr : public CBase
{
	DECLARE_SINGLETON(COptimizationMgr)

private:
	explicit			COptimizationMgr(void);
	virtual				~COptimizationMgr(void);

public:
	void				Set_GraphicDev(LPDIRECT3DDEVICE9 pGraphicDev);
	_bool				Is_InFrustum_Object(const _vec3* pWorldPos, _float fRadius);

private:
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	CFrustum*			m_pFrustum;

private:
	inline virtual void	Free(void);
};

END

#endif // Optimization_h__
