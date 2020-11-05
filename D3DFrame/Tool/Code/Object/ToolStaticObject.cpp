#include "stdafx.h"
#include "ToolStaticObject.h"

#include "Transform.h"
#include "StaticMesh.h"
#include "Shader.h"

USING(Engine)
CToolStaticObject::CToolStaticObject(LPDIRECT3DDEVICE9 pGraphcDev)
	: CToolGameObject(pGraphcDev)
	, m_tInfo()
	, m_pStaticMesh(nullptr)
	, m_fRadius(0.f)
{
}

CToolStaticObject::CToolStaticObject(const CToolStaticObject& rhs)
	: CToolGameObject(rhs)
	, m_tInfo(rhs.m_tInfo)
	, m_pStaticMesh(nullptr)
	, m_fRadius(rhs.m_fRadius)
{
}

CToolStaticObject::~CToolStaticObject(void)
{
}

HRESULT CToolStaticObject::Initialize_GameObject(void)
{
	Engine::CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	DLL::pResourcesMgr->Clone<CStaticMesh>(0, m_tInfo.wStrRenderKey.c_str())->Attach(L"Mesh", this, ID_STATIC);

	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"MeshShader", this, ID_STATIC);

	return S_OK;
}

HRESULT CToolStaticObject::Late_Initialize(void)
{
	m_pStaticMesh = Engine::CGameObject::Get_Component<CStaticMesh>(L"Mesh", ID_STATIC);
	m_pTransform = Engine::CGameObject::Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pShaderCom = Get_Component<CShader>(L"MeshShader", ID_STATIC);
	return S_OK;
}

Engine::_int CToolStaticObject::Update_GameObject(const Engine::_float & fTimeDelta)
{
	return CGameObject::Update_GameObject(fTimeDelta);
}

void CToolStaticObject::Render_GameObject(void)
{
	const Engine::_matrix* pMatrix = m_pTransform->Get_World();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, pMatrix);

	if (m_pStaticMesh)
	{
		LPD3DXEFFECT	pEffect = m_pShaderCom->Get_EffectHandle();
		NULL_CHECK(pEffect);
		pEffect->AddRef();

		_uint	iPassMax = 0;

		FAILED_CHECK_RETURN(SetUp_ConstantTable(pEffect), );

		pEffect->Begin(&iPassMax, 0);

		pEffect->BeginPass(0);

		m_pStaticMesh->Render_Meshes(pEffect);

		pEffect->EndPass();

		pEffect->End();

		Safe_Release(pEffect);
	}

	if (m_pCollider && bColliderRender)
	{
		Engine::_matrix matColWorld;
		D3DXMatrixIdentity(&matColWorld);

		memcpy(&matColWorld.m[3], pMatrix->m[3], sizeof(Engine::_vec3));
		m_pCollider->Render_Collider(COL_FALSE);
	}
}

void CToolStaticObject::Add_Collider(Engine::CCollider * pCol, const Engine::_float& fRadius)
{
	if (m_pCollider)
	{
		Engine::Safe_Release(m_pCollider);
	}

	m_fRadius = fRadius;
	m_pCollider = pCol;
	
}

const Engine::_float & CToolStaticObject::Get_Radius(void) const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_fRadius;
}

const Engine::_tchar * CToolStaticObject::Get_RenderKey(void) const
{
	return m_tInfo.wStrRenderKey.c_str();
}

void CToolStaticObject::Set_RenderKey(const wstring & wStrRenderKey)
{
	m_tInfo.wStrRenderKey = wStrRenderKey;
}

void CToolStaticObject::Set_Info(const OBJECT_INFO & tInfo)
{
	m_pTransform->Set_Info(INFO_POS, &tInfo.tInfo.vPos);
	m_pTransform->Set_Scale(&tInfo.tInfo.vScale);
	m_pTransform->Set_Angle(&tInfo.tInfo.vAngle);

	m_tInfo.wStrRenderKey = tInfo.wStrRenderKey;
}

void CToolStaticObject::Move_X(const Engine::_float & fX)
{
	_vec3 vMove(fX, 0.f, 0.f);

	m_pTransform->Move_Pos(&vMove);
}

void CToolStaticObject::Move_Y(const Engine::_float & fY)
{
	_vec3 vMove = *m_pTransform->Get_Info(INFO_POS);

	vMove.y += fY;

	m_pTransform->Set_Info(INFO_POS, &vMove);
}

void CToolStaticObject::Move_Z(const Engine::_float & fZ)
{
	_vec3 vMove = *m_pTransform->Get_Info(INFO_POS);

	vMove.z += fZ;

	m_pTransform->Set_Info(INFO_POS, &vMove);
}

void CToolStaticObject::Scale_X(const Engine::_float & fX)
{
	_vec3 vScale = *m_pTransform->Get_Scale();

	vScale.x += fX;

	m_pTransform->Set_Scale(&vScale);

}

void CToolStaticObject::Scale_Y(const Engine::_float & fY)
{
	_vec3 vScale = *m_pTransform->Get_Scale();

	vScale.y += fY;

	m_pTransform->Set_Scale(&vScale);
}

void CToolStaticObject::Scale_Z(const Engine::_float & fZ)
{
	_vec3 vScale = *m_pTransform->Get_Scale();

	vScale.z += fZ;

	m_pTransform->Set_Scale(&vScale);
}

void CToolStaticObject::Rot_X(const Engine::_float & fX)
{
	m_pTransform->Rotation(ROT_X, (fX));
}

void CToolStaticObject::Rot_Y(const Engine::_float & fY)
{
	m_pTransform->Rotation(ROT_Y, (fY));
}

void CToolStaticObject::Rot_Z(const Engine::_float & fZ)
{
	m_pTransform->Rotation(ROT_Z, (fZ));
}

void CToolStaticObject::Set_Name(const Engine::_tchar * pKey)
{
	m_wStrName = pKey;
	m_tInfo.wStrRenderKey = pKey;
}

const OBJECT_INFO* CToolStaticObject::Get_Info(void)
{
	return &m_tInfo;
}

const Engine::_vec3 * CToolStaticObject::Get_Scale(void) const
{
	return m_pTransform->Get_Scale();
}

const Engine::_vec3 * CToolStaticObject::Get_Angle(void) const
{
	return m_pTransform->Get_Angle();
}

HRESULT CToolStaticObject::SetUp_ConstantTable(LPD3DXEFFECT & pEffect)
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

void CToolStaticObject::SaveData(HANDLE hFile)
{

}

void CToolStaticObject::LoadData(HANDLE hFile)
{

}

CToolStaticObject* CToolStaticObject::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar* pRenderKey)
{
	CToolStaticObject* pInstance = new CToolStaticObject(pGraphicDev);

	pInstance->Set_Name(pRenderKey);
	pInstance->Set_RenderKey(pRenderKey);
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CToolStaticObject::Clone(void)
{
	CToolStaticObject* pInstance = new CToolStaticObject(*this);

	const _int iMaxStr = 256;
	TCHAR szName[iMaxStr]{};
	lstrcpy(szName, Get_Name());

	static _int iCount = 0;
	wsprintf(szName, L"%s%d", szName, iCount++);

	pInstance->set_Name(szName);

	return pInstance;
}

inline void CToolStaticObject::Free(void)
{
	CToolGameObject::Free();
}
