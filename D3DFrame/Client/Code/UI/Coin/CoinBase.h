#ifndef CoinBase_h__
#define CoinBase_h__

#include "../UIBase.h"

class CCoinBase : public CUIBase
{
protected:
	explicit				CCoinBase(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CCoinBase(void) = default;

public:
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void			Render_GameObject(void) override;

	virtual void			Set_Coins(Engine::_int& iRemainCoin) PURE;

protected:
	void					set_FontSize(const Engine::_int& iFontWidth, const Engine::_int& iFontHeight);

	Engine::_int			m_iCoinNum;
	Engine::_int			m_iFontWidth;
	Engine::_int			m_iFontHeight;
	Engine::_tchar			m_szCoinNum[32];
};

#endif // CoinBase_h__
