#ifndef Rigidbody_h__
#define Rigidbody_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CRigidBody : public CComponent
{
private:
	explicit	CRigidBody(void);
	explicit	CRigidBody(const CRigidBody& rhs);
	virtual		~CRigidBody(void);

public:
	virtual HRESULT			Late_Initialize();
	virtual HRESULT			Initialize_Component();
	virtual _int			Update_Component(const _float& fTimeDelta);
	virtual void			LoadData(HANDLE hFile);

	virtual HRESULT			Attach(CGameObject* pObj, COMPONENTID eID);
	
	void					SetJump() { m_bJump = true; }
	void					CancleJump() { m_bJump = false; }
	_bool					Get_Jump() { return m_bJump; }

	_float					Get_Height(const _float& fTimeDelta);
private:
	static const _float		m_fGravity;
	
	_bool					m_bJump = false;
	GRAVITY_INFO			m_tGravityInfo;

	class CTransform*		m_pTransform = nullptr;

public:
	virtual CComponent*		Clone(void) { return nullptr; }
	static CRigidBody*		Create(void);
};

END

#endif // Rigidbody_h__
