#ifndef TimerMgr_h__
#define TimerMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)
class CTimer;
class ENGINE_DLL CTimerMgr : public CBase
{
	DECLARE_SINGLETON(CTimerMgr)

private:
	explicit CTimerMgr(void);
	virtual ~CTimerMgr(void);

public:
	void		Set_TimeDelta(const _int iTimerTag);
	_float		Get_TimeDelta(const _int iTimerTag);
	HRESULT		Ready_Timer(const _int iTimerTag);
	void		Initialize_Timer(const _int iTimerSize);
private:
	CTimer*	Find_Timer(const _int iTimerTag);

private:
	bool				m_bInitialized;
	vector<CTimer*>		m_vecTimer;

public:
	virtual void freeMem(void);
};

END
#endif // TimerMgr_h__
