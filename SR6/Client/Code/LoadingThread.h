#ifndef Loading_h__
#define Loading_h__

#include "Base.h"

class CLoading : public CBase
{
private:
	explicit						CLoading(void);
	virtual							~CLoading(void);

public:
	LOADINGID						Get_LoadingID(void) const { return m_eLoading; }
	CRITICAL_SECTION*				Get_Crt(void) { return &m_Crt; }
	Engine::_bool					Get_Finish(void) const { return m_bFinish; }
	const Engine::_tchar*			Get_LoadString(void) { return m_szLoading; }
	Engine::_float					Get_Percent(void) { return m_iCurCnt / static_cast<Engine::_float>(m_iMaxCnt); }

public:
	static Engine::_uint CALLBACK	Thread_Main(void* pArg);

public:
	HRESULT							Ready_Loading(LOADINGID eLoading);
	Engine::_uint					Loading_ForStage(void);

private:
	HANDLE							m_hThread;

	CRITICAL_SECTION				m_Crt;
	LOADINGID						m_eLoading;
	Engine::_bool					m_bFinish;
	Engine::_tchar					m_szLoading[256];

	Engine::_int					m_iCurCnt;
	Engine::_int					m_iMaxCnt;

public:
	static CLoading*				Create(LOADINGID eLoading);

private:
	virtual void					freeMem(void);

};


#endif // Loading_h__
