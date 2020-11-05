#ifndef EventMgr_h__
#define EventMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

class CSingleEvent;
class CEventMgr : public CBase
{
	DECLARE_SINGLETON(CEventMgr)

private:
	explicit							CEventMgr(void);
	virtual								~CEventMgr(void);

public:
	void								Register_Event(const Engine::_tchar* pKey, CSingleEvent* pEvent);
	void								Update_Event(const Engine::_float& fTimeDelta);
	void								Activate_Mgr(const Engine::_tchar* pKey);

private:
	map<const _tchar*, CSingleEvent*>	m_mapEvent;

private:
	inline virtual void					freeMem() override;
};

#endif // EventMgr_h__
