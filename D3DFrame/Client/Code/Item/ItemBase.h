#ifndef ItemBase_h__
#define ItemBase_h__

#include "GameObject.h"

class CItemBase : public Engine::CGameObject
{
protected:
	explicit					CItemBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit					CItemBase(const CItemBase& rhs);
	virtual						~CItemBase(void);

public:
	virtual HRESULT				Initialize_GameObject(void) { return S_OK; };
	virtual void				Set_ColliderMat(const Engine::_matrix* pWorld, const Engine::_matrix* pBone = nullptr, const Engine::_vec3 * pStartPos = &Engine::_vec3(0.f, 0.f, 0.f)) {};
	
protected:
	Engine::CShader*			m_pShaderCom;
};

#endif // ItemBase_h__
