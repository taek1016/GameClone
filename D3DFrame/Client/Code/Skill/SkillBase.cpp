#include "stdafx.h"
#include "SkillBase.h"

USING(Engine)

CSkillBase::CSkillBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pShaderCom(nullptr)
	, m_fColRadius(0.f)
	, m_pCollider(nullptr)
	, m_eCollType(COLLTYPE::COL_FALSE)
	, m_iDamage(0)
	, m_dwNaviIndex(0)
	, m_vDir(0.f, 0.f, 0.f)
{
}

CSkillBase::CSkillBase(const CSkillBase & rhs)
	: CGameObject(rhs)
	, m_pShaderCom(rhs.m_pShaderCom)
	, m_fColRadius(rhs.m_fColRadius)
	, m_iDamage(rhs.m_iDamage)
	, m_dwNaviIndex(0)
	, m_vDir(0.f, 0.f, 0.f)
	, m_eCollType(COLLTYPE::COL_FALSE)
{
	if (rhs.m_pTransform)
	{
		m_pTransform = dynamic_cast<CTransform*>(rhs.m_pTransform->Clone());
		m_pTransform->Attach(L"Transform", this, ID_DYNAMIC);
	}
	if (rhs.m_pCollider)
	{
		m_pCollider = dynamic_cast<CSphereCollider*>(rhs.m_pCollider->Clone());
		m_pCollider->Attach(L"MainSphereCol", this, ID_STATIC);
	}
}

CSkillBase::~CSkillBase(void)
{
}

HRESULT CSkillBase::SetUp_ConstantTable(LPD3DXEFFECT & pEffect)
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

void CSkillBase::Set_Dir(const Engine::_vec3 * pDir)
{
	m_vDir = *pDir;
}

void CSkillBase::Set_Damage(const Engine::_int & iDamage)
{
	m_iDamage = iDamage;
}

void CSkillBase::SetUp_Index(void)
{
	m_dwNaviIndex = DLL::pPickMgr->Get_Index(m_pTransform->Get_Info(INFO_POS));
}

void CSkillBase::set_Collider(void)
{
	m_pCollider->Set_Collider(m_pTransform->Get_World());
}

void CSkillBase::read_Data(void)
{
	// 데미지, 콜라이더 크기
	const _tchar* pPath = L"../../Data/PrefabData/SkillPrefab.ini";
	m_iDamage = GetPrivateProfileInt(m_wStrName.c_str(), L"Damage", 0, pPath);

	m_fColRadius = get_ReadData(L"MainCollider");

	if (m_fColRadius > FLT_EPSILON)
	{
		m_pCollider = CSphereCollider::Create(m_pGraphicDev, m_fColRadius, 10, 10, m_pTransform->Get_World());
		m_pCollider->Attach(L"MainSphereCol", this, ID_STATIC);
	}

	_vec3 vScale;
	vScale.x = get_ReadData(L"ScaleX");
	vScale.y = get_ReadData(L"ScaleY");
	vScale.z = get_ReadData(L"ScaleZ");
	m_pTransform->Set_Scale(&vScale);
}

Engine::_float CSkillBase::get_ReadData(const Engine::_tchar * pKey)
{
	const _int iMaxStr = 256;
	_tchar szValue[iMaxStr]{};
	GetPrivateProfileString(m_wStrName.c_str(), pKey, L"0.f", szValue, iMaxStr, L"../../Data/PrefabData/SkillPrefab.ini");

	return static_cast<_float>(_wtof(szValue));
}
