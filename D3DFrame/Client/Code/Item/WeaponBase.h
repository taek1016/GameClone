#ifndef WeaponBase_h__
#define WeaponBase_h__

#include "ItemBase.h"
BEGIN(Engine)
class CSphereCollider;
END
class CCharacterBase;
class CWeaponBase : public CItemBase
{
protected:
	explicit						CWeaponBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CWeaponBase(const CWeaponBase& rhs);
	virtual							~CWeaponBase(void);

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

	void							AttackAct(void);
	void							Cancel_Attack(void);
	void							Update_Matrix(const Engine::_matrix* pWorldMat);
	void							Set_Damage(const Engine::_int iDamage);
	void							Set_Target(CCharacterBase* pTargetStatCom);

	virtual void					Set_ColliderMat(const Engine::_matrix* pWorld, const Engine::_matrix* pBone = nullptr, const Engine::_vec3 * pStartPos = &Engine::_vec3(0.f, 0.f, 0.f)) override;

protected:
	HRESULT							setUp_ConstantTable(LPD3DXEFFECT & pEffect);
	virtual void					attack(void);
	void							initialize_Colliders(const Engine::_float& fLength, const Engine::_float& fSingleRadius);

	virtual Engine::_bool			check_Collide(void);

	Engine::_int					m_iDamage;

	Engine::_float					m_fLength;
	Engine::_float					m_fSingleSphereRadius;

	Engine::_bool					m_bCollided;
	Engine::_bool					m_bGiveDamage;
	Engine::_bool					m_bAttackOrder;

	Engine::COLLTYPE				m_eColType;
	list<Engine::CSphereCollider*>	m_listCollider;

	Engine::CStaticMesh*			m_pMesh;
	CCharacterBase*					m_pTarget;

	const Engine::_matrix*			m_pMatParentBone;
	const Engine::_matrix*			m_pMatParentWorld;

protected:
	inline virtual void				Free(void) override;

};

#endif // WeaponBase_h__
