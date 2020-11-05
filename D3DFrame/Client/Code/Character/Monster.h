#ifndef Monster_h__
#define Monster_h__

#include "character/Character.h"

class CWeaponBase;

class CMonsterBase : public CCharacterBase
{
protected:
	explicit		CMonsterBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit		CMonsterBase(const CMonsterBase& rhs);
	virtual			~CMonsterBase(void);

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;
	void							Render_GameObject(void) override;
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;

	virtual void					Hit(const Engine::_int& iDamage) override;

protected:
	void							print_DeadInfo(const Engine::_float& fTimeDelta);
	virtual void					print_Hit(const Engine::_float& fTimeDelta);
	virtual void					print_Name(void) PURE;
	virtual void					read_Data(void) override;
	virtual Engine::_float			get_ReadData(const Engine::_tchar* pKey) override;

	virtual void					make_Weapon(Engine::CGameObject* pTarget) { ; };

	void							mouse_Pick(void);
	virtual void					act_Determine(const Engine::_float& fTimeDelta) PURE;
	
	Engine::_bool					can_Act(const Engine::_tchar* pKey, Engine::CGameObject* pObj);
	void							can_NextAct(const Engine::_float& fTimeDelta);
	void							set_ActTime(const Engine::_float& fAfterTime);
	void							move_ToPlayer(const Engine::_float& fTimeDelta);
	void							look_Target(Engine::CGameObject* pObj);

	CWeaponBase*					m_pWeapon;

	Engine::_bool					m_bAfterAct;
	Engine::_float					m_fAfterAct;
	Engine::_float					m_fBeginActTime;
	Engine::_float					m_fTimeDelta;

	Engine::_bool					m_bMeleeAtt;

	Engine::_float					m_fCurPatternTime;
	Engine::_float					m_fHitHeight;

	Engine::_int					m_iCurPattern;
	Engine::_int					m_iExp;

	Engine::_bool					m_bHit;
	Engine::_bool					m_bDead;
	Engine::_bool					m_bLooted;

	D3DXCOLOR						m_tColor;
	Engine::_float					m_fCurDeadTime;
	Engine::_float					m_fDeadLifeTime;
	Engine::_tchar					m_szDieMessage[256];
	Engine::_int					m_iMoney;

	const Engine::_matrix*			m_pWeaponMatrix;

public:
	virtual Engine::CGameObject*	Clone(void) PURE;

};

#endif // Monster_h__
