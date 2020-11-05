#ifndef KodoBeastFoot_h__
#define KodoBeastFoot_h__

#include "../WeaponBase.h"

class CStatCom;

class CKodoBeastNose : public CWeaponBase
{
private:
	explicit						CKodoBeastNose(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CKodoBeastNose(const CKodoBeastNose & rhs);
	virtual							~CKodoBeastNose(void) = default;

public:
	virtual HRESULT					Late_Initialize(void) override;

private:
	virtual Engine::_bool			check_Collide(void) override;
	virtual void					attack(void) override;

public:
	static CKodoBeastNose*			Create(LPDIRECT3DDEVICE9 pGraphicDev, CCharacterBase* pTarget);
	virtual Engine::CGameObject*	Clone(void);
};

#endif // KodoBeastFoot_h__
