#include "stdafx.h"
#include "Effect/Fragment.h"

USING(Engine)

CFragment::CFragment() : CParticle()
{
	m_fEmitRate = 0;
	m_fSize = 15;
	m_dwVBSize = 2048;
	m_dwVBOffset = 0;
	m_dwVBBatchSize = 512;

	SetName(L"Fragment");

}

CFragment::CFragment(Engine::_vec3 emitPoint, int numOfParticles)
{
	m_fEmitRate = 0;
	m_fSize = 15;
	m_dwVBSize = 2048;
	m_dwVBOffset = 0;
	m_dwVBBatchSize = 512;
	m_vEmitPoint = emitPoint;

	for (size_t i = 0; i < 15; i++)
	{
		Add_Particle();
	}

}

CFragment::CFragment(const CFragment & rhs)
	:CParticle(rhs)
{
	if (m_pVB == nullptr)
	{
		HRESULT hr = DLL::pGraphicDev->GetDevice()->CreateVertexBuffer(
			rhs.m_dwVBSize * sizeof(Engine::VTX_PARTICLE),
			D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
			FVF_PARTICLE,
			D3DPOOL_DEFAULT,
			&m_pVB,
			0);
	}

	for (size_t i = 0; i < 15; i++)
	{
		Add_Particle();
	}
}

HRESULT CFragment::Initialize_GameObject()
{
	m_fEmitRate = 0;
	m_fSize = 15;
	m_dwVBSize = 2048;
	m_dwVBOffset = 0;
	m_dwVBBatchSize = 512;

	CComponent* pComponent = nullptr;
	pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"Fragment");
	pComponent->Attach(this, ID_STATIC);

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);
	return S_OK;
}

HRESULT CFragment::Late_Initialize()
{
	return S_OK;
}

void CFragment::Reset_AllParticles()
{
	CParticle::Reset_AllParticles();
}

void CFragment::Reset_Particle(Engine::PARTICLEATTRIBUTE* attribute)
{
	CTransform* transform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);

	attribute->bIsAlive = true;

	_vec3 vMin = _vec3(-1, 0, -1);
	_vec3 vMax = _vec3(1, 1, 1);

	_vec3 vRand = Get_RandomVec3(vMin, vMax);
	attribute->vVelocity = vRand;

	m_vEmitPoint.x += vRand.x/10000;
	m_vEmitPoint.z += vRand.z/10000;

	attribute->vPos = m_vEmitPoint;

	
	D3DXVec3Normalize(&attribute->vVelocity, &attribute->vVelocity);

	attribute->vVelocity *= 5.f;

	attribute->color = D3DXCOLOR(
		1,
		1,
		1,
		1
	);

	attribute->colorFade = D3DXCOLOR(1, 1, 1, 1);

	attribute->fAge = 0.0f;
	attribute->fLifeTime = 1.f;

	attribute->fFadeTime = 2.f;
	attribute->fCurFadeTime = 0.f;

	attribute->vAcc = _vec3(0, 0, 0);

}

void CFragment::Pre_Render()
{
	CParticle::Pre_Render();

	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, false);

	CTexture* tex = Get_Component<CTexture>(TEXTURE, ID_STATIC);
	tex->Render_Texture();
}

void CFragment::Post_Render()
{
	CParticle::Post_Render();
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

Engine::_int CFragment::Update_GameObject(const Engine::_float & ftimeDelta)
{
	CInGameObject::Update_GameObject(ftimeDelta);
	auto iter = m_ltParticles.begin();
	while (iter != m_ltParticles.end())
	{
		if ((*iter).bIsAlive)
		{
			(*iter).vPos += ((*iter).vVelocity * ftimeDelta);
			(*iter).vPos.y += (*iter).vAcc.y * ftimeDelta;
			(*iter).vAcc.y -= 0.03f;
			iter->fAge += ftimeDelta;

			if (iter->fAge > iter->fLifeTime)
			{
				iter->fCurFadeTime += ftimeDelta;
				iter->colorFade.a -= 0.01f;
				iter->color = iter->colorFade;
				if (iter->fCurFadeTime > iter->fFadeTime)
				{
					iter->bIsAlive = false;
					m_bIsRunning = false;

					DLL::pPoolMgr->Back_Pool(POOL_PARTICLE, this);
					return BACK_POOL;
				}
			}
		}
		iter++;
	}

	return Engine::_int();
}

void CFragment::freeMem()
{
	if (m_pVB != nullptr)
		m_pVB->Release();
	if (m_pTexture != nullptr)
		m_pTexture->Release();

	CParticle::freeMem();
}

CFragment * CFragment::Create()
{
	CFragment*	pInstance = new CFragment();
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

CFragment * CFragment::Clone(const Engine::_vec3 * pPos)
{
	return new CFragment(*this);
}