#ifndef __LOGO_H__
#define __LOGO_H__

#include "Scene.h"
class CLogo : public CScene
{
protected:
	CLogo();

public:
	virtual ~CLogo();

public:
	// CScene을(를) 통해 상속됨
	virtual int		Update() override;
	virtual void	LateUpdate() override;
	virtual void	Render() override;

	static	CLogo*	Create();

private:
	virtual HRESULT Initialize() override;
	virtual void	Release() override;

	static unsigned __stdcall LoadTextures(void* pParam);

private:
	HANDLE	m_hLoadingThread;

	static	bool m_bLogoLoading;
};

#endif // __LOGO_H__