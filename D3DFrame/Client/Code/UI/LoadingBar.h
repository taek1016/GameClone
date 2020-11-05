#ifndef LoadingBar_h__
#define LoadingBar_h__

#include "GameObject.h"

class CLoading;
class CLoadingBar : public Engine::CGameObject
{
	enum LOADING_BAR { LOADBAR_BACKGROUND, LOADBAR_SPARK, LOADBAR_END };

private:
	explicit						CLoadingBar(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CLoadingBar(void);

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

private:
	void							set_LoadingThread(CLoading* pLoadingThread);

	Engine::CTransform*				m_pTransformCom[LOADBAR_END];
	CLoading*						m_pLoadingThread;
	Engine::CTexture*				m_pTexture[LOADBAR_END];
	Engine::CRcTex*					m_pBuffer[LOADBAR_END];

public:
	static CLoadingBar*				Create(LPDIRECT3DDEVICE9 pGraphicDev, CLoading* pLoadingThread);
	virtual Engine::CGameObject*	Clone(void) override;

private:
	inline virtual void				Free(void) override;
};

#endif // LoadingBar_h__