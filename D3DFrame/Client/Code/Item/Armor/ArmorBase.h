#ifndef ArmorBase_h__
#define ArmorBase_h__

#include "../ItemBase.h"

class CArmorBase : public CItemBase
{
protected:
	explicit		CArmorBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit		CArmorBase(const CArmorBase& rhs);
	virtual			~CArmorBase(void) = default;

public:

};

#endif // ArmorBase_h__
