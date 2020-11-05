#include "stdafx.h"
#include "Particle.h"

USING(Engine)

CParticle::CParticle() : 
	CInGameObject()
{
}

CParticle::~CParticle()
{
}

HRESULT CParticle::Initialize_GameObject()
{
	if (m_pVB == nullptr)
	{
		HRESULT hr = DLL::pGraphicDev->GetDevice()->CreateVertexBuffer(
			m_dwVBSize * sizeof(Engine::VTX_PARTICLE),
			D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
			FVF_PARTICLE,
			D3DPOOL_DEFAULT,
			&m_pVB,
			0);
	}

	CComponent* pComponent = nullptr;
	CTransform* transform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	if (transform == nullptr)
	{
		pComponent = CTransform::Create();
		pComponent->Attach(this, ID_DYNAMIC);
	}
	return S_OK;
}

void CParticle::Reset_Particle(PARTICLEATTRIBUTE* pAtt)
{

}

void CParticle::Reset_AllParticles()
{
	m_bIsRunning = true;
	auto iter = m_ltParticles.begin();
	while (iter != m_ltParticles.end())
	{
		Reset_Particle(&(*iter));
		iter++;
	}
}

void CParticle::Add_Particle()
{
	PARTICLEATTRIBUTE particle;
	Reset_Particle(&particle);

	m_ltParticles.push_back(particle);
}

void CParticle::Render_GameObject()
{
	if (!m_ltParticles.empty())
	{
		Pre_Render();

		LPDIRECT3DDEVICE9 pGraphicDev = DLL::pGraphicDev->GetDevice();

		pGraphicDev->SetFVF(FVF_PARTICLE);
		pGraphicDev->SetStreamSource(0, m_pVB, 0, sizeof(VTX_PARTICLE));

		if (m_dwVBOffset >= m_dwVBSize)
		{
			m_dwVBOffset = 0;
		}

		VTX_PARTICLE* vertices = 0;
		VTX_PARTICLE* curVertex = 0;

		m_pVB->Lock(m_dwVBOffset * sizeof(VTX_PARTICLE), 
			m_dwVBBatchSize * sizeof(VTX_PARTICLE), 
			(void**)&vertices, 
			m_dwVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		curVertex = vertices;

		DWORD dwNumParticlesInBatch = 0;

		list<PARTICLEATTRIBUTE>::iterator iter;
		for (iter = m_ltParticles.begin(); iter != m_ltParticles.end(); iter++)
		{
			if (iter->bIsAlive)
			{
				curVertex->vPos = iter->vPos;
				curVertex->color = iter->color;
				curVertex++;

				dwNumParticlesInBatch++;

				if (dwNumParticlesInBatch == m_dwVBBatchSize)
				{
					m_pVB->Unlock();

					pGraphicDev->DrawPrimitive(D3DPT_POINTLIST, m_dwVBOffset, m_dwVBBatchSize);
					m_dwVBOffset += m_dwVBBatchSize;

					if (m_dwVBOffset >= m_dwVBSize)
						m_dwVBOffset = 0;

					m_pVB->Lock(m_dwVBOffset * sizeof(VTX_PARTICLE),
						m_dwVBBatchSize * sizeof(VTX_PARTICLE),
						(void**)&vertices,
						m_dwVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					dwNumParticlesInBatch = 0;
				}
			}
		}

		m_pVB->Unlock();
		if (dwNumParticlesInBatch)
		{
			pGraphicDev->DrawPrimitive(D3DPT_POINTLIST,
				m_dwVBOffset, dwNumParticlesInBatch);
		}

		m_dwVBOffset += m_dwVBBatchSize;

		Post_Render();
	}
	CInGameObject::Render_GameObject();
}

void CParticle::Pre_Render()
{
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_POINTSIZE, FtoW(m_fSize));
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_POINTSIZE_MIN, FtoW(m_fSize));
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_POINTSIZE_MAX, FtoW(100.f));

	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_POINTSCALE_A, FtoW(0.f));
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_POINTSCALE_B, FtoW(0.f));

	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_POINTSCALE_C, FtoW(1.f));

	DLL::pGraphicDev->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DLL::pGraphicDev->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DLL::pGraphicDev->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DLL::pGraphicDev->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DLL::pGraphicDev->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
}

void CParticle::Post_Render()
{
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	DLL::pGraphicDev->GetDevice()->SetTexture(0, nullptr);
}

void CParticle::Clear_DeadParticles()
{
	auto iter = m_ltParticles.begin();
	{
		while (iter != m_ltParticles.end())
		{
			if ((*iter).bIsAlive == false)
			{
				m_ltParticles.erase(iter);
			}
			else
				iter++;
		}
	}
}

Engine::_float CParticle::Get_RandomFloat(_float fRandMin, _float fRandMax)
{
	if (fRandMin >= fRandMax)
		return fRandMin;

	float fRetVal = (rand() % 10000) * 0.0001f;
	fRetVal = (fRetVal * (fRandMax - fRandMin)) + fRandMin;
	return fRetVal;
}

Engine::_vec3 CParticle::Get_RandomVec3(Engine::_vec3 vMin, Engine::_vec3 vMax)
{
	_vec3 vRetVal;
	
	vRetVal.x = Get_RandomFloat(vMin.x, vMax.x);
	vRetVal.y = Get_RandomFloat(vMin.y, vMax.y);
	vRetVal.z = Get_RandomFloat(vMin.z, vMax.z);
	
	return vRetVal;
}

CParticle::CParticle(const CParticle & rhs)
	:CInGameObject(rhs),
	m_fSize(rhs.m_fSize),
	m_dwVBSize(rhs.m_dwVBSize),
	m_dwVBOffset(rhs.m_dwVBOffset),
	m_dwVBBatchSize(rhs.m_dwVBBatchSize)
{
}
