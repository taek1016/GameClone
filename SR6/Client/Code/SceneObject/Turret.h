#ifndef Turret_h__
#define Turret_h__

#include "PickableObject.h"

enum ATTACK_DIR { DIR_UP, DIR_RIGHTUP, DIR_RIGHT, DIR_RIGHTDOWN, DIR_DOWN, DIR_LEFTDOWN, DIR_LEFT, DIR_LEFTUP, DIR_IDLE, DIR_END };

class CTurret : public CPickableObject
{
	CTurret();
	CTurret(const CTurret& rhs);

	ATTACK_DIR				m_CurState;

	Engine::CTexture*		m_pTexture[DIR_END]{};
	Engine::CTexture*		m_pCurTexture = nullptr;

	Engine::_float			m_fSearchTime = 0.f;

	Engine::_float			m_fCurFrame = 0.f;
	Engine::_float			m_fMaxFrame = 0.f;

	Engine::_float			m_fAttackTime = 0.f;

	Engine::_float			m_fAttackDistance = 0.f;

	CGameObject*			m_pTarget = nullptr;

	Engine::_int			m_iStatusAction[DIR_END]{};
public:
	Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta)override;

	void	Render_GameObject()override;

	HRESULT Initialize_GameObject()override;

	HRESULT Late_Initialize()override;

	bool	IsPicked();

	virtual CGameObject*	Clone(const Engine::_vec3 * pPos = nullptr) override;

	static CTurret* Create();

	void freeMem()override;

	void SetState(ATTACK_DIR dir);
};

#endif