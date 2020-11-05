#include "stdafx.h"
#include "Terrain.h"

USING(Engine)

CTerrain::CTerrain(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pMesh(nullptr)
	, m_pNaviMesh(nullptr)
	, m_pShaderCom(nullptr)
{
}

CTerrain::CTerrain(const CTerrain & rhs)
	: CGameObject(rhs)
	, m_pMesh(nullptr)
	, m_pNaviMesh(nullptr)
	, m_pShaderCom(nullptr)
{
}

CTerrain::~CTerrain(void)
{
}

HRESULT CTerrain::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	CNaviMesh::Create(m_pGraphicDev)->Attach(L"NaviMesh", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"MeshShader", this, ID_STATIC);

	return S_OK;
}

HRESULT CTerrain::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pMesh = Get_Component<CStaticMesh>(L"Mesh", ID_STATIC);
	m_pNaviMesh = Get_Component<CNaviMesh>(L"NaviMesh", ID_STATIC);
	m_pShaderCom = Get_Component<CShader>(L"MeshShader", ID_STATIC);

	return S_OK;
}

Engine::_int CTerrain::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_NONALPHA, this);

	return iExit;
}

void CTerrain::Render_GameObject(void)
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

	if (m_pNaviMesh && g_bNaviRender)
	{
		m_pNaviMesh->Render_NaviMesh();
	}
}

void CTerrain::Initialize_Terrain(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_vec3 * pAngle, const Engine::_tchar * pKey)
{
	auto pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	pTransform->Set_Info(INFO::INFO_POS, pPos);
	pTransform->Set_Scale(pScale);
	pTransform->Set_Angle(pAngle);
	set_Name(pKey);

	DLL::pResourcesMgr->Clone<CStaticMesh>(RESOURCE_STATIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);
}

void CTerrain::Add_Cell(const Engine::_vec3 * pPos1, const Engine::_vec3 * pPos2, const Engine::_vec3 * pPos3)
{
	m_pNaviMesh->Add_Cell(pPos1, pPos2, pPos3);
}

void CTerrain::Link_NaviMesh(void)
{
	m_pNaviMesh->Link_Cell();
}

Engine::_ulong CTerrain::Find_CellIndex(const Engine::_vec3 * pPos)
{
	auto pVector = m_pNaviMesh->Get_Vec();

	_vec3 vDown(0.f, -1.f, 0.f);
	_float fU, fV, fDist;

	for (auto iter : *pVector)
	{
		auto pPos1 = iter->Get_Point(CCell::POINT_A);
		auto pPos2 = iter->Get_Point(CCell::POINT_B);
		auto pPos3 = iter->Get_Point(CCell::POINT_C);

		if (D3DXIntersectTri(pPos1, pPos2, pPos3, pPos, &vDown, &fU, &fV, &fDist))
		{
			return *iter->Get_Index();
		}
	}

	return 0;

}

CTerrain* CTerrain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrain* pInstance = new CTerrain(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

Engine::CGameObject * CTerrain::Clone(void)
{
	return new CTerrain(*this);
}

HRESULT CTerrain::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
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