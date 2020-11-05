#ifndef StaticGameObject_h__
#define StaticGameObject_h__

#include "GameObject.h"

class CStaticObject : public Engine::CGameObject
{
private:
	explicit						CStaticObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CStaticObject(const CStaticObject& rhs);
	virtual							~CStaticObject(void);

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject() override;

	void							Make_Collider(const Engine::_vec3* pPos, const Engine::_float& fRadius);

private:
	void							set_RenderKey(const Engine::_tchar* pKey);
	void							set_Radius(const Engine::_float& fRadius);
	HRESULT							setUp_ConstantTable(LPD3DXEFFECT& pEffect);

	Engine::CStaticMesh*			m_pMesh;
	Engine::CSphereCollider*		m_pSphereCol;
	Engine::CShader*				m_pShaderCom;

	Engine::_float					m_fRadius;

public:
	static CStaticObject*			Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar* pKey);
	virtual Engine::CGameObject*	Clone(void);

private:
	inline virtual void				Free(void);
};
#endif // StaticGameObject_h__