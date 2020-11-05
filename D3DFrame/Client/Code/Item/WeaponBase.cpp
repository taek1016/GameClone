#include "stdafx.h"
#include "WeaponBase.h"

#include "Sphere.h"
#include "Character/Character.h"

USING(Engine)

CWeaponBase::CWeaponBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItemBase(pGraphicDev)
	, m_bCollided(false)
	, m_bGiveDamage(false)
	, m_bAttackOrder(false)
	
	, m_iDamage(0)

	, m_pTarget(nullptr)
	, m_pMesh(nullptr)

	, m_eColType(COLLTYPE::COL_FALSE)
{
}

CWeaponBase::CWeaponBase(const CWeaponBase & rhs)
	: CItemBase(rhs)
	, m_bCollided(false)
	, m_bGiveDamage(false)
	, m_bAttackOrder(false)
	, m_pTarget(nullptr)
	, m_eColType(COLLTYPE::COL_FALSE)
	, m_iDamage(rhs.m_iDamage)
{
	for (auto iter : rhs.m_listCollider)
	{
		m_listCollider.push_back(dynamic_cast<CSphereCollider*>(iter->Clone()));
	}

	if (nullptr != rhs.m_pMesh)
	{
		m_pMesh = dynamic_cast<CStaticMesh*>(rhs.m_pMesh->Clone());
	}
}

CWeaponBase::~CWeaponBase(void)
{
}

HRESULT CWeaponBase::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	if (!m_wStrName.empty())
	{
		DLL::pResourcesMgr->Clone<CStaticMesh>(RESOURCE_STATIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);
		DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"MeshShader", this, ID_STATIC);
	}

	return S_OK;
}

HRESULT CWeaponBase::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);

	if (!m_wStrName.empty())
	{
		m_pShaderCom = Get_Component<CShader>(L"MeshShader", ID_STATIC);
		m_pMesh = Get_Component<CStaticMesh>(L"Mesh", ID_STATIC);
	}

	return S_OK;
}

_int CWeaponBase::Update_GameObject(const _float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	if (m_bAttackOrder)
	{
		m_bCollided = check_Collide();
	}

	if (m_bCollided)
	{
		if (m_bGiveDamage)
		{
			m_eColType = COL_DURING_ATTACK;
		}
		else
		{
			m_eColType = COL_ATTACK_START;
			attack();
		}
	}
	else
	{
		m_bGiveDamage = false;
	}

	if (nullptr != m_pMatParentBone)
	{
		auto pMatrix = m_pTransform->Get_World();
		_matrix matParentConverter = *m_pMatParentBone * *m_pMatParentWorld;
		m_pTransform->Set_WorldMatrix(&(*pMatrix * matParentConverter));
	}
	else if (nullptr == m_pMatParentBone)
	{
		auto pMatrix = m_pTransform->Get_World();
		_matrix matParentConverter = *m_pMatParentWorld;
		m_pTransform->Set_WorldMatrix(&(*pMatrix * matParentConverter));
	}

	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CWeaponBase::Render_GameObject(void)
{
	if (nullptr != m_pMesh)
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
	}

	if (g_bAttackCol)
	{
		auto pMatWorld = m_pTransform->Get_World();

		for (auto iter : m_listCollider)
		{
			iter->Render_Collider(m_eColType, pMatWorld);
		}
	}
}

void CWeaponBase::AttackAct(void)
{
	m_bAttackOrder = true;
}

void CWeaponBase::Cancel_Attack(void)
{
	m_eColType = COL_FALSE;
	m_bCollided = false;
	m_bAttackOrder = false;
	m_bGiveDamage = false;
}

void CWeaponBase::Update_Matrix(const Engine::_matrix * pMat)
{
	m_pTransform->Set_WorldMatrix(pMat);
}

void CWeaponBase::Set_Damage(const Engine::_int iDamage)
{
	m_iDamage = iDamage;
}

void CWeaponBase::Set_Target(CCharacterBase* pTarget)
{
	if (nullptr != m_pTarget)
	{
		Safe_Release(m_pTarget);
	}

	m_pTarget = pTarget;
	m_pTarget->AddRef();
}

void CWeaponBase::Set_ColliderMat(const Engine::_matrix * pWorld, const Engine::_matrix * pBone, const _vec3 * pStartPos)
{
	m_pMatParentWorld = pWorld;
	m_pMatParentBone = pBone;

	_int iSize = static_cast<_int>(m_fLength / m_fSingleSphereRadius);
	for (_int i = 0; i < iSize; ++i)
	{
		m_listCollider.push_back(CSphereCollider::Create(m_pGraphicDev, m_fSingleSphereRadius, 10, 10, pWorld, pBone, pStartPos));
	}
}

void CWeaponBase::attack(void)
{
	if (false == m_bGiveDamage)
	{
		m_pTarget->Hit(m_iDamage);
		m_bGiveDamage = true;
	}
}

void CWeaponBase::initialize_Colliders(const Engine::_float & fLength, const Engine::_float & fSingleRadius)
{
	m_fSingleSphereRadius = fSingleRadius;
	m_fLength = fLength;
}

Engine::_bool CWeaponBase::check_Collide(void)
{
	_bool bIsCollided = false;

	for (auto iter : m_listCollider)
	{
		if (CollideFunc::ActionColToPlayer(iter, DLL::pObjMgr->Get_ObjList(L"Player")->front()))
		{
			bIsCollided = true;
			break;
		}
	}

	return bIsCollided;
}

HRESULT CWeaponBase::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
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
inline void CWeaponBase::Free(void)
{
	CGameObject::Free();

	for (auto iter : m_listCollider)
	{
		Safe_Release(iter);
	}
	Safe_Release(m_pTarget);
}
