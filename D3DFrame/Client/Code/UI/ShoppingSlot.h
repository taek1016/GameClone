#ifndef ShoppingSlot_h__
#define ShoppingSlot_h__

#include "ItemSlot.h"

class CShoppingSlot : public CItemSlot
{
private:
	explicit						CShoppingSlot(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CShoppingSlot(void) = default;

public:
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Click_Action(void);

	void							Initialize_Name(void);

private:
	void							make_CoinUI(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	class CCoinUI*					m_pCoin;
	Engine::_vec3					m_vStartPos;
	Engine::_vec3					m_vFontScale;
	
	Engine::_tchar					m_szItemName[32];
	D3DXCOLOR						m_tColor;

public:
	static CShoppingSlot*			Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);

};

#endif // ShoppingSlot_h__
