#ifndef PlayerBase_h__
#define PlayerBase_h__

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CPlayerBase : public CGameObject
{
protected:
	explicit			CPlayerBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit			CPlayerBase(const CPlayerBase& rhs);
	virtual				~CPlayerBase(void);

public:
	virtual HRESULT		Initialize_GameObject(void) PURE;

protected:

protected:
	virtual void		LoadData(const _tchar* pPath) PURE;
	inline virtual void	Free(void) override PURE;
};

END
#endif // PlayerBase_h__
