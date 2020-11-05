#include "stdafx.h"
#include "MeshEffectBase.h"

USING(Engine)

CMeshEffectBase::CMeshEffectBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEffectBase(pGraphicDev)
	, m_pMesh(nullptr)
	, m_pShader(nullptr)
	, m_bDead(false)
{
}

CMeshEffectBase::CMeshEffectBase(const CMeshEffectBase & rhs)
	: CEffectBase(rhs)
	, m_pShader(rhs.m_pShader)
	, m_bDead(false)
{
}

HRESULT CMeshEffectBase::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	DLL::pResourcesMgr->Clone<CDynamicMesh>(RESOURCE_DYNAMIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"Shader", this, ID_STATIC);

	return S_OK;
}

HRESULT CMeshEffectBase::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pMesh = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);
	m_pShader = Get_Component<CShader>(L"Shader", ID_STATIC);

	return S_OK;
}

Engine::_int CMeshEffectBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (m_bDead)
	{
		DLL::pEffectMgr->Back_Pool(m_wStrName.c_str(), this);
		return BACK_POOL;
	}

	act_Determine(fTimeDelta);

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	m_pMesh->Play_Animation(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CMeshEffectBase::Render_GameObject(void)
{
	LPD3DXEFFECT	pEffect = m_pShader->Get_EffectHandle();
	NULL_CHECK(pEffect);
	pEffect->AddRef();

	_uint	iPassMax = 0;

	FAILED_CHECK_RETURN(setUp_ConstantTable(pEffect), );

	pEffect->Begin(&iPassMax, 0);

	pEffect->BeginPass(2);

	m_pMesh->Render_Meshes(pEffect);

	pEffect->EndPass();

	pEffect->End();

	Safe_Release(pEffect);
}

void CMeshEffectBase::Set_Target(Engine::CGameObject * pTarget)
{
	m_pTarget = pTarget;
	m_pTarget->AddRef();

	m_pTargetTransform = m_pTarget->Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pTargetTransform->AddRef();
}

void CMeshEffectBase::read_Data(void)
{
	_vec3 vScale;
	vScale.x = get_ReadData(L"ScaleX");
	vScale.y = get_ReadData(L"ScaleY");
	vScale.z = get_ReadData(L"ScaleZ");

	m_pTransform->Set_Scale(&vScale);
}

Engine::_float CMeshEffectBase::get_ReadData(const Engine::_tchar * pKey)
{
	const _int iMaxStr = 256;
	_tchar szValue[iMaxStr]{};
	GetPrivateProfileString(m_wStrName.c_str(), pKey, L"0.f", szValue, iMaxStr, L"../../Data/PrefabData/MeshEffectPrefab.ini");

	return static_cast<_float>(_wtof(szValue));
}

HRESULT CMeshEffectBase::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
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
