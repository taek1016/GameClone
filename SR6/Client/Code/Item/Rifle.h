#ifndef Rifle_h__
#define Rifle_h__

#include "WeaponBase.h"

class CRifle : public Engine::CWeaponBase
{
private:
	explicit				CRifle(void);
	explicit				CRifle(const CRifle& rhs);
	virtual					~CRifle(void);

public:
	virtual HRESULT			Late_Initialize() override;
	virtual HRESULT			Initialize_GameObject() override;
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void			Attack(const Engine::_float& fTimeDelta) override;
	
private:
	Engine::_float			m_fShotCool = 0.15f;
	Engine::_float			m_fCurTime = 0.15f;

	Engine::CTexture*		m_pTexture = nullptr;

	Engine::_bool			m_bAttack = false;
	Engine::_float			m_fAttAction = 0.f;
	Engine::_float			m_fMaxAction = 3.f;

public:
	static CRifle*			Create(void);
	virtual CGameObject*	Clone(const Engine::_vec3 * pPos = nullptr) override;
	virtual void			LoadData(HANDLE hFile) override;
	virtual void			Render_GameObject() override;
};

#endif // Rifle_h__