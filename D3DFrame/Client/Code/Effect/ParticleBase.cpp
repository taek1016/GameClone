#include "stdafx.h"
#include "ParticleBase.h"

USING(Engine)

CParticleBase::CParticleBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEffectBase(pGraphicDev)
	, m_pShader(nullptr)
	, m_pBuffer(nullptr)
	, m_pTexture(nullptr)
	, m_pRigidBody(nullptr)

	, m_fFrameCnt(0.f)
	, m_fFrameMax(0.f)
	, m_fSpeed(0.f)

	, m_fCurTime(0.f)
	, m_fDeadTime(0.f)
	, m_vDir(0.f, 0.f, 0.f)
{
}

CParticleBase::CParticleBase(const CParticleBase & rhs)
	: CEffectBase(rhs)
	, m_pShader(rhs.m_pShader)
	, m_pBuffer(rhs.m_pBuffer)
	, m_pTexture(rhs.m_pTexture)

	, m_fFrameCnt(0.f)
	, m_fFrameMax(0.f)
	, m_fSpeed(0.f)

	, m_fCurTime(0.f)
	, m_fDeadTime(rhs.m_fDeadTime)
	, m_vDir(rhs.m_vDir)
{
	m_pShader->AddRef();
	m_pBuffer->AddRef();
	m_pTexture->AddRef();

	if (rhs.m_pTransform)
	{
		m_pTransform = dynamic_cast<CTransform*>(rhs.m_pTransform->Clone());
		m_pTransform->Attach(L"Transform", this, ID_DYNAMIC);
	}

	if (rhs.m_pRigidBody)
	{
		m_pRigidBody = dynamic_cast<CRigidBody*>(rhs.m_pRigidBody->Clone());
		m_pRigidBody->Attach(L"RigidBody", this, ID_DYNAMIC);
	}
}

void CParticleBase::Set_Dir(const Engine::_vec3 * pDir)
{
	m_vDir = *pDir;
}

HRESULT CParticleBase::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	
	m_pBuffer = CRcTex::Create(m_pGraphicDev);
	m_pBuffer->Attach(L"Buffer", this, ID_STATIC);

	m_pShader = DLL::pShaderMgr->Clone_Shader(L"Shader_Effect");
	m_pShader->Attach(L"Shader", this, ID_STATIC);

	return S_OK;
}

HRESULT CParticleBase::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	
	return S_OK;
}

Engine::_int CParticleBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	m_fCurTime += fTimeDelta;
	if (m_fCurTime >= m_fDeadTime)
	{
		DLL::pEffectMgr->Back_Pool(m_wStrName.c_str(), this);
		return BACK_POOL;
	}

	move_Particle(fTimeDelta);

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	_matrix	matWorld, matView, matBill;

	matWorld = *m_pTransform->Get_World();
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixIdentity(&matBill);

	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, NULL, &matBill);

	m_pTransform->Set_WorldMatrix(&(matBill * matWorld));

	CGameObject::Compute_ViewZ();

	DLL::pRenderer->Add_RenderGroup(RENDER_NONALPHA, this);

	return iExit;
}

void CParticleBase::Render_GameObject(void)
{
	LPD3DXEFFECT	pEffect = m_pShader->Get_EffectHandle();
	NULL_CHECK(pEffect);
	pEffect->AddRef();

	_uint	iPassMax = 0;

	FAILED_CHECK_RETURN(setUp_ConstantTable(pEffect), );

	pEffect->Begin(&iPassMax, 0);

	pEffect->BeginPass(0);

	m_pBuffer->Render_Buffer();

	pEffect->EndPass();

	pEffect->End();

	Safe_Release(pEffect);
}

void CParticleBase::Set_Speed(const Engine::_float & fSpeed)
{
	m_fSpeed = fSpeed;
}

void CParticleBase::set_Texture(const D3DXCOLOR & tColor)
{
	m_pGraphicDev->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture, NULL);

	D3DLOCKED_RECT	tLockRect;
	ZeroMemory(&tLockRect, sizeof(D3DLOCKED_RECT));

	m_pTexture->LockRect(0, &tLockRect, NULL, NULL);

	*((_ulong*)tLockRect.pBits) = tColor;

	m_pTexture->UnlockRect(0);
}

void CParticleBase::set_Speed(const Engine::_float & fSpeed)
{
	m_fSpeed = fSpeed;
}

void CParticleBase::set_DeadTime(const Engine::_float & fDeadTime)
{
	m_fDeadTime = fDeadTime;
}

void CParticleBase::set_MaxFrame(const Engine::_float & fMaxFrame)
{
	m_fFrameMax = fMaxFrame;
}

HRESULT CParticleBase::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	_matrix			matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->Get_World());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	pEffect->SetTexture("g_BaseTexture", m_pTexture);
	DLL::pRenderTarget->SetUp_OnShader(pEffect, L"Target_Depth", "g_DepthTexture");

	return S_OK;
}

inline void CParticleBase::Free(void)
{
	CEffectBase::Free();

	Safe_Release(m_pTexture);
}
