#ifndef Observer_h__
#define Observer_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CContent;
class ENGINE_DLL CObserver : public CBase
{
private:
	explicit			CObserver(void);
	virtual				~CObserver(void);

public:
	void Notify(_int iMessage, void* pData);
	void Subscribe(CContent* pContent);
	void UnSubscribe(CContent* pContent);

private:
	list<CContent*>		m_ObserverList;

public:
	static	CObserver*	Create(void);

protected:
	virtual void		freeMem(void);
};

END

#endif // Observer_h__
