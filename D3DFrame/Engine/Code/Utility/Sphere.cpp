#include "Sphere.h"

#include "Transform.h"
USING(Engine)

CSphereCollider::CSphereCollider(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCollider(pGraphicDev)
	, m_vCenterPos(0.f, 0.f, 0.f)
	, m_fRadius(0.f)
{
	D3DXMatrixIdentity(&m_matWorld);
}

CSphereCollider::CSphereCollider(const CSphereCollider & rhs)
	: CCollider(rhs)
	, m_vCenterPos(rhs.m_vCenterPos)
	, m_fRadius(rhs.m_fRadius)
{
}

CSphereCollider::~CSphereCollider(void)
{
}

const _vec3 * CSphereCollider::Get_CenterPos(void)
{
	if (nullptr != m_pBone)
	{
		_matrix matBone = m_matPosition * *m_pBone * *m_pWorld;
		memcpy(&m_vCenterPos, matBone.m[3], sizeof(_vec3));
	}
	else
	{
		memcpy(&m_vCenterPos, m_pWorld->m[3], sizeof(_vec3));
	}
	return &m_vCenterPos;
}

const _float * CSphereCollider::Get_Radius(void) const
{
	return &m_fRadius;
}

HRESULT CSphereCollider::Initialize_Collider(const _float& fRadius, const _ulong & dwSlice, const _ulong & dwStack, const _matrix* pWorld, const _matrix* pBone, const _vec3* pPos)
{
	m_fRadius = fRadius;
	D3DXCreateSphere(m_pGraphicDev, m_fRadius, dwSlice, dwStack, &m_pMesh, nullptr);

	m_pWorld = pWorld;
	m_pBone = pBone;
	if (nullptr != pPos)
	{
		memcpy(m_matWorld.m[3], pPos, sizeof(_vec3));
	}

	set_Material();
	set_Texture();

	return S_OK;
}

void CSphereCollider::Set_Collider(const _matrix * pWorld, const _matrix * pBone, const _vec3 * pPos)
{
	m_pWorld = pWorld;
	m_pBone = pBone;
	if (nullptr != pPos)
	{
		memcpy(m_matWorld.m[3], pPos, sizeof(_vec3));
	}
}

CSphereCollider * CSphereCollider::Create(LPDIRECT3DDEVICE9 pGraphicDev, 
											const _float& fRadius,
											const _ulong & dwSlice,
											const _ulong & dwStack, 
											const _matrix* pWorld, 
											const _matrix* pBone, 
											const _vec3* pPos)
{
	CSphereCollider* pInstance = new CSphereCollider(pGraphicDev);

	if (FAILED(pInstance->Initialize_Collider(fRadius, dwSlice, dwStack, pWorld, pBone, pPos)))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CSphereCollider::Clone(void)
{
	return new CSphereCollider(*this);
}
