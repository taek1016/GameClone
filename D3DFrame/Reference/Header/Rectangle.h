#ifndef RcCol_h__
#define RcCol_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcCol : public CVIBuffer
{
private:
	explicit			CRcCol(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit			CRcCol(const CRcCol& rhs);
	virtual				~CRcCol(void);

public:
	virtual HRESULT		Initialize_Buffer(void) override;


public:
	static CRcCol*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CResources* Clone(void) override;
};

END
#endif // RcCol_h__