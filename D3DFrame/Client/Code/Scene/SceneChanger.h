#ifndef SceneChanger_h__
#define SceneChanger_h__

#include "Scene.h"

BEGIN(Engine)
class CTexture;
class CRcTex;
END

class CLoadingBar;

class CSceneChanger : public Engine::CScene
{
private:
	explicit				CSceneChanger(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CSceneChanger(void);

public:
	virtual HRESULT			Initialize_Scene(void);
	virtual Engine::_int	Update_Scene(const Engine::_float& fTimeDelta);
	virtual void			Render_Scene(void);

	void					SetUp_Scene(LOADINGID eID, const Engine::_tchar* pName);
private:
	class CLoading*			m_pLoading;

	LOADINGID				m_eLoadingID;

	Engine::CTexture*		m_pTexture;
	Engine::CRcTex*			m_pBuffer;

	Engine::_matrix			m_matWorld;

public:
	static CSceneChanger*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void			Free(void) override;
};

#endif // SceneChanger_h__
