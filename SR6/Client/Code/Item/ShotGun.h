#ifndef ShotGun_h__
#define ShotGun_h__

#include "WeaponBase.h"

class CShotGun : public Engine::CWeaponBase
{
private:
	explicit				CShotGun(void);
	explicit				CShotGun(const CShotGun& rhs);
	virtual					~CShotGun(void);

public:
	virtual HRESULT			Late_Initialize() override;
	virtual HRESULT			Initialize_GameObject() override;
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void			Attack(const Engine::_float& fTimeDelta) override;
	
private:
	Engine::_float			m_fShotCool = 1.f;
	Engine::_float			m_fCurTime = 1.f;

	Engine::CTexture*		m_pTexture = nullptr;

	Engine::_bool			m_bAttack = false;
	Engine::_float			m_fAttAction = 0.f;
	Engine::_float			m_fMaxAction = 16.f;

public:
	static CShotGun*			Create(void);
	virtual CGameObject*	Clone(const Engine::_vec3 * pPos = nullptr) override;
	virtual void			LoadData(HANDLE hFile) override;
	virtual void			Render_GameObject() override;
};

#endif // ShotGun_h__