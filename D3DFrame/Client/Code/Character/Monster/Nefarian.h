#ifndef Nefarian_h__
#define Nefarian_h__

#include "../Monster.h"

BEGIN(Engine)
class CGameObject;
END

class CNefarian : public CMonsterBase
{
	enum NEFARIAN_PATTERN			{ NEF_ATTACK, NEF_BREATH_CAST, NEF_BREATH, NEF_STOMP, NEF_LIFT, NEF_HOVER, NEF_LAND, NEF_PATTERN_END };

private:
	explicit						CNefarian(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CNefarian(const CNefarian& rhs);
	virtual							~CNefarian(void) = default;

private:
	virtual void					print_Name(void) override;
	virtual void					make_Weapon(Engine::CGameObject* pTarget) override;

	virtual void					act_Determine(const Engine::_float& fTimeDelta) override;
	void							initialize_ActionCols(void);
	void							move_Pattern(Engine::CGameObject* pPlayer, const Engine::_float & fTimeDelta);
	void							melee_Attack(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							breath_Cast(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							breath_Shot(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							stomp_Around(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							lift_Off(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							hover(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							landing(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);

	Engine::_int					m_iHoverCount;

public:
	static CNefarian*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // Nefarian_h__
