#ifndef FlyVehicle_h__
#define FlyVehicle_h__

#include "../VehicleBase.h"

class CFlyVehicle : public CVehicleBase
{
protected:
	explicit				CFlyVehicle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CFlyVehicle(const CFlyVehicle& rhs);
	virtual					~CFlyVehicle(void) = default;


protected:
	Engine::_bool			check_GroundUpperPos(Engine::_float& fYPos);
	virtual void			read_Data(void) override;

	virtual void			key_Input(const Engine::_float& fTimeDelta);
	virtual void			sky_KeyInput(const Engine::_float& fTimeDelta);
	virtual void			ground_KeyInput(const Engine::_float& fTimeDelta);

	Engine::_bool			m_bFlyStart;
	Engine::_bool			m_bFlyDown;
	Engine::_bool			m_bFly;
	Engine::_bool			m_bFlyFast;

	Engine::_float			m_fFlyFastSpeed;
	Engine::_float			m_fFlyNormalSpeed;
};
#endif // FlyVehicle_h__