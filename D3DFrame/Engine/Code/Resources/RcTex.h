#ifndef RcTex_h__
#define RcTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcTex : public CVIBuffer
{
private:
	explicit			CRcTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit			CRcTex(const CRcTex& rhs);
	virtual				~CRcTex(void);

public:
	virtual HRESULT		Initialize_Buffer(void) override;

public:
	static CRcTex*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CResources* Clone(void) override;
};

END
#endif // RcTex_h__