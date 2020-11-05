#ifndef Background_h__
#define Background_h__

#include "GameObject.h"

class CBackground : public Engine::CGameObject
{
private:
	explicit						CBackground(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CBackground(const CBackground& rhs);
	virtual							~CBackground(void);

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

	void							Set_Scale(const Engine::_vec3* pScale);

private:
	HRESULT							SetUp_ConstantTable(LPD3DXEFFECT& pEffect);

	Engine::CTexture*				m_pTextures;
	Engine::CVIBuffer*				m_pRcTex;
	Engine::CShader*				m_pShader;

public:
	static CBackground*				Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar* pKey);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // Background_h__
