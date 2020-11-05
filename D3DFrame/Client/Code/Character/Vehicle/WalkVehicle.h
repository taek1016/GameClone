#ifndef WalkVehicle_h__
#define WalkVehicle_h__

#include "../VehicleBase.h"

class CWalkVehicle : public CVehicleBase
{
protected:
	explicit				CWalkVehicle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CWalkVehicle(const CWalkVehicle& rhs);
	virtual					~CWalkVehicle(void) = default;


protected:
	virtual void			key_Input(const Engine::_float& fTimeDelta);


};
#endif // WalkVehicle_h__
