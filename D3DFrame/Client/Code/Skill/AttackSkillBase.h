#ifndef AttackSkillBase_h__
#define AttackSkillBase_h__

#include "SkillBase.h"

class CAttackSkillBase : public CSkillBase
{
protected:
	explicit					CAttackSkillBase(const CAttackSkillBase& rhs);
	explicit					CAttackSkillBase(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual						~CAttackSkillBase(void);

public:
	virtual HRESULT				Initialize_GameObject(void) override PURE;
	virtual HRESULT				Late_Initialize(void) override PURE;
	virtual Engine::_int		Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void				Render_GameObject(void) override;

	virtual void				Attack(CGameObject* pTarget) PURE;

protected:
	void						set_Speed(const Engine::_float& fSpeed);
	virtual void				act_Determine(const Engine::_float& fTimeDelta) PURE;
	virtual void				check_DeadCondition(void) PURE;
	virtual void				dead_Effect(void) PURE;

	Engine::CDynamicMesh*		m_pMesh;
	Engine::_float				m_fSpeed;
	Engine::_bool				m_bDead;
};

#endif // AttackSkillBase_h__
