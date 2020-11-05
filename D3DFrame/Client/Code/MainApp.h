#ifndef MainApp_h__
#define MainApp_h__

#include "Base.h"

class CMainApp : public CBase
{
private:
	explicit				CMainApp(void);
	virtual					~CMainApp(void);

public:
	HRESULT					Initialize_MainApp(void);
	Engine::_int			Update_MainApp(const Engine::_float& fTimeDelta);
	void					Render_MainApp(void);

private:
	HRESULT					initialize_DefaultSetting(void);
	HRESULT					initialize_Scene(void);

	Engine::_int			m_iExit = 0;

	LPDIRECT3DDEVICE9		m_pGraphicDev;

public:
	static CMainApp*		Create(void);

private:
	inline virtual void		Free(void);
};


#endif // MainApp_h__
