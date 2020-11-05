#ifndef Collider_h__
#define Collider_h__

#include "Engine_Defines.h"
#include "Resources.h"

BEGIN(Engine)
class CTransform;
class ENGINE_DLL CCollider : public CResources
{
protected:
	explicit	CCollider(void);
	explicit	CCollider(const CCollider& rhs);
	virtual		~CCollider(void);

public:
	virtual _int			Update_Component(const _float& fTimeDelta);
	virtual HRESULT			Late_Initialize();
	virtual HRESULT			Initialize_Component() PURE;
	virtual HRESULT			Attach(CGameObject* pObj, COMPONENTID com_ID);

	virtual void			Render_Collider() PURE;

	void					Set_Collision(const COLLISION& eIsCollision, const _float& fDamage = 0)
	{
		m_eIsCollision = eIsCollision;
		m_fDamage = fDamage;
	}
	const COLLIDER_TYPE		Get_ColType() const { return m_eColType; }
	const COLLISION			Get_IsCol() const { return m_eIsCollision; }
	const _float			Get_Damage() const { return m_fDamage; }
	const _vec3*			Get_Pos() const { return &m_vPos; }

	virtual bool			Is_Collide(CCollider* pOther, _float* pDistance = nullptr) PURE;
	void					Set_Transform(CTransform* pTransform);

protected:
	CTransform*				m_pTransform = nullptr;
	_bool					m_bDead = false;
	COLLIDER_TYPE			m_eColType = COLLISION_END;
	COLLISION				m_eIsCollision = COLL_END;
	_float					m_fDamage = 0.f;
	_vec3					m_vPos;

public:
	virtual CComponent*		Clone(void) PURE;

protected:
	virtual void			freeMem(void);
};

END

#endif // Collider_h__