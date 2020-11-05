#ifndef SilverCoin_h__
#define SilverCoin_h__

#include "CoinBase.h"

class CSilverCoin : public CCoinBase
{
private:
	explicit				CSilverCoin(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CSilverCoin(void) = default;

public:
	virtual void Set_Coins(Engine::_int& iRemainCoin);

public:
	static CSilverCoin*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale, const Engine::_int & iFontWidth, const Engine::_int & iFontHeight);

};
#endif // SilverCoin_h__
