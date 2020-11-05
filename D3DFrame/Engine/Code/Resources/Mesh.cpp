#include "Mesh.h"

USING(Engine)

CMesh::CMesh(LPDIRECT3DDEVICE9 pGraphicDev)
	: CResources(pGraphicDev)
{
}

CMesh::CMesh(const CMesh& rhs)
	: CResources(rhs)
{
}

CMesh::~CMesh(void)
{
}