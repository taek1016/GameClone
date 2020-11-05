#ifndef MatrialBase_h__
#define MatrialBase_h__

#include "ItemBase.h"

BEGIN(Engine)

class ENGINE_DLL CMaterialBase : public CItemBase
{
protected:
	explicit		CMaterialBase(void);
	explicit		CMaterialBase(const CMaterialBase& rhs);
	virtual			~CMaterialBase(void);

public:
	virtual HRESULT		Late_Initialize() PURE;
	virtual HRESULT		Initialize_GameObject() PURE;

public:
	virtual CGameObject* Clone(const _vec3* pPos) PURE;
};

END
#endif // MatrialBase_h__
