#ifndef BossZombie_h__
#define BossZOmbie_h__

#include "SceneObject/MonsterBase.h"

class CBossZombie : public CMonster
{
	CBossZombie();
	CBossZombie(const CBossZombie& rhs);

	_float				m_fJumpDelay = 10;
	_float				m_fJumpTime = 0;
	_bool				m_bJump = false;

public:
	Engine::_int		Update_GameObject(const Engine::_float& fTimeDelta)override;
	void				Render_GameObject()override;

	HRESULT				Initialize_GameObject()override;
	virtual void		Take_Damage(const _float& fDamage);

	static CBossZombie* Create();

	CBossZombie*		Clone(const Engine::_vec3* pPos = nullptr)override;

	void				LoadData(HANDLE hFile)override;
};

#endif