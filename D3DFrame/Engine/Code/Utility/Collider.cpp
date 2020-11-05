#include "Collider.h"

#include "Transform.h"

USING(Engine)

CCollider::CCollider(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent()
	, m_pGraphicDev(pGraphicDev)
	, m_pMesh(nullptr)
	, m_pWorld(nullptr)
	, m_pBone(nullptr)
{
	m_pGraphicDev->AddRef();
	D3DXMatrixIdentity(&m_matPosition);
}

CCollider::CCollider(const CCollider& rhs)
	: CComponent(rhs)
	, m_pMesh(nullptr)
	, m_pWorld(nullptr)
	, m_pBone(nullptr)
	, m_pTexture{ nullptr }
	, m_pGraphicDev(rhs.m_pGraphicDev)
{
	m_pGraphicDev->AddRef();
	D3DXMatrixIdentity(&m_matPosition);
}

CCollider::~CCollider(void)
{
}

void CCollider::Render_Collider(COLLTYPE eType)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pGraphicDev->SetMaterial(&m_Material[eType]);
	m_pGraphicDev->SetTexture(0, m_pTexture[eType]);
	m_pMesh->DrawSubset(0);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void CCollider::Render_Collider(COLLTYPE eType, const _matrix * pMatrix)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, pMatrix);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pGraphicDev->SetMaterial(&m_Material[eType]);
	m_pGraphicDev->SetTexture(0, m_pTexture[eType]);
	m_pMesh->DrawSubset(0);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}


void CCollider::set_Material(void)
{
	m_Material[COLLTYPE::COL_FALSE].Diffuse.r = m_Material[COLLTYPE::COL_FALSE].Ambient.r = 0.f;
	m_Material[COLLTYPE::COL_FALSE].Diffuse.g = m_Material[COLLTYPE::COL_FALSE].Ambient.g = 1.f;
	m_Material[COLLTYPE::COL_FALSE].Diffuse.b = m_Material[COLLTYPE::COL_FALSE].Ambient.b = 0.f;
	m_Material[COLLTYPE::COL_FALSE].Diffuse.a = m_Material[COLLTYPE::COL_FALSE].Ambient.a = 1.f;

	m_Material[COLLTYPE::COL_FALSE].Emissive.r = m_Material[COLLTYPE::COL_FALSE].Specular.r = 0.f;
	m_Material[COLLTYPE::COL_FALSE].Emissive.g = m_Material[COLLTYPE::COL_FALSE].Specular.g = 1.f;
	m_Material[COLLTYPE::COL_FALSE].Emissive.b = m_Material[COLLTYPE::COL_FALSE].Specular.b = 0.f;
	m_Material[COLLTYPE::COL_FALSE].Emissive.a = m_Material[COLLTYPE::COL_FALSE].Specular.a = 1.f;

	m_Material[COLLTYPE::COL_FALSE].Power = 1.f;

	m_Material[COLLTYPE::COL_TRUE].Diffuse.r = m_Material[COLLTYPE::COL_TRUE].Ambient.r = 1.f;
	m_Material[COLLTYPE::COL_TRUE].Diffuse.g = m_Material[COLLTYPE::COL_TRUE].Ambient.g = 0.f;
	m_Material[COLLTYPE::COL_TRUE].Diffuse.b = m_Material[COLLTYPE::COL_TRUE].Ambient.b = 0.f;
	m_Material[COLLTYPE::COL_TRUE].Diffuse.a = m_Material[COLLTYPE::COL_TRUE].Ambient.a = 1.f;

	m_Material[COLLTYPE::COL_TRUE].Emissive.r = m_Material[COLLTYPE::COL_TRUE].Specular.r = 1.f;
	m_Material[COLLTYPE::COL_TRUE].Emissive.g = m_Material[COLLTYPE::COL_TRUE].Specular.g = 0.f;
	m_Material[COLLTYPE::COL_TRUE].Emissive.b = m_Material[COLLTYPE::COL_TRUE].Specular.b = 0.f;
	m_Material[COLLTYPE::COL_TRUE].Emissive.a = m_Material[COLLTYPE::COL_TRUE].Specular.a = 1.f;
						 
	m_Material[COLLTYPE::COL_TRUE].Power = 1.f;
}

void CCollider::set_Texture(void)
{
	const _float fCritic = 1.f / COL_END;

	D3DXCOLOR tColor;
	for (_uint i = 0; i < COL_END; ++i)
	{
		m_pGraphicDev->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture[i], NULL);

		D3DLOCKED_RECT	tLockRect;
		ZeroMemory(&tLockRect, sizeof(D3DLOCKED_RECT));

		m_pTexture[i]->LockRect(0, &tLockRect, NULL, NULL);

		switch (i)
		{
		case Engine::COL_FALSE:
			tColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
			break;
		case Engine::COL_ATTACK_START:
			tColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
			break;
		case Engine::COL_DURING_ATTACK:
			tColor = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);
			break;
		case Engine::COL_TRUE:
			tColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
			break;
		}
		*((_ulong*)tLockRect.pBits) = tColor;

		m_pTexture[i]->UnlockRect(0);
	}

}

void CCollider::Free(void)
{
	Safe_Release(m_pMesh);
	Safe_Release(m_pGraphicDev);

	for (_int i = 0; i < static_cast<_int>(COLLTYPE::COL_END); ++i)
	{
		Safe_Release(m_pTexture[i]);
	}
}