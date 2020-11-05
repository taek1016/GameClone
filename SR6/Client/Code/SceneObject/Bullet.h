#ifndef Bullet_h__
#define Bullet_h__

#include "GameObject.h"

class CBullet : public Engine::CGameObject
{
private:
	explicit	CBullet(void);
	explicit	CBullet(const CBullet& rhs);
	virtual		~CBullet(void);

public:
	virtual HRESULT			Initialize_GameObject();
	virtual HRESULT			Late_Initialize();
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void			Render_GameObject();

	void					Set_Info(const Engine::_vec3* pPos, const Engine::_vec3* pLook, const Engine::_float fSpeed, const Engine::_float fDamage);

private:
	Engine::_vec3			m_vLook;

	Engine::_float			m_fSpeed;
	Engine::_float			m_fLifeTime = 0.f;
	Engine::_float			m_fDieTime = 3.f;

	Engine::CCollider*		m_pCollider = nullptr;
	Engine::CTransform*		m_pTransform = nullptr;

public:
	static CBullet*			Create(void);
	virtual CGameObject*	Clone(const Engine::_vec3* pPos = nullptr);
	virtual void			LoadData(HANDLE hFile);
};

#endif // Bullet_h__