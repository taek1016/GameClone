#ifndef TwoFourBag_h__
#define TwoFourBag_h__

#include "BagBase.h"

class CThreeFourBag : public CBagBase
{
private:
	explicit				CThreeFourBag(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CThreeFourBag(void) = default;

public:
	static CThreeFourBag*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
};

#endif // TwoFourBag_h__
