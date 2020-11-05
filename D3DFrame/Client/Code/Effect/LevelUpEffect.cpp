#include "stdafx.h"
#include "LevelUpEffect.h"

USING(Engine)

CLevelUpEffect::CLevelUpEffect(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEffectBase(pGraphicDev)
	, m_fCurTime(0.f)
	, m_fLifeTime(0.f)
	, m_fParticleMakeTime(0.4f)
	, m_fDeadTime(4.f)
{
	set_Name(L"LevelUp");
}

CLevelUpEffect::CLevelUpEffect(const CLevelUpEffect & rhs)
	: CEffectBase(rhs)
	, m_fCurTime(0.f)
	, m_fParticleMakeTime(rhs.m_fParticleMakeTime)
	, m_fLifeTime(0.f)
	, m_fDeadTime(rhs.m_fDeadTime)
{
}

HRESULT CLevelUpEffect::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	return S_OK;
}

HRESULT CLevelUpEffect::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);

	return S_OK;
}

Engine::_int CLevelUpEffect::Update_GameObject(const Engine::_float & fTimeDelta)
{
	m_fLifeTime += fTimeDelta;
	if (m_fLifeTime >= m_fDeadTime)
	{
		DLL::pEffectMgr->Back_Pool(m_wStrName.c_str(), this);
		return BACK_POOL;
	}

	auto pPlayerPos = DLL::pObjMgr->Get_ObjList(L"Player")->front()->Get_Pos();
	m_pTransform->Set_Info(INFO_POS, pPlayerPos);

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	m_fCurTime += fTimeDelta;
	if (m_fCurTime >= m_fParticleMakeTime)
	{
		m_fCurTime = 0.f;
		DLL::pEffectMgr->Get_Effect(L"LevelUpSingleFloor", m_pTransform->Get_Info(INFO_POS));
	}

	return iExit;
}

void CLevelUpEffect::Render_GameObject(void)
{
}

void CLevelUpEffect::Ready_ToGo(void)
{

}

HRESULT CLevelUpEffect::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	return S_OK;
}

CLevelUpEffect * CLevelUpEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLevelUpEffect* pInstance = new CLevelUpEffect(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();

	return pInstance;
}

Engine::CGameObject * CLevelUpEffect::Clone(void)
{
	CLevelUpEffect* pInstance = new CLevelUpEffect(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
