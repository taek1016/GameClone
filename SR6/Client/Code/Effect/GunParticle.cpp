#include "stdafx.h"
#include "Effect/GunParticle.h"



CGunParticle::CGunParticle()
{
}

CGunParticle::CGunParticle(const CGunParticle & rhs)
	:CParticle(rhs)
{
	if (m_pVB == nullptr)
	{
		HRESULT hr = DLL::pGraphicDev->GetDevice()->CreateVertexBuffer(
			1 * sizeof(Engine::VTX_PARTICLE),
			D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
			FVF_PARTICLE,
			D3DPOOL_DEFAULT,
			&m_pVB,
			0);
	}

	Add_Particle();
}

HRESULT CGunParticle::Initialize_GameObject()
{
	CComponent* pComponent = nullptr;
	pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"GunFire");
	pComponent->Attach(this, ID_STATIC);

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	if (m_pVB == nullptr)
	{
		HRESULT hr = DLL::pGraphicDev->GetDevice()->CreateVertexBuffer(
			1 * sizeof(Engine::VTX_PARTICLE),
			D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
			FVF_PARTICLE,
			D3DPOOL_DEFAULT,
			&m_pVB,
			0);
	}

	Add_Particle();

	return S_OK;
}

HRESULT CGunParticle::Late_Initialize()
{

	return S_OK;
}

void CGunParticle::Reset_AllParticles()
{
	m_fEmitRate = 0;
	m_fSize = 80;
	m_dwVBSize = 1;
	m_dwVBOffset = 0;
	m_dwVBBatchSize = 1;
	HRESULT hr;
	if (m_pVB == nullptr)
	{
		hr = DLL::pGraphicDev->GetDevice()->CreateVertexBuffer(
			1 * sizeof(Engine::VTX_PARTICLE),
			D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
			FVF_PARTICLE,
			D3DPOOL_DEFAULT,
			&m_pVB,
			0);
	}

	CParticle::Reset_AllParticles();

}

void CGunParticle::Reset_Particle(Engine::PARTICLEATTRIBUTE * attribute)
{
	attribute->bIsAlive = true;
	attribute->vPos = m_vEmitPoint;

	attribute->color = D3DXCOLOR(1, 1, 1, 1);

	attribute->fAge = 0.0f;
	attribute->fLifeTime = 0.1f;

	m_iTexIndex = rand() % 5;
}

void CGunParticle::Pre_Render()
{
	CParticle::Pre_Render();
}

void CGunParticle::Post_Render()
{
	CParticle::Post_Render();
}

void CGunParticle::Render_GameObject()
{
	CTexture* tex = Get_Component<CTexture>(TEXTURE, ID_STATIC);
	tex->Render_Texture(m_iTexIndex);
	if (!m_ltParticles.empty())
	{
		Pre_Render();

		LPDIRECT3DDEVICE9 pGraphicDev = DLL::pGraphicDev->GetDevice();

		pGraphicDev->SetFVF(FVF_PARTICLE);
		pGraphicDev->SetStreamSource(0, m_pVB, 0, sizeof(VTX_PARTICLE));

		VTX_PARTICLE* vertices = 0;
		VTX_PARTICLE* curVertex = 0;

		m_pVB->Lock(0, 0, (void**)&vertices, 0);

		curVertex = vertices;
		auto iter = m_ltParticles.begin();

		if (iter->bIsAlive)
		{
			curVertex->vPos = iter->vPos;
			curVertex->color = iter->color;
		}

		m_pVB->Unlock();
		pGraphicDev->DrawPrimitive(D3DPT_POINTLIST, 0, 1);

		Post_Render();
	}
}

Engine::_int CGunParticle::Update_GameObject(const Engine::_float & ftimeDelta)
{
	CInGameObject::Update_GameObject(ftimeDelta);
	auto iter = m_ltParticles.begin();
	while (iter != m_ltParticles.end())
	{
		if ((*iter).bIsAlive)
		{
			iter->fAge += ftimeDelta;

			if (iter->fAge > iter->fLifeTime)
			{
				iter->bIsAlive = false;
				m_bIsRunning = false;
				DLL::pPoolMgr->Back_Pool(POOL_GUNFIRE, this);
				return BACK_POOL;
			}
		}
		iter++;
	}

	return Engine::_int();
}

void CGunParticle::freeMem()
{
	if (m_pVB != nullptr)
		m_pVB->Release();
	if (m_pTexture != nullptr)
		m_pTexture->Release();

	CParticle::freeMem();
}

CGunParticle* CGunParticle::Create()
{
	CGunParticle*	pInstance = new CGunParticle();
	pInstance->SetName(L"GunParticle");
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGunParticle * CGunParticle::Clone(const Engine::_vec3 * pPos)
{
	return new CGunParticle(*this);
}