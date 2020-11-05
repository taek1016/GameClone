#ifndef Camera_h__
#define Camera_h__

#include "GameObject.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CCamera : public CComponent
{
protected:
	explicit CCamera(void);
	virtual ~CCamera(void);

public:
	const _matrix*		Get_ViewSpace(void) { return &m_matView; }
	const _matrix*		Get_Projection(void) { return &m_matProj; }

	const _vec3*		Get_At() const { return &m_vAt; }
	const _vec3*		Get_Eye() const { return &m_vEye; }

	void				Shake_Camera(int range);

	virtual HRESULT		Late_Initialize(const _vec3* pEye,
										const _vec3* pAt,
										const _vec3* pUp) PURE;

	virtual HRESULT		Initialize_Camera(const _float& fFovY,
											const _float& fAspect,
											const _float& fNear,
											const _float& fFar);
	void				Set_Distance(const _float& fDistance);
	void				Set_Transform(CTransform* pTransform);
	virtual _int		Update_Component(const _float& fTimeDelta) override PURE;

	void				Ready_NormalView(LPDIRECT3DDEVICE9 pGraphicDev);
	void				Rebound_Camera();

protected:
	CTransform*			m_pTargetTransform = nullptr;
	_vec3				m_vEye, m_vAt, m_vUp;
	_float				m_fFovY, m_fAspect, m_fNear, m_fFar;
	_matrix				m_matView, m_matProj;
	_float				m_fDistance;

	_float				m_fShakeOffsetX = 0;
	_float				m_fShakeOffsetY = 0;
	_int				m_iCurBoundInterval = 0;

protected:
	inline virtual void	freeMem(void) override;
};

END
#endif // Camera_h__
