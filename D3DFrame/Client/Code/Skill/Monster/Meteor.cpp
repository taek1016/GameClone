#include "stdafx.h"
#include "Meteor.h"

#include "Character\Character.h"

USING(Engine)

CMeteor::CMeteor(LPDIRECT3DDEVICE9 pGraphicDev)
	: CAttackSkillBase(pGraphicDev)
{
	set_Name(L"Meteor");
	Set_Damage(10);
}

CMeteor::CMeteor(const CMeteor & rhs)
	: CAttackSkillBase(rhs)
{
}

HRESULT CMeteor::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	DLL::pResourcesMgr->Clone<CDynamicMesh>(RESOURCE_DYNAMIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"Shader", this, ID_STATIC);
	
	return S_OK;
}

HRESULT CMeteor::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pMesh = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);
	m_pShaderCom = Get_Component<CShader>(L"Shader", ID_STATIC);
	m_pCollider = CSphereCollider::Create(m_pGraphicDev, 8.f, 10, 10, m_pTransform->Get_World());
	m_pCollider->Attach(L"MainSphereCol", this, ID_STATIC);

	return S_OK;
}

void CMeteor::Attack(CGameObject * pTarget)
{
	dynamic_cast<CCharacterBase*>(pTarget)->Hit(m_iDamage);
}

void CMeteor::act_Determine(const Engine::_float & fTimeDelta)
{
	auto pPos = m_pTransform->Get_Info(INFO_POS);

	_vec3 vMoveDir = m_vDir * m_fSpeed * fTimeDelta;
	_vec3 vPos = *pPos + vMoveDir;
	_vec3 vMovePos = DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIndex, pPos, &vMoveDir);

	if (vPos.y <= vMovePos.y)
	{
		vPos.y = vMovePos.y;
		dead_Effect();
		m_bDead = true;
	}

	m_pTransform->Set_Info(INFO_POS, &vPos);

	list<CGameObject*>* pList = DLL::pObjMgr->Get_ObjList(L"Player");
	for (auto iter : *pList)
	{
		if (CollideFunc::SphereToSphere(m_pCollider, iter->Get_Component<CSphereCollider>(L"MainSphereCol", ID_STATIC)))
		{
			dynamic_cast<CCharacterBase*>(iter)->Hit(m_iDamage);
			dead_Effect();
			m_bDead = true;
		}
	}
}

void CMeteor::check_DeadCondition(void)
{

}

void CMeteor::dead_Effect(void)
{
}

CMeteor * CMeteor::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMeteor* pInstance = new CMeteor(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	const _float fScaleValue = 15.f;
	pInstance->Set_Scale(&_vec3(fScaleValue, fScaleValue, fScaleValue));
	pInstance->set_Speed(20.f);

	return pInstance;
}

Engine::CGameObject * CMeteor::Clone(void)
{
	CMeteor* pInstance = new CMeteor(*this);

	pInstance->Late_Initialize();
	
	return pInstance;
}
