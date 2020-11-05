#ifndef Resources_h__
#define Resources_h__

#include "Engine_Defines.h"
#include "Base.h"
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CResources : public CComponent
{
protected:
	explicit CResources(void);
	explicit CResources(const CResources& rhs);
	virtual ~CResources(void);

public:
	virtual HRESULT			Late_Initialize() { return S_OK; };

protected:
	// 그래픽 장치가 필요한데 접근하기가 만만찮아서 추가.
	LPDIRECT3DDEVICE9		m_pGraphicDev = nullptr;
	_bool					m_bClone = false;

public:
	virtual HRESULT			Attach(CGameObject* pObj, COMPONENTID com_ID);
protected:
	virtual void			freeMem(void);
};

END

#endif // Resources_h__
