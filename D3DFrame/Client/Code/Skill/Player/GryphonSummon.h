#ifndef GryphonSummon_h__
#define GryphonSummon_h__

#include "SummonVehicleBase.h"

class CGryphonSummon : public CSummonVehicleBase
{
private:
	explicit						CGryphonSummon(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CGryphonSummon(const CGryphonSummon& rhs);
	virtual							~CGryphonSummon(void) = default;

private:
	virtual void					summon_Effect(const Engine::_vec3* pPos) override;

public:
	static CGryphonSummon*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // GryphonSummon_h__
