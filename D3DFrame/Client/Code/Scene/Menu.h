#ifndef Menu_h__
#define Menu_h__

#include "Scene.h"

class CBackground;
class CButton;

class CMenu : public Engine::CScene
{
	enum MENU_BUTTON		{ BUTTON_START, BUTTON_EXIT, BUTTON_END};

private:
	explicit				CMenu(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CMenu(void);

public:
	virtual HRESULT			Initialize_Scene(void);
	virtual Engine::_int	Update_Scene(const Engine::_float& fTimeDelta);
	virtual void			Render_Scene(void);

private:
	CBackground*			m_pBackground;
	CButton*				m_pMenuButton[BUTTON_END];

	Engine::_bool			m_bStartClicked;
	Engine::_bool			m_bEndClicked;
	Engine::_float			m_fVolume;

public:
	static CMenu*			Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void			Free(void) override;

};

#endif // Menu_h__