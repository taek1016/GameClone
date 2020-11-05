#ifndef SummonVehicle_h__
#define SummonVehicle_h__

#include "../SummonSkillBase.h"

class CSummonVehicleBase : public CSummonSkillBase
{
protected:
	explicit				CSummonVehicleBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CSummonVehicleBase(const CSummonVehicleBase& rhs);
	virtual					~CSummonVehicleBase(void) = default;

public:
	virtual HRESULT			Initialize_GameObject(void) override;
	virtual HRESULT			Late_Initialize(void) override;

	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void			Render_GameObject(void) override;

protected:
	virtual void			summon_Effect(const Engine::_vec3* pPos) PURE;
};

#endif // SummonVehicle_h__
