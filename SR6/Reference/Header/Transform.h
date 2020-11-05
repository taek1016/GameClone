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

	// 게터, 셋터
public:
	const _vec3*		Get_Info(INFO eType);
	void				Get_Info(INFO eType, _vec3* pInfo);
	const _vec3*		Get_Scale() const { return &m_vScale; }

	const _matrix*		Get_World(void) const { return &m_matWorld; }
	_vec3*				Get_Angle(void)			{ return &m_vAngle; }
	void				Move_Pos(const _vec3* const pDir);
	void				Rotation(ROTATION eType, const _float& fAngle);

	const _matrix*		Compute_LookAtTarget(const _vec3* pTargetPos);
	void				Chase_Target(const _vec3* pTargetPos, const _float& fSpeed);

	void				Set_Scale(const _float& fX, const _float& fY, const _float& fZ);
	void				Set_Scale(const _vec3* pScale);

	void				Set_Pos(const _float& fX, const _float& fY, const _float& fZ);
	void				Set_Pos(const _vec3* pPos);

	void				Set_Look(const _vec3* pLook);

	void				Set_Angle(const _vec3* pAngle);
	void				Set_Angle(ROTATION eType, const _float& fAngle);

	void				SetParent(CTransform* parent);

public:
	virtual HRESULT		Late_Initialize() { return S_OK; };
	virtual HRESULT		Initialize_Component(void);
	virtual _int		Update_Component(const _float& fTimeDelta);

	virtual HRESULT		Attach(CGameObject* pObj, COMPONENTID com_ID = ID_DYNAMIC);

	virtual void		LoadData(HANDLE hFile)override;
private:
	_vec3				m_vInfo[INFO::INFO_END];
	_vec3				m_vScale;
	_vec3				m_vAngle;
	_matrix				m_matWorld;

	CTransform*			m_pParentTransform = nullptr;
public:
	static CTransform*	Create(void);
	virtual CComponent*	Clone()override;
};
END
#endif // Transform_h__
