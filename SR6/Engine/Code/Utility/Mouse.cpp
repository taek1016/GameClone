#include "Mouse.h"
#include "Transform.h"
USING(Engine)

CMouse::CMouse(void)
	: CGameObject()
{
}

CMouse::CMouse(const CMouse& rhs)
	: CGameObject(rhs)
{
}

CMouse::~CMouse(void)
{
}