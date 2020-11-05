#ifndef TriCol_h__
#define TriCol_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTriCol : public CVIBuffer
{
private:
	explicit				CTriCol(void);
	explicit				CTriCol(const CTriCol& rhs);
	virtual					~CTriCol(void);

public:
	HRESULT					Initialize_Buffer(void);

public:
	static CTriCol*			Create(void);
	virtual CResources*		Clone(void) override;

private:
	inline virtual void		freeMem();
};

END

#endif // TriCol_h__
