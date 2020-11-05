#ifndef SupporterBase_h__
#define SupporterBase_h__

#include "../Character.h"

class CWeaponBase;

class CSupporterBase : public CCharacterBase
{
protected:
	explicit				CSupporterBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CSupporterBase(const CSupporterBase& rhs);
	virtual					~CSupporterBase(void) = default;

public:
	virtual HRESULT			Initialize_GameObject(void) override;
	virtual HRESULT			Late_Initialize(void) override;
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void			Render_GameObject(void) override;

protected:
	virtual void			read_Data(void);
	virtual Engine::_float	get_ReadData(const Engine::_tchar* pKey);

	virtual void			act_Determine(const Engine::_float& fTimeDelta) PURE;
	virtual void			make_Weapon(void) { ; };

	Engine::_bool			can_Act(const Engine::_tchar* pKey, Engine::CGameObject* pObj);
	void					can_NextAct(const Engine::_float& fTimeDelta);
	void					set_ActTime(const Engine::_float& fAfterTime);
	void					move_ToTarget(CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void					look_Target(Engine::CGameObject* pObj);

	CWeaponBase*			m_pWeapon;

	Engine::_bool			m_bAfterAct;

	Engine::_float			m_fCurLifeTime;
	Engine::_float			m_fMaxLifeTime;

	Engine::_float			m_fAfterAct;
	Engine::_float			m_fBeginActTime;
	Engine::_float			m_fRunSpeed;

	Engine::CGameObject*	m_pTarget;
	Engine::_float			m_fCurDetermineTime;

	Engine::_bool			m_bMeleeAtt;

	Engine::_float			m_fCurPatternTime;

	Engine::_int			m_iCurPattern;

protected:
	inline virtual void		Free(void) override;
};
#endif // SupporterBase_h__
