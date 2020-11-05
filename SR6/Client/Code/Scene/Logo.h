#ifndef Logo_h__
#define Logo_h__

#include "Scene.h"

class CLoading;
class CLoadBar;
class CBackGround;

class CLogo : public Engine::CScene
{
private:
	explicit CLogo(void);
	virtual ~CLogo(void);

public:
	virtual HRESULT			Initialize_Scene(void) override;
	virtual Engine::_int	Update_Scene(const Engine::_float& fTimeDelta) override;
	virtual void			Render_Scene(void) override;

private:
	Engine::_int			m_iCurCount;
	Engine::_int			m_iMaxCount;

	HRESULT					Initialize_Resource(RESOURCEID eMAX);
	HRESULT					Initialize_GameObject();

	CLoading*				m_pLoading = nullptr;
	CLoadBar*				m_pLoadBar = nullptr;
	CBackGround*			m_pBackGround = nullptr;

public:
	static CLogo*			Create(void);

private:
	virtual void			freeMem(void) override;

};

#endif // Logo_h__
