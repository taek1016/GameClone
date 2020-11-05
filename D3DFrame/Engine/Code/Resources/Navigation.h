#ifndef Navigation_h__
#define Navigation_h__

#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CNavigation
{
private:
	explicit	CNavigation(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine);
	virtual		~CNavigation(void);

public:
	static CNavigation*	Create(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine);
	virtual void		Clone();

private:
	inline virtual void	Free(void);
};
END

#endif // Navigation_h__
