#ifndef ChickenSummon_h__
#define ChickenSummon_h__

#include "SummonVehicleBase.h"

class CChickenSummon : public CSummonVehicleBase
{
private:
	explicit						CChickenSummon(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CChickenSummon(const CChickenSummon& rhs);
	virtual							~CChickenSummon(void) = default;

private:
	virtual void					summon_Effect(const Engine::_vec3* pPos) override;

public:
	static CChickenSummon*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // ChickenSummon_h__
