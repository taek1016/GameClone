#ifndef ControllerBase_h__
#define ControllerBase_h__

#include "Component.h"

BEGIN(Engine)

class CGameObject;
class CTransform;
class CDynamicMesh;

class ENGINE_DLL CControllerBase : public CComponent
{
protected:
	explicit			CControllerBase(CGameObject* pTarget);
	explicit			CControllerBase(const CControllerBase& rhs);
	virtual				~CControllerBase(void);

public:
	virtual HRESULT		Late_Initialize(void) override;
	virtual _int		Update_Component(const _float& fTimeDelta) override PURE;

protected:
	void				get_TargetLook(void);

	_vec3				m_vDir;

	CGameObject*		m_pTarget;
	CTransform*			m_pTargetTransform;
	CDynamicMesh*		m_pTargetDynamicMesh;

private:
	inline virtual void	Free(void);
};

END
#endif // ControllerBase_h__
