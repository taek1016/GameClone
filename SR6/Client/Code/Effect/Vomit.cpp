#include "stdafx.h"
#include "Effect/Vomit.h"
#include <iostream>

USING(Engine)

CVomit::CVomit() : CParticle()
{
	m_fEmitRate = 0;
	m_fSize = 15;
	m_dwVBSize = 2048;
	m_dwVBOffset = 0;
	m_dwVBBatchSize = 512;

	SetName(L"Vomit");
}

CVomit::CVomit(Engine::_vec3 emitPoint, int numOfParticles)
{
	m_fEmitRate = 0;
	m_fSize = 15;
	m_dwVBSize = 2048;
	m_dwVBOffset = 0;

	m_dwVBBatchSize = 512;
	m_vEmitPoint = emitPoint;

	for (size_t i = 0; i < 10; i++)
	{
		Add_Particle();
	}
}

CVomit::CVomit(const CVomit & rhs)
	:CParticle(rhs),
	m_fRunningTime(rhs.m_fRunningTime),
	m_fDeathTime(rhs.m_fDeathTime)
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

	Add_Particle();
}

HRESULT CVomit::Initialize_GameObject()
{
	m_fEmitRate = 0;
	m_fSize = 30;
	m_dwVBSize = 2048;
	m_dwVBOffset = 0;
	m_dwVBBatchSize = 512;

	CComponent* pComponent = nullptr;
	pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"Vomit");
	pComponent->Attach(this, ID_STATIC);

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	m_fRunningTime = 0.f;
	m_fDeathTime = 3.f;
	return S_OK;
}

HRESULT CVomit::Late_Initialize()
{
	return S_OK;
}

void CVomit::Reset_AllParticles()
{
	CParticle::Reset_AllParticles();
}

void CVomit::Reset_Particle(Engine::PARTICLEATTRIBUTE* attribute)
{
	CGameObject* player = DLL::pSearchMgr->Get_Object(L"Player");
	if (player == nullptr)
		return;
	CTransform* playerTransform = player->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	CTransform* transform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);

	attribute->bIsAlive = true;

	_vec3 vMin = _vec3(-0.5, -1, 0);
	_vec3 vMax = _vec3(0.5, 0, 1);
	
	_vec3 vPos = *transform->Get_Info(INFO_POS);
	vPos.y += 2;

	_vec3 playerPos = *playerTransform->Get_Info(INFO_POS);

	_vec3 dir = playerPos - vPos;

	D3DXVec3Normalize(&dir, &dir);

	_vec3 vRand = Get_RandomVec3(vMin, vMax);

	dir.x += vRand.x;
	dir.y += vRand.y;

	attribute->vVelocity = dir;

	//m_vEmitPoint.x += dir.x / 10000;
	//m_vEmitPoint.z += dir.z / 10000;

	attribute->vPos = m_vEmitPoint;
	attribute->vPos.y += 2;


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
	attribute->fLifeTime = 3.f;

	attribute->fFadeTime = 2.f;
	attribute->fCurFadeTime = 0.f;

	attribute->vAcc = _vec3(0, 0, 0);

}

void CVomit::Pre_Render()
{
	CParticle::Pre_Render();

	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, false);

	CTexture* tex = Get_Component<CTexture>(TEXTURE, ID_STATIC);
	tex->Render_Texture();
}

void CVomit::Post_Render()
{
	CParticle::Post_Render();
	DLL::pGraphicDev->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

Engine::_int CVomit::Update_GameObject(const Engine::_float & ftimeDelta)
{
	m_fRunningTime += ftimeDelta;
	if (m_fRunningTime > m_fDeathTime)
	{
		if (m_fRunningTime - m_fDeathTime > 1)
		{
			m_bIsRunning = false;
			DLL::pPoolMgr->Back_Pool(POOL_VOMIT, this);
			return BACK_POOL;
		}
	}

	m_fEmitTime += ftimeDelta;

	if (m_fEmitTime > 0.06f && m_fRunningTime <= m_fDeathTime)
	{
		Add_Particle();
		m_fEmitTime = 0;
	}
	CInGameObject::Update_GameObject(ftimeDelta);
	CGameObject* pPlayer = DLL::pSearchMgr->Get_Object(L"Player");
	CTransform* transform = pPlayer->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	_vec3 playerPos = *transform->Get_Info(INFO_POS);
	auto iter = m_ltParticles.begin();
	while (iter != m_ltParticles.end())
	{
		if ((*iter).bIsAlive)
		{
			(*iter).vPos += ((*iter).vVelocity * ftimeDelta);
			iter->fAge += ftimeDelta;
			if (D3DXVec3Length(&(playerPos - iter->vPos)) < 3)
			{
				pPlayer->Take_Damage(1);
			}
			if (iter->fAge > iter->fLifeTime)
			{
				iter->fCurFadeTime += ftimeDelta;
				iter->colorFade.a -= 0.01f;
				iter->color = iter->colorFade;
				if (iter->fCurFadeTime > iter->fFadeTime)
				{
					iter->bIsAlive = false;
					Reset_Particle(&*iter);
				}
			}
		}
		iter++;
	}

	return Engine::_int();
}

void CVomit::freeMem()
{
	if (m_pVB != nullptr)
		m_pVB->Release();
	if (m_pTexture != nullptr)
		m_pTexture->Release();

	CParticle::freeMem();
}

CVomit * CVomit::Create()
{
	CVomit*	pInstance = new CVomit();
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

CVomit * CVomit::Clone(const Engine::_vec3 * pPos)
{
	return new CVomit(*this);
}