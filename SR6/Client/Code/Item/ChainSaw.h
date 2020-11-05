#ifndef ChainSaw_h__
#define ChainSaw_h__

#include "WeaponBase.h"

class CChainSaw : public Engine::CWeaponBase
{
private:
	explicit						CChainSaw(void);
	explicit						CChainSaw(const CChainSaw& rhs);
	virtual							~CChainSaw(void);

public:
	virtual HRESULT					Late_Initialize() override;
	virtual HRESULT					Initialize_GameObject() override;
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Attack(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject() override;

private:
	Engine::_float					m_fAttackCool = 0.2f;
	Engine::_float					m_fCurTime = 0.2f;
	Engine::_float					m_fAttAction = 0.f;
	Engine::_float					m_fMaxAction = 2.f;
	Engine::_bool					m_bAttack = false;

	Engine::CCollider*				m_pCollider = nullptr;
	Engine::CTransform*				m_pTransform = nullptr;
	Engine::CTexture*				m_pTexture = nullptr;

public:
	static CChainSaw*				Create(void);
	virtual Engine::CGameObject*	Clone(const Engine::_vec3* pPos) override;
	virtual void					LoadData(HANDLE hFile) override;

private:

};
#endif // ChainSaw_h__
