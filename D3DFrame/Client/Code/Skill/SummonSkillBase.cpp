#include "stdafx.h"
#include "SummonSkillBase.h"

USING(Engine)

CSummonSkillBase::CSummonSkillBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSkillBase(pGraphicDev)
{
}

CSummonSkillBase::CSummonSkillBase(const CSummonSkillBase & rhs)
	: CSkillBase(rhs)
{
}

HRESULT CSummonSkillBase::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	DLL::pResourcesMgr->Clone<CDynamicMesh>(RESOURCE_DYNAMIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"Shader_Mesh", this, ID_STATIC);

	return S_OK;
}

HRESULT CSummonSkillBase::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pMesh = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);
	m_pShaderCom = Get_Component<CShader>(L"Shader_Mesh", ID_STATIC);

	return S_OK;
}

void CSummonSkillBase::Render_GameObject(void)
{
	LPD3DXEFFECT	pEffect = m_pShaderCom->Get_EffectHandle();
	NULL_CHECK(pEffect);
	pEffect->AddRef();

	_uint	iPassMax = 0;

	FAILED_CHECK_RETURN(SetUp_ConstantTable(pEffect), );

	pEffect->Begin(&iPassMax, 0);

	pEffect->BeginPass(0);

	m_pMesh->Render_Meshes(pEffect);

	pEffect->EndPass();

	pEffect->End();

	Safe_Release(pEffect);

	//if (g_bCollider)
	//{
	//	m_pCollider->Render_Collider(m_eCollType, m_pTransform->Get_World());
	//}
}

inline void CSummonSkillBase::Free(void)
{
	CSkillBase::Free();

	m_listComponent->clear();
}
