#include "Sphere.h"

#include "Transform.h"

USING(Engine)

CSphere::CSphere(void)
	: CCollider()
	, m_fRadius(0.f)
{
	m_eColType = COLLISION_SPHERE;
}

CSphere::CSphere(const CSphere & rhs)
	: CCollider(rhs)
	, m_fRadius(rhs.m_fRadius)
{
}

CSphere::~CSphere(void)
{
}

HRESULT CSphere::Initialize_Component()
{
	D3DXCreateSphere(m_pGraphicDev, m_fRadius, 10, 5, &m_pMesh, NULL);

	return S_OK;
}

void CSphere::Render_Collider()
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pMesh->DrawSubset(0);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

bool CSphere::Is_Collide(CCollider* pOther, _float* pDistance)
{
	CSphere* pOtherSphere = dynamic_cast<CSphere*>(pOther);

	_float fDis = D3DXVec3Length(&(*pOtherSphere->Get_Pos() - m_vPos));

	_float fRadiusSum = pOtherSphere->m_fRadius + m_fRadius;
	if (fRadiusSum >= fDis)
	{
		if (nullptr != pDistance)
		{
			*pDistance = fRadiusSum - fDis;
		}
		return true;
	}

	return false;
}

CSphere * CSphere::Create(const _float & fRadius)
{
	CSphere* pInstance = new CSphere;

	pInstance->Set_Radius(fRadius);

	if (FAILED(pInstance->Initialize_Component()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CSphere::Clone(void)
{
	return new CSphere(*this);
}

inline void CSphere::freeMem()
{
	CCollider::freeMem();
	Safe_Release(m_pMesh);
}
