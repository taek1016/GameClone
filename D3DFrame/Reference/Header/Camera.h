#ifndef Camera_h__
#define Camera_h__

#include "GameObject.h"

#include "Component.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CCamera : public CGameObject
{
protected:
	explicit			CCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit			CCamera(const CCamera& rhs);
	virtual				~CCamera(void);

	// Getter, Setter
public:
	const _matrix*		Get_ViewSpace(void);
	const _matrix*		Get_Projection(void);

	const _vec3*		Get_At() const;
	const _vec3*		Get_Eye() const;

	virtual void		Set_Transform(CTransform* pTransform);
	void				Set_Distance(const _float& fDistance);

public:
	virtual HRESULT		Late_Initialize(const _vec3* pEye,
										const _vec3* pAt,
										const _vec3* pUp) PURE;

	virtual HRESULT		Initialize_Camera(const _float& fFovY,
										const _float& fAspect,
										const _float& fNear,
										const _float& fFar);

	virtual _int		Update_GameObject(const _float& fTimeDelta) PURE;

protected:
	virtual void		target_Renewal(const Engine::_float& fTimeDelta) PURE;
	void				set_ProjData(const _float& fFovY, const _float& fAspect, const _float& fNear, const _float& fFar);
	void				set_ViewData(const _vec3* pEye, const _vec3* pAt, const _vec3* pUp);

protected:
	CTransform*			m_pTargetTransform = nullptr;
	_vec3				m_vEye, m_vAt, m_vUp;
	_float				m_fFovY, m_fAspect, m_fNear, m_fFar;
	_matrix				m_matView, m_matProj;
	_float				m_fDistance;

protected:
	inline virtual void	Free(void) override;
};

END
#endif // Camera_h__