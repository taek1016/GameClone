#ifndef SelectionCircle_h__
#define SelectionCircle_h__

#include "UIBase.h"

class CSelectionCircle : public CUIBase
{
private:
	explicit						CSelectionCircle(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CSelectionCircle(const CSelectionCircle& rhs);
	virtual							~CSelectionCircle(void) = default;

public:
	virtual HRESULT					Initialize_UI(const Engine::_tchar* pName);
	virtual HRESULT					Late_InitializeUI(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	//virtual void					Render_GameObject(void) override;

private:
	//HRESULT							SetUp_ConstantTable(LPD3DXEFFECT & pEffect);

	Engine::CShader*				m_pShaderCom;

public:
	static CSelectionCircle*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // SelectionCircle_h__
