#include "stdafx.h"
#include "FrostNova.h"

#include "Character/Player.h"
USING(Engine)

CFrostNova::CFrostNova(LPDIRECT3DDEVICE9 pGraphicDev)
	: CAttackSkillBase(pGraphicDev)
	, m_bAttack(false)
	, m_fColRadius(0.f)
	, m_fDuration(0.8f)
	, m_fCurTime(0.f)
{
	set_Name(L"FrostNova");
}

CFrostNova::CFrostNova(const CFrostNova & rhs)
	: CAttackSkillBase(rhs)
	, m_bAttack(false)
	, m_fColRadius(rhs.m_fColRadius)
	, m_fCurTime(0.f)
	, m_fDuration(rhs.m_fDuration)
{
}

CFrostNova::~CFrostNova(void)
{
}

HRESULT CFrostNova::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	DLL::pResourcesMgr->Clone<CDynamicMesh>(RESOURCE_DYNAMIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);

	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"MeshShader", this, ID_STATIC);

	return S_OK;
}

HRESULT CFrostNova::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);

	m_pMesh = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);

	m_pCollider = CSphereCollider::Create(m_pGraphicDev, m_fColRadius, 10, 10, m_pTransform->Get_World());
	m_pCollider->Attach(L"Collider", this, ID_STATIC);

	m_pShaderCom = Get_Component<CShader>(L"MeshShader", ID_STATIC);

	return S_OK;
}

void CFrostNova::Render_GameObject(void)
{
	CAttackSkillBase::Render_GameObject();
}

void CFrostNova::Attack(CGameObject* pTarget)
{
	pTarget->Get_Component<CStatCom>(L"Stat", ID_STATIC)->Hit(m_iDamage);
}

void CFrostNova::set_Damage(const Engine::_int & iDamage)
{
	m_iDamage += iDamage;
}

void CFrostNova::check_DeadCondition(void)
{
	if (m_fCurTime >= m_fDuration && m_pMesh->Is_AnimationSetEnd())
	{
		m_bDead = true;
	}
}

void CFrostNova::dead_Effect(void)
{
}

void CFrostNova::act_Determine(const Engine::_float & fTimeDelta)
{
	_vec3 vScale = *m_pTransform->Get_Scale();
	const _float fScaleMag = 0.05f;
	vScale += _vec3(fScaleMag, fScaleMag, fScaleMag);
	m_pTransform->Set_Scale(&vScale);

	m_fCurTime += fTimeDelta;
	if (!m_bAttack)
	{
		auto pList = DLL::pObjMgr->Get_ObjList(L"Monster");
		for (auto iter : *pList)
		{
			if (CollideFunc::SphereToSphere(m_pCollider, iter->Get_Component<CSphereCollider>(L"MainSphereCol", ID_STATIC)))
			{
				Attack(iter);
			}
		}
		m_bAttack = true;
	}

	check_DeadCondition();
}

void CFrostNova::set_Radius(const Engine::_float & fRadius)
{
	m_fColRadius = fRadius;
}

CFrostNova * CFrostNova::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_float & fRadius)
{
	CFrostNova* pInstance = new CFrostNova(pGraphicDev);

	pInstance->set_Radius(fRadius);
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	
	pInstance->Late_Initialize();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CFrostNova::Clone(void)
{
	CFrostNova* pInstance = new CFrostNova(*this);


	CPlayer* pPlayer = dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front());

	_vec3 vPos = pPlayer->Get_SkillHandPosition(false);
	vPos.y += 1.0f;
	pInstance->Set_Pos(&vPos);
	pInstance->m_pTransform->Update_Component(0.f);
	//pInstance->Set_Rotation(ROT_X, D3DXToRadian(-90.f));

	pInstance->Late_Initialize();
	pInstance->set_Damage(pPlayer->Get_Damage());

	return pInstance;
}
