#ifndef CameraMgr_h__
#define CameraMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

#include "Camera.h"

BEGIN(Engine)

class CGameObject;
class CCamera;
class CTransform;

class ENGINE_DLL CCameraMgr : public CBase
{
	DECLARE_SINGLETON(CCameraMgr)

private:
	explicit						CCameraMgr(void);

public:
	virtual							~CCameraMgr(void);

public:
	const _int						Get_CurCamera(void);
	const _vec3*					Get_At() const;
	const _vec3*					Get_Eye() const;

	const _matrix*					Get_ViewSpace(void);
	const _matrix*					Get_Projection(void);	

	void							Set_Window(const _float& fWidth, const _float& fHeight);
	void							Initialize_CameraMgr(const _int& iMaxCamera);
	void							Late_Initialize(const _vec3* pEye,
													const _vec3* pAt,
													const _vec3* pUp);

	_int							Update_Camera(const _float& fTimeDelta);

	HRESULT							Set_Object(CGameObject* pObj);
	void							Set_CurCamera(const _int& iCameraTag) { m_iCurCamera = iCameraTag; }

	void							Ready_NormalView();

	void							Make_Billboard(CTransform* pTransform);
	_matrix							Get_Billboard(CTransform* pTransform);

	template<typename T>
	T* Add_Camera(const _int& iCameraTag,
				  const _float& fFovY,
				  const _float& fAspect,
				  const _float& fNear,
				  const _float& fFar,
				  const _float& fDistance = 1.f)
	{
		T* pInstance = T::Create(fFovY, fAspect, fNear, fFar);

		pInstance->Set_Distance(fDistance);

		m_vecCamera[iCameraTag] = pInstance;

		return pInstance;
	}

private:
	_int							m_iMaxCamera;
	_int							m_iCurCamera;

	_float							m_fWidth;
	_float							m_fHeight;

	CGameObject*					m_pTarget = nullptr;
	LPDIRECT3DDEVICE9				m_pGraphicDev = nullptr;
	vector<CCamera*>				m_vecCamera;

private:
	inline virtual void				Free() override;
};

END

#endif // CameraMgr_h__