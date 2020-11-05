#ifndef MainApp_h__
#define MainApp_h__


class CMainApp : public CBase
{
private:	
	explicit CMainApp(void);
	virtual ~CMainApp(void);

public:
	HRESULT			Ready_MainApp(void);
	Engine::_int	Update_MainApp(const Engine::_float fTimeDelta);
	void			Render_MainApp(void);

private:
	HRESULT			Initialize_DefaultSetting(void);
	HRESULT			Initialize_Scene(void);

	Engine::_int	m_iExit = 0;

public:
	static CMainApp*	Create(void);

private:
	virtual			void freeMem(void);
};


#endif // MainApp_h__
