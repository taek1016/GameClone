#ifndef RigidBody_h__
#define RigidBody_h__

#include "Component.h"

class CRigidBody : public Engine::CComponent
{
private:
	explicit					CRigidBody(const Engine::_float& fDefaultPower, const Engine::_float& fMaxPower);
	explicit					CRigidBody(const CRigidBody& rhs);
	virtual						~CRigidBody(void) = default;

public:
	virtual Engine::_int		Update_Component(const Engine::_float& fTimeDelta) override;
	virtual HRESULT				Attach(const Engine::_tchar* pKey, Engine::CGameObject* pObj, Engine::COMPONENTID com_ID) override;
	void						Activate(const Engine::_bool& bActivate);
	const Engine::_float		Get_YPos(void);

private:
	Engine::CTransform*			m_pTargetTransform;

	Engine::_bool				m_bActivated;
	Engine::_float				m_fAccTime;
	Engine::_float				m_fPower;

	Engine::_float				m_fDefaultPower;
	Engine::_float				m_fMaxPower;

public:
	static CRigidBody*			Create(const Engine::_float& fDefaultPower, const Engine::_float& fMaxPower);
	virtual Engine::CComponent*	Clone(void) override;

private:
	inline virtual void			Free(void) override;
};

#endif // RigidBody_h__
