#ifndef ItemExplanationSlot_h__
#define ItemExplanationSlot_h__

#include "UIBase.h"

class CShoppingSlot;

class CItemExplanationSlot : public CUIBase
{
private:
	explicit						CItemExplanationSlot(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CItemExplanationSlot(void) = default;

public:
	virtual HRESULT					Initialize_UI(const Engine::_tchar * pName) override;
	virtual HRESULT					Late_InitializeUI(const Engine::_vec3* pPos, const Engine::_vec3* pScale) override;
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

private:
	void							make_ItemExplanation(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_tchar* pName);
	CShoppingSlot*					m_pItemSlot;
	
public:
	static CItemExplanationSlot*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale, const Engine::_tchar* pName);
	virtual Engine::CGameObject*	Clone(void) override;

private:
	inline virtual void				Free(void) override;
};

#endif // ItemExplanationSlot_h__
