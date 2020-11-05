#ifndef VehicleBase_h__
#define VehicleBase_h__

#include "Character.h"

class CPlayer;

class CVehicleBase : public CCharacterBase
{
protected:
	explicit				CVehicleBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CVehicleBase(const CVehicleBase& rhs);
	virtual					~CVehicleBase(void) = default;

public:
	virtual HRESULT			Initialize_GameObject(void) override;
	virtual HRESULT			Late_Initialize(void) override;

	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	void					Ride_Vehicle(CPlayer* pCharacter);
	void					DisEmbark(void);

protected:
	void					set_SeatBoneName(const char* pName);
	void					get_CameraRight(Engine::_vec3 * pRight);
	virtual void			pickUp_Target(void);
	virtual void			key_Input(const Engine::_float& fTimeDelta) PURE;
	virtual void			read_Data(void);
	virtual Engine::_float	get_ReadData(const Engine::_tchar* pKey);

	string					m_StrSeatBoneName;
	Engine::_float			m_fRunSpeed;
	Engine::_float			m_fWalkSpeed;
	Engine::_float			m_fTargetHeight;

	Engine::_bool			m_bRun;
	Engine::_bool			m_bRiding;
	Engine::_bool			m_bDead;

	CPlayer*				m_pRidingTarget;
	Engine::CTransform*		m_pRidingTargetTransform;
};

#endif // VehicleBase_h__
