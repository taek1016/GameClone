#ifndef BossController_h__
#define BossController_h__

#include "Controller.h"

class CBossController : public Engine::CController
{
private:
	explicit					CBossController(void);
	virtual						~CBossController(void);

public:
	virtual HRESULT				Late_Initialize();
	virtual HRESULT				Initialize_Component() override;
	virtual Engine::_int		Update_Component(const Engine::_float & fTimeDelta) override;

	void						Jump();
	Engine::_bool				IsLanded() { return m_bLanded; }
	void						LandAttack();
private:
	void						Check_Map(void);
	void						Key_Input(const Engine::_float& fTimeDelta);
	void						Set_OnTerrain(void);
	Engine::_float				Compute_HeightOnTerrain(const Engine::_vec3* pPos, const Engine::BasicVertex* pVtx, const Engine::_ulong& dwTotalCnt);

	Engine::_float				m_fCameraChangeTime = 0.f;
	Engine::_float				m_fCameraChangeDelay = 0.5f;

	Engine::_float				m_fAttackCool = 10.f;
	Engine::_float				m_fCurCool = 0.f;

	Engine::_float				m_fNowAttackingTime = 0.f;

	Engine::_bool				m_bNowAttacking = false;

	Engine::CTransform*			m_pTransform = nullptr;
	Engine::_float				m_fSpeed;
	Engine::_float				m_fDetectLength;
	Engine::_float				m_fAttackLength;

	Engine::_float				m_fJumpOffset = 0;

	Engine::_float				m_fShakeTime = 0;
	Engine::_float				m_fShakeOffset = 0;
	Engine::_bool				m_bShaking = false;

	Engine::_bool				m_bJump = false;
	Engine::_bool				m_bLanded = true;
	Engine::_bool				m_bVoming = false;

	Engine::CGameObject*		m_pPlayer;

	class CBody*				m_pBody = nullptr;

public:
	static CBossController*		Create(void);

	CBossController*			Clone(void)override;
private:
	inline virtual void			freeMem();
};

#endif // MonsterController_h__
