#ifndef TwoFourBag_h__
#define TwoFourBag_h__

#include "BagBase.h"

class CFourFourBag : public CBagBase
{
private:
	explicit				CFourFourBag(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CFourFourBag(void) = default;

public:
	static CFourFourBag*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
};

#endif // TwoFourBag_h__
