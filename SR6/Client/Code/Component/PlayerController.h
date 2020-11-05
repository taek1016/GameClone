#ifndef PlayerController_h__
#define PlayerController_h__

#include "Controller.h"

class CPlayerController : public Engine::CController
{
private:
	explicit					CPlayerController(void);
	virtual						~CPlayerController(void);

public:
	//void						Set_Dir(const Engine::_vec3* vDir);
	virtual HRESULT				Late_Initialize();
	virtual HRESULT				Initialize_Component() override;
	virtual Engine::_int		Update_Component(const Engine::_float & fTimeDelta) override;

	void						AirBorne();
	void						Jump();

private:
	void						Key_Input(const Engine::_float& fTimeDelta);
	void						Set_OnTerrain(void);
	Engine::_float				Compute_HeightOnTerrain(const Engine::_vec3* pPos, const Engine::BasicVertex* pVtx, const Engine::_ulong& dwTotalCnt);

	Engine::CTransform*			m_pTransform = nullptr;
	Engine::CRigidBody*			m_pRigidBody = nullptr;
	Engine::_float				m_fSpeed;

	Engine::_bool				m_bSingleShot = true;
	Engine::_bool				m_bAirborne = false;

	Engine::_float				m_fJumpPower = 4.f;

	Engine::_bool				m_bNowJumping = false;

	CBody*						m_pBody = nullptr;
	Engine::_float				m_fAirTime = 0.f;
	Engine::_float				m_fAirbornePower = 0.f;

public:
	static CPlayerController*	Create(void);

private:
	inline virtual void			freeMem();
};

#endif // PlayerController_h__
