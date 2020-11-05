#ifndef Logo_h__
#define Logo_h__

#include "Scene.h"

class CBackground;
class CLoadingBar;

class CLogo : public Engine::CScene
{
private:
	explicit				CLogo(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CLogo(void);

public:
	virtual HRESULT			Initialize_Scene(void);
	virtual Engine::_int	Update_Scene(const Engine::_float& fTimeDelta);
	virtual void			Render_Scene(void);

private:
	class CLoading*			m_pLoading;
	CBackground*			m_pBackground;
	CLoadingBar*			m_pLoadingBar;

public:
	static CLogo*			Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void			Free(void) override;
};

#endif // Logo_h__
