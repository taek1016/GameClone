#include "stdafx.h"
#include "FrostBolt.h"

#include "Character/Player.h"

USING(Engine)

CFrostBolt::CFrostBolt(LPDIRECT3DDEVICE9 pGraphicDev)
	: CAttackSkillBase(pGraphicDev)
	, m_fSpeed(0.f)
	, m_pTarget(nullptr)
{
	set_Name(L"FrostBolt");
}

CFrostBolt::CFrostBolt(const CFrostBolt & rhs)
	: CAttackSkillBase(rhs)
	, m_fSpeed(0.f)
	, m_pTarget(nullptr)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	rhs.m_pMesh->Clone()->Attach(L"Mesh", this, ID_STATIC);
}

CFrostBolt::~CFrostBolt(void)
{
}

HRESULT CFrostBolt::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	DLL::pResourcesMgr->Clone<CDynamicMesh>(RESOURCE_DYNAMIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);

	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"MeshShader", this, ID_STATIC);

	return S_OK;
}

HRESULT CFrostBolt::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pMesh = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);

	m_pTransform->Rotation(ROT_X, D3DXToRadian(90.f));

	m_pShaderCom = Get_Component<CShader>(L"MeshShader", ID_STATIC);

	return S_OK;
}

void CFrostBolt::Attack(CGameObject* pTarget)
{
	dynamic_cast<CCharacterBase*>(m_pTarget)->Hit(m_iDamage);
}

void CFrostBolt::act_Determine(const Engine::_float& fTimeDelta)
{
	_vec3 vDir(0.f, 0.f, 0.f);

	if (m_pTarget)
	{
		auto pTargetPos = m_pTarget->Get_Pos();
		m_pTransform->Compute_LookAtTarget(pTargetPos);

		vDir = *pTargetPos - *m_pTransform->Get_Info(INFO_POS);
		
		D3DXVec3Normalize(&vDir, &vDir);
		vDir *= m_fSpeed;
	}
	else
	{
		m_bDead = true;
		return;
	}
	m_pTransform->Move_Pos(&vDir);

	auto pList = DLL::pObjMgr->Get_ObjList(L"Monster");

	if (CollideFunc::SphereToSphere(m_pCollider, m_pTarget->Get_Component<CSphereCollider>(L"MainSphereCol", ID_STATIC)))
	{
		Attack(m_pTarget);
		check_DeadCondition();
	}
}

CFrostBolt * CFrostBolt::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_float& fRadius)
{
	CFrostBolt* pInstance = new CFrostBolt(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CFrostBolt::Clone(void)
{
	CFrostBolt* pInstance = new CFrostBolt(*this);

	pInstance->Late_Initialize();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front());
	
	pInstance->Set_Pos(&pPlayer->Get_SkillHandPosition(true));
	pInstance->set_Target();
	pInstance->set_Damage(pPlayer->Get_Damage());

	return pInstance;
}

void CFrostBolt::set_Damage(const Engine::_int & iDamage)
{
	m_iDamage += iDamage;
}

void CFrostBolt::set_Target(void)
{
	m_pTarget = DLL::pMouseMgr->Get_PickTarget();

	if (nullptr == m_pTarget)
	{
		m_bDead = true;
	}
	else
	{
		auto pTargetPos = m_pTarget->Get_Pos();
		_vec3 vDir = *pTargetPos - *m_pTransform->Get_Info(INFO_POS);
		m_fSpeed = D3DXVec3Length(&vDir) * 0.025f;
		m_pTransform->Rotation(ROT_X, D3DXToRadian(-90.f));
		m_pTransform->Compute_LookAtTarget(pTargetPos);
		set_Collider();
	}
}

void CFrostBolt::check_DeadCondition(void)
{
	m_bDead = true;
}

void CFrostBolt::dead_Effect(void)
{
}
