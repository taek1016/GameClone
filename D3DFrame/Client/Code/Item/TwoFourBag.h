#ifndef TwoFourBag_h__
#define TwoFourBag_h__

#include "BagBase.h"

class CTwoFourBag : public CBagBase
{
private:
	explicit			CTwoFourBag(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CTwoFourBag(void) = default;

public:
	static CTwoFourBag*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
};

#endif // TwoFourBag_h__
