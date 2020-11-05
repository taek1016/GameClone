#ifndef Skybox_h__
#define Skybox_h__

#include "GameObject.h"

class CSkyBox : public Engine::CGameObject
{
protected:
	explicit				CSkyBox(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CSkyBox(const CSkyBox& rhs);
	virtual					~CSkyBox(void) = default;

public:
	virtual HRESULT			Initialize_GameObject(void) override;
	virtual HRESULT			Late_Initialize(void) override;
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void			Render_GameObject(void) override;

protected:
	virtual HRESULT			setUp_ConstantTable(LPD3DXEFFECT& pEffect);
	void					update_Position(const Engine::_float& fTimeDelta);

	Engine::CDynamicMesh*	m_pMesh;
	Engine::CShader*		m_pShader;
};

#endif // Skybox_h__