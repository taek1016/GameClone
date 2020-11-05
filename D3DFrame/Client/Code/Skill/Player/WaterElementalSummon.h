#ifndef WaterElementalSummon_h__
#define WaterElementalSummon_h__

#include "../SummonSkillBase.h"

class CWaterElementalSummon : public CSummonSkillBase
{
private:
	explicit						CWaterElementalSummon(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CWaterElementalSummon(const CWaterElementalSummon& rhs);
	virtual							~CWaterElementalSummon(void) = default;

public:
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;

public:
	static CWaterElementalSummon*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // WaterElementalSummon_h__
