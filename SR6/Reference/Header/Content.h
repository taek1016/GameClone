#ifndef Content_h__
#define Content_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CContent : public CBase
{
protected:
	explicit CContent(void);
	virtual ~CContent(void);

public:
	virtual void Update_Content(_int iMessage, void* pData) PURE;

protected:
	inline virtual void freeMem() PURE;
};

END

#endif // Content_h__
