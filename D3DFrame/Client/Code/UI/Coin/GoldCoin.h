#ifndef GoldCoin_h__
#define GoldCoin_h__

#include "CoinBase.h"

class CGoldCoin : public CCoinBase
{
private:
	explicit				CGoldCoin(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CGoldCoin(void) = default;

public:
	virtual void			Set_Coins(Engine::_int& iRemainCoin);

public:
	static CGoldCoin*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale, const Engine::_int & iFontWidth, const Engine::_int & iFontHeight);

};
#endif // GoldCoin_h__
