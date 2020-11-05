#ifndef RCTEX_h__
#define RCTEX_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcTex : public CVIBuffer
{
private:
	explicit			CRcTex(void);
	explicit			CRcTex(const CRcTex& rhs);
	virtual				~CRcTex(void);

public:
	HRESULT				Initialize_Buffer(void);

public:
	static CRcTex*		Create(void);
	virtual CResources* Clone(void) override;
};

END

#endif // RCTEX_h__