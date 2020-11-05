#ifndef MonsterController_h__
#define MonsterController_h__

#include "Controller.h"

class CMonsterController : public Engine::CController
{
private:
	explicit					CMonsterController(void);
	virtual						~CMonsterController(void);

public:
	virtual HRESULT				Late_Initialize();
	virtual HRESULT				Initialize_Component() override;
	virtual Engine::_int		Update_Component(const Engine::_float & fTimeDelta) override;

private:
	void						Check_Map(void);
	void						Key_Input(const Engine::_float& fTimeDelta);
	void						Set_OnTerrain(void);
	Engine::_float				Compute_HeightOnTerrain(const Engine::_vec3* pPos, const Engine::BasicVertex* pVtx, const Engine::_ulong& dwTotalCnt);

	Engine::_float				m_fCameraChangeTime = 0.f;
	Engine::_float				m_fCameraChangeDelay = 0.5f;

	Engine::_float				m_fAttackCool = 1.f;
	Engine::_float				m_fCurCool = 1.f;

	Engine::CTransform*			m_pTransform = nullptr;
	Engine::_float				m_fSpeed;
	Engine::_float				m_fDetectLength;
	Engine::_float				m_fAttackLength;

	Engine::_bool				m_bJump = false;

	Engine::CGameObject*		m_pPlayer;

	class CBody*				m_pBody = nullptr;

public:
	static CMonsterController*	Create(void);

	CMonsterController*			Clone(void)override;
private:
	inline virtual void			freeMem();
};

#endif // MonsterController_h__
