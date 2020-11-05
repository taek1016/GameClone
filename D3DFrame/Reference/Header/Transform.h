#ifndef Transform_h__
#define Transform_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform : public CComponent
{
private:
	explicit			CTransform(void);
	explicit			CTransform(const CTransform& rhs);
	virtual				~CTransform(void);

public:
	virtual HRESULT		Late_Initialize(void) override;
	virtual HRESULT		Initialize_Component(void) override;
	virtual _int		Update_Component(const _float& fTimeDelta) override;

	void				Move_Pos(const _vec3* const pDir);
	void				Rotation(ROTATION eType, const _float& fAngle);

	void				Compute_LookAtTarget(const _vec3* pTargetPos);
	//void				Chase_Target(const _vec3* pTargetPos, const _float& fSpeed);

	// Getter, Setter
public:
	const _vec3*		Get_Info(const INFO& eInfoType) const;
	const _vec3*		Get_Scale(void) const;
	const _vec3*		Get_Angle(void) const;

	const _matrix*		Get_World(void) const;
	
	void				Set_Info(const INFO& eInfoType, const _vec3* pVec);
	void				Set_Scale(const _vec3* pScale);
	void				Set_Angle(const ROTATION& eRotID, const _float& fAngle);
	void				Set_Angle(const _vec3* pAngle);

	void				Set_WorldMatrix(const _matrix * matWorld);

private:
	_vec3				m_vInfo[INFO::INFO_END];
	_vec3				m_vScale;
	_vec3				m_vAngle;

	_matrix				m_matWorld;

public:
	static CTransform*	Create(void);
	virtual CComponent*	Clone(void) override;
};

END
#endif // Transform_h__
