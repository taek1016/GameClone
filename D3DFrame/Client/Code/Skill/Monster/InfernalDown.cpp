#include "stdafx.h"
#include "InfernalDown.h"

USING(Engine)

CInfernalDown::CInfernalDown(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSummonSkillBase(pGraphicDev)
	, m_fCurTime(0.f)
	, m_fLength(0.f)
	, m_bLengthSet(false)
{
	set_Name(L"InfernalBall");
}

CInfernalDown::CInfernalDown(const CInfernalDown & rhs)
	: CSummonSkillBase(rhs)
	, m_fCurTime(0.f)
	, m_bLengthSet(false)
{
}

Engine::_int CInfernalDown::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (false == m_bLengthSet)
	{
		set_Length();
	}

	m_fCurTime += fTimeDelta;

	const _float fLifeTime = 2.f;
	if (m_fCurTime >= fLifeTime)
	{
		DLL::pObjMgr->Add_GameObject(L"Skill", DLL::pSkillMgr->Get_MonsterSkill(L"InfernalGroundDown", m_pTransform->Get_Info(INFO_POS)));

		return DEAD_OBJ;
	}

	m_pTransform->Move_Pos(&(m_vDir * fTimeDelta * m_fLength));

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	m_pMesh->Play_Animation(fTimeDelta);
	DLL::pRenderer->Add_RenderGroup(RENDER_NONALPHA, this);

	return iExit;
}

void CInfernalDown::set_Length(void)
{
	const _vec3* pPlayerPos = DLL::pObjMgr->Get_ObjList(L"Player")->front()->Get_Pos();

	const _vec3* pPos = m_pTransform->Get_Info(INFO_POS);

	m_fLength = D3DXVec3Length(&(*pPlayerPos - *pPos));

	m_pMesh->Set_AnimationSet(0);
}

CInfernalDown * CInfernalDown::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CInfernalDown* pInstance = new CInfernalDown(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Set_Scale(&_vec3(2.f, 2.f, 2.f));

	return pInstance;
}

Engine::CGameObject * CInfernalDown::Clone(void)
{
	CInfernalDown* pInstance = new CInfernalDown(*this);

	pInstance->Late_Initialize();

	return pInstance;
}