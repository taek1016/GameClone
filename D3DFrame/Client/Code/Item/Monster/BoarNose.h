#ifndef BoarNose_h__
#define BoarNose_h__

#include "../WeaponBase.h"

BEGIN(Engine)
class CSphereCollider;
END

class CBoarNose : public CWeaponBase
{
private:
	explicit						CBoarNose(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CBoarNose(const CBoarNose& rhs);
	virtual							~CBoarNose(void);

public:
	virtual HRESULT					Late_Initialize(void) override;

private:
	virtual Engine::_bool			check_Collide(void) override;
	virtual void					attack(void) override;

public:
	static CBoarNose*				Create(LPDIRECT3DDEVICE9 pGraphicDev, CCharacterBase* pTarget);
	virtual Engine::CGameObject*	Clone(void);
};

#endif // BoarNose_h__
