#include "stdafx.h"
#include "TextureSkillBase.h"

USING(Engine)

CTextureSkillBase::CTextureSkillBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSkillBase(pGraphicDev)
	, m_fCurIndex(0.f)
	, m_fCurDeltaTime(0.f)
	, m_fMaxSize(0.f)
	, m_pBuffer(nullptr)
	, m_pTexture(nullptr)
	, m_bDead(false)
	, m_vScale(0.f, 0.f, 0.f)
	, m_pCollider(nullptr)
{
}

CTextureSkillBase::CTextureSkillBase(const CTextureSkillBase & rhs)
	: CSkillBase(rhs)
	, m_fCurIndex(0.f)
	, m_fCurDeltaTime(0.f)
	, m_fMaxSize(rhs.m_fMaxSize)
	, m_bDead(false)
	, m_vScale(rhs.m_vScale)
	, m_pCollider(nullptr)
{
	if (rhs.m_pTexture)
	{
		rhs.m_pTexture->Clone()->Attach(L"Texture", this, ID_STATIC);
	}

	if (rhs.m_pBuffer)
	{
		rhs.m_pBuffer->Clone()->Attach(L"Buffer", this, ID_STATIC);
	}

	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	if (rhs.m_pShaderCom)
	{
		rhs.m_pShaderCom->Clone()->Attach(L"Shader", this, ID_STATIC);
	}
}

HRESULT CTextureSkillBase::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);
	DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, m_wStrName.c_str())->Attach(L"Texture", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Liquid")->Attach(L"Shader", this, ID_STATIC);

	return S_OK;
}

HRESULT CTextureSkillBase::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pBuffer = Get_Component<CRcTex>(L"Buffer", ID_STATIC);
	m_pTexture = Get_Component<CTexture>(L"Texture", ID_STATIC);
	m_pShaderCom = Get_Component<CShader>(L"Shader", ID_STATIC);

	return S_OK;
}

Engine::_int CTextureSkillBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (m_bDead)
	{
		dead_Action(fTimeDelta);
		return DEAD_OBJ;
	}

	check_TextureIndex(fTimeDelta);

	act_Determine(fTimeDelta);

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
	m_fCurDeltaTime = fTimeDelta;

	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CTextureSkillBase::Render_GameObject(void)
{	
	LPD3DXEFFECT	pEffect = m_pShaderCom->Get_EffectHandle();
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

	if (g_bCollider && m_pCollider)
	{
		m_pCollider->Render_Collider(m_eCollType, m_pTransform->Get_World());
	}
}

void CTextureSkillBase::set_Index(const Engine::_float & fMaxIndex)
{
	m_fCurIndex = 0.f;
	m_fMaxSize = fMaxIndex;
}

HRESULT CTextureSkillBase::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	//_matrix			matWorld, matView, matProj;

	//matWorld = CameraFunc::Make_BillBoard(m_pGraphicDev, m_pTransform);
	//m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	//m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	//pEffect->SetMatrix("g_matWorld", &matWorld);
	//pEffect->SetMatrix("g_matView", &matView);
	//pEffect->SetMatrix("g_matProj", &matProj);

	//m_pTexture->Set_Texture(pEffect, "g_BaseTexture", _uint(m_fCurIndex));
	//DLL::pRenderTarget->SetUp_OnShader(pEffect, L"Target_Depth", "g_DepthTexture");
	_matrix matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->Get_World());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	_vec4 vCameraPos;
	_matrix matViewInv;
	D3DXMatrixInverse(&matViewInv, NULL, &matView);
	memcpy(&vCameraPos, matViewInv.m[3], sizeof(_vec4));

	const D3DLIGHT9*		pLight = DLL::pLightMgr->Get_LightInfo(0);
	NULL_CHECK_RETURN(pLight, S_OK);

	pEffect->SetFloat("g_fTime", m_fCurIndex / 4.f);
	m_pTexture->Set_Texture(pEffect, "g_DiffuseSampler_Tex", 0);

	return S_OK;
}
