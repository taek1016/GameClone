#ifndef Title_h__
#define Title_h__

#include "Scene.h"

class CBackGround;
class CTitleText;

class CTitle : public Engine::CScene
{
private:
	explicit	CTitle(void);
	explicit	CTitle(const CTitle& rhs);
	virtual		~CTitle(void);

public:
	virtual HRESULT			Initialize_Scene(void) override;
	virtual Engine::_int	Update_Scene(const Engine::_float& fTimeDelta) override;
	virtual void			Render_Scene(void) override;

private:
	CBackGround*			m_pBackGround = nullptr;
	CTitleText*				m_pText = nullptr;
public:
	static CTitle*			Create(void);

private:
	virtual void			freeMem(void) override;
};

#endif // Title_h__
