#ifndef FirstPersonView_h__
#define FirstPersonView_h__

#include "Camera.h"

class CFirstPersonView : public Engine::CCamera
{
private:
	explicit					CFirstPersonView(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit					CFirstPersonView(const CFirstPersonView& rhs);
	virtual						~CFirstPersonView(void);

public:
	virtual HRESULT				Late_Initialize(const Engine::_vec3* pEye,
												const Engine::_vec3* pAt,
												const Engine::_vec3* pUp);

	virtual Engine::_int		Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void				Set_Transform(Engine::CTransform* pTransform) override;

private:
	void						get_FrontShot(const Engine::_float& fTimeDelta);
	void						get_TargetBehind(const Engine::_float& fTimeDelta);
	void						key_Input(const Engine::_float& fTimeDelta);
	virtual void				target_Renewal(const Engine::_float& fTimeDelta) override;

	Engine::_float				m_fAngle;
	Engine::_float				m_fAngleX;
	Engine::_float				m_fAngleY;
	Engine::_float				m_fDistance;
	
	Engine::_vec3				m_vRotAxis;
	Engine::_vec3				m_vTargetEye;
	Engine::_vec3				m_vPreviousEye;

	Engine::_bool				m_bAutoCamera;

public:
	static CFirstPersonView*	Create(const Engine::_float& fFovY, const Engine::_float& fAspect, const Engine::_float& fNear, const Engine::_float& fFar);
	virtual CGameObject*		Clone() override;
};
#endif // FirstPersonView_h__
