#ifndef SingleEvent_h__
#define SingleEvent_h__

#include "Engine_Defines.h"
#include "Base.h"

class CSingleEvent : public CBase
{
private:
	explicit				CSingleEvent(void);
	virtual					~CSingleEvent(void);

public:
	void					Update_Event(const Engine::_float& fTimeDelta);
	void					Activate_Event();

private:
	Engine::_bool			m_bActivate;

	Engine::_int			m_iCurEvent;
	Engine::_int			m_iMaxEvent;

	Engine::_float			m_fCurTime;
	Engine::_float			m_fEventTime;

public:
	static CSingleEvent*	Create(void);

private:
	inline virtual void		freeMem();
};
#endif // SingleEvent_h__
