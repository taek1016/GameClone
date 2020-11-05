#ifndef CoinUI_h__
#define CoinUI_h__

#include "UIBase.h"

class CCoinBase;

class CCoinUI : public CUIBase
{
	enum COIN_ENUM			{ COIN_GOLD, COIN_SILVER, COIN_COOPER, COIN_END };

private:
	explicit				CCoinUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CCoinUI(void) = default;

public:
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;

	void					Set_Coins(Engine::_int& iMoney);

private:
	void					make_Coins(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	Engine::_int			m_iFontWidth;
	Engine::_int			m_iFontHeight;

	CCoinBase*				m_pCoins[COIN_END];

public:
	static CCoinUI*			Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);

private:
	inline virtual void		Free(void) override;
};
#endif // CoinUI_h__
