#ifndef StaticCamera_h__
#define StaticCamera_h__

#include "Camera.h"

BEGIN(Engine)
class CTransform;
END

class CStaticCamera : public Engine::CCamera
{
private:
	explicit CStaticCamera(void);
	virtual ~CStaticCamera(void);

public:
	virtual HRESULT		Late_Initialize(const Engine::_vec3* pEye,
										const Engine::_vec3* pAt,
										const Engine::_vec3* pUp);
	virtual Engine::_int Update_Component(const Engine::_float& fTimeDelta) override;

private:
	void	Mouse_Move(const Engine::_float & fTimeDelta);
	void	Target_Renewal(const Engine::_float& fTimeDelta);

private:
	Engine::_float			m_fDistance = 1.f;
	Engine::_float			m_fAngle = 0.f;

public:
	static CStaticCamera*		Create(const Engine::_float& fFovY,
										const Engine::_float& fAspect,
										const Engine::_float& fNear,
										const Engine::_float& fFar);

private:
	virtual void freeMem(void) override;

};


#endif // StaticCamera_h__
