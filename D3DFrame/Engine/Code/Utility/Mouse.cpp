#include "Mouse.h"
#include "Transform.h"

USING(Engine)

CMouse::CMouse(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CMouse::CMouse(const CMouse& rhs)
	: CGameObject(rhs)
{
}

CMouse::~CMouse(void)
{
}