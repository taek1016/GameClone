#include "stdafx.h"
#include "Effect/FireWork.h"

USING(Engine)

CFireWork::CFireWork() : CParticle()
{
	m_fEmitRate = 0;
	m_fSize = 15;
	m_dwVBSize = 2048;
	m_dwVBOffset = 0;
	m_dwVBBatchSize = 512;

	SetName(L"FireWork");

}

CFireWork::CFireWork(Engine::_vec3 emitPoint, int numOfParticles)
{
	m_fEmitRate = 0;
	m_fSize = 15;
	m_dwVBSize = 2048;
	m_dwVBOffset = 0;
	m_dwVBBatchSize = 512;
	m_vEmitPoint = emitPoint;

	for (size_t i = 0; i < 512; i++)
	{
		Add_Particle();
	}

}

CFireWork::CFireWork(const CFireWork & rhs)
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

	for (size_t i = 0; i < 512; i++)
	{
		Add_Particle();
	}

	
	Reset_Particle(&m_particle);
}

HRESULT CFireWork::Initialize_GameObject()
{
	m_fEmitRate = 0;
	m_fSize = 15;
	m_dwVBSize = 2048;
	m_dwVBOffset = 0;
	m_dwVBBatchSize = 512;

	CComponent* pComponent = nullptr;
	pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"FireWork");
	pComponent->Attach(this, ID_STATIC);

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);
	return S_OK;
}

HRESULT CFireWork::Late_Initialize()
{
	return S_OK;
}

void CFireWork::Reset_AllParticles()
{
	CParticle::Reset_AllParticles();
}

void CFireWork::Reset_Particle(Engine::PARTICLEATTRIBUTE* attribute)
{
	CTransform* transform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);

	attribute->bIsAlive = true;
	attribute->vPos = m_vEmitPoint;

	_vec3 vMin = _vec3(-1.f, -1.f, -1.f);
	_vec3 vMax = _vec3(1.f, 1.f, 1.f);

	attribute->vVelocity = Get_RandomVec3(vMin, vMax);
	D3DXVec3Normalize(&attribute->vVelocity, &attribute->vVelocity);

	attribute->vVelocity *= 800.f;

	attribute->color = D3DXCOLOR(
		Get_RandomFloat(0, 1),
		Get_RandomFloat(0, 1),
		Get_RandomFloat(0, 1),
		1
	);

	attribute->colorFade = D3DXCOLOR(1, 1, 1, 1);

	attribute->fAge = 0.0f;
	attribute->fLifeTime = 6.f;

	attribute->fFadeTime = 3.f;
	attribute->fCurFadeTime = 0.f;

	attribute->vAcc = _vec3(0, 0, 0);

}

void CFireWork::Pre_Render()
{
	CParticle::Pre_Render();
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, false);

	CTexture* tex = Get_Component<CTexture>(TEXTURE, ID_STATIC);
	tex->Render_Texture();
}

void CFireWork::Post_Render()
{
	CParticle::Post_Render();
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void CFireWork::Render_GameObject()
{
	Pre_Render();
	if (!m_bFirstFire)
	{
		LPDIRECT3DDEVICE9 pGraphicDev = DLL::pGraphicDev->GetDevice();

		pGraphicDev->SetFVF(FVF_PARTICLE);
		pGraphicDev->SetStreamSource(0, m_pVB, 0, sizeof(VTX_PARTICLE));

		VTX_PARTICLE* vertices = 0;

		m_pVB->Lock(m_dwVBOffset * sizeof(VTX_PARTICLE),
			m_dwVBBatchSize * sizeof(VTX_PARTICLE),
			(void**)&vertices,
			m_dwVBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		vertices->vPos = m_particle.vPos;
		vertices->color = m_particle.color;

		m_pVB->Unlock();

		pGraphicDev->DrawPrimitive(D3DPT_POINTLIST, 0, 1);
	}
	else
	{
		CParticle::Render_GameObject();
	}
	Post_Render();
}

void CFireWork::SetBombPoint(Engine::_vec3 vPoint)
{
	m_vEmitPoint = vPoint;

	m_particle.vPos = vPoint;
	m_particle.vPos.y -= 50;

	m_iYOffset = 1;

	m_bFirstFire = false;
}

Engine::_int CFireWork::Update_GameObject(const Engine::_float & ftimeDelta)
{
	CInGameObject::Update_GameObject(ftimeDelta);

	if (!m_bFirstFire)
	{
		m_particle.vPos.y += (600 / m_iYOffset++) * ftimeDelta;
		if (m_iYOffset >= 30)
			m_iYOffset--;
		if (m_particle.vPos.y > m_vEmitPoint.y)
		{
			m_iYOffset = 1;
			m_bFirstFire = true;
			m_particle.bIsAlive = false;
		}
	}
	else
	{
		auto iter = m_ltParticles.begin();
		while (iter != m_ltParticles.end())
		{
			if ((*iter).bIsAlive)
			{
				(*iter).vPos += (((*iter).vVelocity / m_iYOffset++) * ftimeDelta);
				if (m_iYOffset >= 30)
					m_iYOffset--;
				(*iter).vPos.y += (*iter).vAcc.y * ftimeDelta;
				(*iter).vAcc.y -= 0.03f;
				iter->fAge += ftimeDelta;

				if (iter->fAge > iter->fFadeTime)
				{
					iter->fCurFadeTime += ftimeDelta;
					iter->colorFade.a -= 0.01;
					if (iter->colorFade.a < 0.02)
						iter->colorFade.a = 0.01;
					iter->color = iter->colorFade;
					if (iter->fCurFadeTime > iter->fLifeTime)
					{
						m_iYOffset = 1;
						iter->bIsAlive = false;
						m_bIsRunning = false;
						m_bFirstFire = false;
						DLL::pPoolMgr->Back_Pool(POOL_PARTICLE, this);
						return BACK_POOL;
					}
				}
			}
			iter++;
		}
	}

	return Engine::_int();
}

void CFireWork::freeMem()
{
	if (m_pVB != nullptr)
		m_pVB->Release();
	if (m_pTexture != nullptr)
		m_pTexture->Release();

	CParticle::freeMem();
}

CFireWork * CFireWork::Create()
{
	CFireWork*	pInstance = new CFireWork();
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

CFireWork * CFireWork::Clone(const Engine::_vec3 * pPos)
{
	return new CFireWork(*this);
}