#ifndef DynamicCamera_h__
#define DynamicCamera_h__

#include "Camera.h"

BEGIN(Engine)

END

class CDynamicCamera : public Engine::CCamera
{
private:
	explicit				CDynamicCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CDynamicCamera(void);

public:
	virtual HRESULT			Late_Initialize(const Engine::_vec3* pEye,
		const Engine::_vec3* pAt,
		const Engine::_vec3* pUp) override;

	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;

	void					Set_Speed(const Engine::_float& fSpeed);

private:
	virtual void			target_Renewal(const Engine::_float& fTimeDelta) override;

	Engine::_float			m_fSpeed;

public:
	static CDynamicCamera*	Create(const Engine::_float& fFovY, const Engine::_float& fAspect, const Engine::_float& fNear, const Engine::_float& fFar);
	virtual CGameObject*	Clone() override;
};

#endif // DynamicCamera_h__
