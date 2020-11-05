#ifndef InfernalHand_h__
#define InfernalHand_h__

#include "../WeaponBase.h"

class CStatCom;

class CInfernalHand : public CWeaponBase
{
private:
	explicit						CInfernalHand(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CInfernalHand(const CInfernalHand & rhs);
	virtual							~CInfernalHand(void) = default;

public:
	virtual HRESULT					Late_Initialize(void) override;

private:
	virtual void					attack(void) override;

public:
	static CInfernalHand*			Create(LPDIRECT3DDEVICE9 pGraphicDev, CCharacterBase* pTarget);
	virtual Engine::CGameObject*	Clone(void);
};

#endif // InfernalHand_h__
