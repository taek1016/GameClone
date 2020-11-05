#ifndef NefarianFLFoot_h__
#define NefarianFLFoot_h__

#include "../WeaponBase.h"

class CStatCom;

class CNefarianFLFoot : public CWeaponBase
{
private:
	explicit	CNefarianFLFoot(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit	CNefarianFLFoot(const CNefarianFLFoot& rhs);
	virtual		~CNefarianFLFoot(void) = default;

public:
	virtual HRESULT					Late_Initialize(void) override;

private:
	virtual void					attack(void) override;

public:
	static CNefarianFLFoot*			Create(LPDIRECT3DDEVICE9 pGraphicDev, CCharacterBase* pTarget);
	virtual Engine::CGameObject*	Clone(void);
};

#endif // NefarianFLFoot_h__
