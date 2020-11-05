#ifndef ObserverMgr_h__
#define ObserverMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)
class CContent;
class CObserver;
class ENGINE_DLL CObserverMgr : public CBase
{
	DECLARE_SINGLETON(CObserverMgr)

private:
	explicit	CObserverMgr(void);
	virtual		~CObserverMgr(void);

public:
	HRESULT		Add_Observer(const _tchar* pObserverKey, CObserver* pObserver);
	void		Notify(const _tchar* pObserverKey, _int iMessage, void* pData);
	void		Subscribe(const _tchar* pObserverKey, CContent* pContent);
	void		Unsubscribe(const _tchar* pObserverKey, CContent* pContent);

private:
	map<const _tchar*, CObserver*>	m_mapObserver;

private:
	inline virtual void freeMem(void);
};

END

#endif // ObserverMgr_h__
