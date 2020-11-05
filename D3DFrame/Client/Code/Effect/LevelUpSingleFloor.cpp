#include "stdafx.h"
#include "LevelUpSingleFloor.h"

#include "Particle/LeftSide.h"
#include "Particle/RightSide.h"

USING(Engine)

CLevelUpSingleFloor::CLevelUpSingleFloor(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEffectBase(pGraphicDev)
	, m_fAngle(0.f)
	, m_fCurTime(0.f)
	, m_fDeleteTime(2.f)
	, m_vUp(0.f, 0.f, 0.f)
	, m_pLeft(nullptr)
	, m_pRight(nullptr)
{
	set_Name(L"LevelUpSingleFloor");
}

CLevelUpSingleFloor::CLevelUpSingleFloor(const CLevelUpSingleFloor & rhs)
	: CEffectBase(rhs)
	, m_fAngle(0.f)
	, m_fCurTime(0.f)
	, m_vUp(rhs.m_vUp)
	, m_fDeleteTime(rhs.m_fDeleteTime)
	, m_pLeft(nullptr)
	, m_pRight(nullptr)
{
}

HRESULT CLevelUpSingleFloor::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	return S_OK;
}

HRESULT CLevelUpSingleFloor::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);

	return S_OK;
}

Engine::_int CLevelUpSingleFloor::Update_GameObject(const Engine::_float & fTimeDelta)
{
	m_fCurTime += fTimeDelta;

	if (m_fCurTime >= m_fDeleteTime)
	{
		DLL::pEffectMgr->Back_Pool(m_wStrName.c_str(), this);
		return BACK_POOL;
	}

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	
	Move_Particle(DLL::pObjMgr->Get_ObjList(L"Player")->front(), fTimeDelta);

	if (m_pLeft)
	{
		m_pLeft->Update_GameObject(fTimeDelta);
	}

	if (m_pRight)
	{
		m_pRight->Update_GameObject(fTimeDelta);
	}

	return iExit;
}

void CLevelUpSingleFloor::Render_GameObject(void)
{
}

void CLevelUpSingleFloor::Clone_YellowParticle(void)
{
	m_pLeft = CLeftSide::Create(m_pGraphicDev);
	m_pRight = CRightSide::Create(m_pGraphicDev);
}

void CLevelUpSingleFloor::Move_Particle(Engine::CGameObject* pTarget, const Engine::_float & fTimeDelta)
{
	m_vUp += _vec3(0.f, 2.f, 0.f) * fTimeDelta;
	_vec3 vPos = m_vUp + *pTarget->Get_Pos();

	m_pTransform->Set_Info(INFO_POS, &vPos);

	m_fAngle += D3DXToRadian(360.f) * fTimeDelta;

	m_pLeft->Set_Data(m_fAngle, m_pTransform->Get_Info(INFO_POS));
	m_pRight->Set_Data(m_fAngle, m_pTransform->Get_Info(INFO_POS));
}

void CLevelUpSingleFloor::Ready_ToGo(void)
{
	m_fAngle = 0.f;
	m_fCurTime = 0.f;

	m_pLeft->Ready_ToGo();
	m_pRight->Ready_ToGo();
}

HRESULT CLevelUpSingleFloor::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	return S_OK;
}

CLevelUpSingleFloor * CLevelUpSingleFloor::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLevelUpSingleFloor* pInstance = new CLevelUpSingleFloor(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();

	return pInstance;
}

Engine::CGameObject * CLevelUpSingleFloor::Clone(void)
{
	CLevelUpSingleFloor* pInstance = new CLevelUpSingleFloor(*this);

	pInstance->Late_Initialize();
	pInstance->Clone_YellowParticle();

	return pInstance;
}

inline void CLevelUpSingleFloor::Free(void)
{
	CEffectBase::Free();

	Safe_Release(m_pLeft);
	Safe_Release(m_pRight);
}
