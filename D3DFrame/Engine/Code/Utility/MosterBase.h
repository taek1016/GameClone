#ifndef MosterBase_h__
#define MosterBase_h__

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CMonsterBase : public CGameObject
{
protected:
	explicit			CMonsterBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit			CMonsterBase(const CMonsterBase& rhs);
	virtual				~CMonsterBase(void);

public:
	virtual HRESULT		Initialize_GameObject(void) PURE;

protected:
	virtual void		LoadData(const _tchar* pPath) PURE;
	inline virtual void	Free(void) override PURE;
};

END
#endif // MosterBase_h__
