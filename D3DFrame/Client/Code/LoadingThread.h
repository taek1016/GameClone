#ifndef LoadingThread_h__
#define LoadingThread_h__

#include "Base.h"

class CLoading : public CBase
{
private:
	explicit						CLoading(void);
	virtual							~CLoading(void);

public:
	LOADINGID						Get_LoadingID(void) const { return m_eLoadingID; }
	CRITICAL_SECTION*				Get_Crt(void) { return &m_Crt; }
	Engine::_bool					Get_Finish(void) const { return m_bFinish; }
	const Engine::_tchar*			Get_LoadString(void) { return m_szLoading; }
	Engine::_float					Get_Percent(void) { return m_iCurCnt / static_cast<Engine::_float>(m_iMaxCnt); }

	HRESULT							Initialize_LoadingThread(LOADINGID eLoading);
	Engine::_uint					Loading_Data(void);
	Engine::_uint					Loading_Field(void);
	Engine::_uint					Loading_Dungeon(void);

	void							Loading_DataCount(const Engine::_tchar* pPath);

public:
	static Engine::_uint CALLBACK	Thread_Main(void* pArg);

private:
	LOADINGID						m_eLoadingID;
	HANDLE							m_hThread;
	CRITICAL_SECTION				m_Crt;

	Engine::_bool					m_bFinish;
	Engine::_tchar					m_szLoading[256];

	Engine::_int					m_iCurCnt;
	Engine::_int					m_iMaxCnt;

public:
	static CLoading*				Create(LOADINGID eLoading);

private:
	inline virtual void				Free(void) override;

};

#endif // LoadingThread_h__
