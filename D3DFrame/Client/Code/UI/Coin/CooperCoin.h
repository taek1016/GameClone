#ifndef CooperCoin_h__
#define CooperCoin_h__

#include "CoinBase.h"

class CCooperCoin : public CCoinBase
{
private:
	explicit				CCooperCoin(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CCooperCoin(void) = default;

public:
	virtual void			Set_Coins(Engine::_int& iRemainCoin);

public:
	static CCooperCoin*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale, const Engine::_int & iFontWidth, const Engine::_int & iFontHeight);

};
#endif // CooperCoin_h__
