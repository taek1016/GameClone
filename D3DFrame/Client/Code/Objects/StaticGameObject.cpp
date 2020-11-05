#include "stdafx.h"
#include "StaticGameObject.h"

USING(Engine)

CStaticObject::CStaticObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	
	, m_fRadius(0.f)

	, m_pMesh(nullptr)
	, m_pSphereCol(nullptr)
	, m_pShaderCom(nullptr)
{
}

CStaticObject::CStaticObject(const CStaticObject & rhs)
	: CGameObject(rhs)

	, m_pMesh(nullptr)
	, m_pSphereCol(nullptr)
	, m_pShaderCom(nullptr)
{
}

CStaticObject::~CStaticObject(void)
{
}

HRESULT CStaticObject::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	DLL::pResourcesMgr->Clone<CStaticMesh>(RESOURCE_STATIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"MeshShader", this, ID_STATIC);

	return S_OK;
}

HRESULT CStaticObject::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pMesh = Get_Component<CStaticMesh>(L"Mesh", ID_STATIC);
	m_pSphereCol = Get_Component<CSphereCollider>(L"Collider", ID_STATIC);
	m_pShaderCom = Get_Component<CShader>(L"MeshShader", ID_STATIC);

	return S_OK;
}

Engine::_int CStaticObject::Update_GameObject(const _float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	if (DLL::pOptimizationMgr->Is_InFrustum_Object(m_pTransform->Get_Info(INFO::INFO_POS), m_fRadius))
	{	
		DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);
	}

	return iExit;
}

void CStaticObject::Render_GameObject()
{
	LPD3DXEFFECT	pEffect = m_pShaderCom->Get_EffectHandle();
	NULL_CHECK(pEffect);
	pEffect->AddRef();

	_uint	iPassMax = 0;

	FAILED_CHECK_RETURN(setUp_ConstantTable(pEffect), );

	pEffect->Begin(&iPassMax, 0);

	pEffect->BeginPass(0);

	m_pMesh->Render_Meshes(pEffect);

	pEffect->EndPass();

	pEffect->End();

	Safe_Release(pEffect);

	if (g_bCollider && m_pSphereCol)
	{
		const _matrix* pMatrix = m_pTransform->Get_World();

		_matrix matCopy;
		D3DXMatrixIdentity(&matCopy);

		memcpy(&matCopy.m[3], pMatrix->m[3], sizeof(_vec3));

		m_pSphereCol->Render_Collider(COL_FALSE);
	}
}

void CStaticObject::Make_Collider(const _vec3* pPos, const Engine::_float & fRadius)
{
	m_pTransform->Set_Info(INFO::INFO_POS, pPos);
	m_pTransform->Update_Component(0.f);
	set_Radius(fRadius);

	CSphereCollider::Create(m_pGraphicDev, m_fRadius, 10, 10, m_pTransform->Get_World())->Attach(L"Collider", this, ID_STATIC);
}

void CStaticObject::set_RenderKey(const Engine::_tchar * pKey)
{
	m_wStrName = pKey;
}

void CStaticObject::set_Radius(const Engine::_float & fRadius)
{
	m_fRadius = fRadius;
}

HRESULT CStaticObject::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	_matrix			matWorld, matView, matProj;

	matWorld = *m_pTransform->Get_World();
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	const D3DLIGHT9*		pLight = DLL::pLightMgr->Get_LightInfo(0);
	NULL_CHECK_RETURN(pLight, S_OK);


	pEffect->SetVector("g_vLightDir", &_vec4(pLight->Direction, 0.f));
	pEffect->SetVector("g_vLightDiffuse", (_vec4*)&pLight->Diffuse);
	pEffect->SetVector("g_vLightSpecular", (_vec4*)&pLight->Specular);
	pEffect->SetVector("g_vLightAmbient", (_vec4*)&pLight->Ambient);


	D3DMATERIAL9		tMtrlInfo;
	ZeroMemory(&tMtrlInfo, sizeof(D3DMATERIAL9));

	tMtrlInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	tMtrlInfo.Power = 100.f;

	pEffect->SetVector("g_vMtrlDiffuse", (_vec4*)&tMtrlInfo.Diffuse);
	pEffect->SetVector("g_vMtrlSpecular", (_vec4*)&tMtrlInfo.Specular);
	pEffect->SetVector("g_vMtrlAmbient", (_vec4*)&tMtrlInfo.Ambient);

	_vec4		vCamPos;
	D3DXMatrixInverse(&matView, NULL, &matView);
	memcpy(&vCamPos, &matView.m[3][0], sizeof(_vec4));

	pEffect->SetVector("g_vCamPos", &vCamPos);
	pEffect->SetFloat("g_fPower", tMtrlInfo.Power);

	return S_OK;
}

CStaticObject * CStaticObject::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar * pKey)
{
	CStaticObject* pInstance = new CStaticObject(pGraphicDev);

	pInstance->set_RenderKey(pKey);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	pInstance->Late_Initialize();
	return pInstance;
}

Engine::CGameObject * CStaticObject::Clone(void)
{
	CStaticObject* pInstance = new CStaticObject(*this);

	pInstance->Late_Initialize();

	return pInstance;
}

inline void CStaticObject::Free(void)
{
	CGameObject::Free();
	m_pMesh = nullptr;
	m_pSphereCol = nullptr;
	m_pTransform = nullptr;
}
