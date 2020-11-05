#ifndef OneFourBag_h__
#define OneFourBag_h__

#include "BagBase.h"

class COneFourBag : public CBagBase
{
private:
	explicit		COneFourBag(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual			~COneFourBag(void) = default;

public:
	static COneFourBag*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
};


#endif // OneFourBag_h__
