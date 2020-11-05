#ifndef DoomguardSword_h__
#define DoomguardSword_h__

#include "../WeaponBase.h"

class CDoomguardSword : public CWeaponBase
{
private:
	explicit						CDoomguardSword(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CDoomguardSword(const CDoomguardSword& rhs);
	virtual							~CDoomguardSword(void) = default;

public:
	virtual HRESULT					Late_Initialize(void) override;

private:
	virtual Engine::_bool			check_Collide(void) override;
	virtual void					attack(void) override;

public:
	static CDoomguardSword*			Create(LPDIRECT3DDEVICE9 pGraphicDev, CCharacterBase* pTarget);
	virtual Engine::CGameObject*	Clone(void);

};
#endif // DoomguardSword_h__
