#ifndef Resources_h__
#define Resources_h__

#include "Engine_Defines.h"
#include "Base.h"
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CResources : public CComponent
{
protected:
	explicit				CResources(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CResources(const CResources& rhs);
	virtual					~CResources(void);

public:
	virtual HRESULT			Late_Initialize() { return S_OK; };

protected:
	// �׷��� ��ġ�� �ʿ��ѵ� �����ϱⰡ �������Ƽ� �߰�.
	LPDIRECT3DDEVICE9		m_pGraphicDev = nullptr;
	_bool					m_bClone = false;

public:
	virtual HRESULT			Attach(const _tchar* pKey, CGameObject* pObj, COMPONENTID com_ID);

protected:
	virtual void			Free(void) override;
};

END

#endif // Resources_h__