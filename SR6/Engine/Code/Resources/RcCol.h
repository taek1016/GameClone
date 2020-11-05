#ifndef RcCol_h__
#define RcCol_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcCol : public CVIBuffer
{
private:
	explicit			CRcCol(void);
	explicit			CRcCol(const CRcCol& rhs);
	virtual				~CRcCol(void);

public:
	HRESULT				Initialize_Buffer(void);


public:
	static CRcCol*		Create(void);
	virtual CResources* Clone(void) override;
};

END

#endif // RcCol_h__
