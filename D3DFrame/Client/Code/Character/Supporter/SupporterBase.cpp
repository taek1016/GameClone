#include "stdafx.h"
#include "SupporterBase.h"

#include "Item/WeaponBase.h"

USING(Engine)

CSupporterBase::CSupporterBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCharacterBase(pGraphicDev)
	, m_pWeapon(nullptr)
	, m_pTarget(nullptr)
	, m_bAfterAct(false)
	, m_fAfterAct(0.f)
	, m_fBeginActTime(0.f)
	, m_bMeleeAtt(false)
	, m_fCurPatternTime(0.f)
	, m_iCurPattern(0)
	, m_fCurLifeTime(0.f)
	, m_fMaxLifeTime(0.f)
	, m_fRunSpeed(0.f)
	, m_fCurDetermineTime(1.f)
{
}

CSupporterBase::CSupporterBase(const CSupporterBase & rhs)
	: CCharacterBase(rhs)
	, m_pWeapon(nullptr)
	, m_pTarget(nullptr)
	, m_bAfterAct(false)
	, m_fAfterAct(0.f)
	, m_fBeginActTime(0.f)
	, m_bMeleeAtt(false)
	, m_fCurPatternTime(0.f)
	, m_iCurPattern(0)
	, m_fCurLifeTime(0.f)
	, m_fCurDetermineTime(1.f)
	, m_fMaxLifeTime(rhs.m_fMaxLifeTime)
	, m_fRunSpeed(rhs.m_fRunSpeed)
{
	if (rhs.m_pWeapon)
	{
		m_pWeapon = dynamic_cast<CWeaponBase*>(rhs.m_pWeapon->Clone());
	}
}

HRESULT CSupporterBase::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	DLL::pResourcesMgr->Clone<CDynamicMesh>(RESOURCE_DYNAMIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"Shader", this, ID_STATIC);
	CStatCom::Create()->Attach(L"Stat", this, ID_STATIC);

	initialize_Animation();

	return S_OK;
}

HRESULT CSupporterBase::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);

	m_pMesh = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);

	m_pStatCom = Get_Component<CStatCom>(L"Stat", ID_STATIC);

	m_pShaderCom = Get_Component<CShader>(L"Shader", ID_STATIC);

	CCharacterBase::Late_Initialize();

	return S_OK;
}

Engine::_int CSupporterBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	m_fCurLifeTime += fTimeDelta;

	set_PreAnimationKey();
	if (m_pStatCom->Get_Dead() || m_fCurLifeTime >= m_fMaxLifeTime)
	{
		Set_AnimationSet(L"Death");
		play_Animation();

		if (m_pMesh->Is_AnimationSetEnd())
		{
			return DEAD_OBJ;
		}
		return 0;
	}

	for (auto iter : m_mapAction)
	{
		iter.second->Update_Component(fTimeDelta);
	}

	reset_ActCol();

	if (m_pMesh->Is_AnimationSetEnd())
	{
		if (m_bMeleeAtt && m_pWeapon)
		{
			m_pWeapon->Cancel_Attack();
			m_bMeleeAtt = false;
		}
	}

	act_Determine(fTimeDelta);

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	play_Animation();
	m_pMesh->Play_Animation(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);

	if (nullptr != m_pWeapon)
	{
		m_pWeapon->Update_GameObject(fTimeDelta);
	}

	return iExit;
}

void CSupporterBase::Render_GameObject(void)
{
	CCharacterBase::Render_GameObject();

	if (nullptr != m_pWeapon)
	{
		m_pWeapon->Render_GameObject();
	}
}

void CSupporterBase::read_Data(void)
{
	m_fMaxLifeTime = get_ReadData(L"LifeTime");
	m_fRunSpeed = get_ReadData(L"Run");

	_vec3 vScale;
	vScale.x = get_ReadData(L"ScaleX");
	vScale.y = get_ReadData(L"ScaleY");
	vScale.z = get_ReadData(L"ScaleZ");

	m_pTransform->Set_Scale(&vScale);
}

Engine::_float CSupporterBase::get_ReadData(const Engine::_tchar * pKey)
{
	const _int iMaxStr = 256;
	_tchar szValue[iMaxStr]{};
	GetPrivateProfileString(m_wStrName.c_str(), pKey, L"0.f", szValue, iMaxStr, L"../../Data/PrefabData/SupporterPrefab.ini");

	return static_cast<_float>(_wtof(szValue));
}

Engine::_bool CSupporterBase::can_Act(const Engine::_tchar* pKey, Engine::CGameObject* pObj)
{
	_bool bCanAct = m_mapAction[pKey]->Can_Act() && CollideFunc::ActionColToPlayer(m_mapAction[pKey], pObj);

	if (bCanAct)
	{
		m_mapAction[pKey]->Reset_Act();
		m_mapActColType[pKey] = COL_TRUE;
	}

	return bCanAct;
}

void CSupporterBase::can_NextAct(const Engine::_float & fTimeDelta)
{
	m_fAfterAct += fTimeDelta;
	if (m_fAfterAct >= m_fBeginActTime)
	{
		m_fAfterAct = 0.f;
		m_bAfterAct = false;
	}
}

void CSupporterBase::set_ActTime(const Engine::_float & fAfterTime)
{
	m_bAfterAct = true;
	m_fBeginActTime = fAfterTime;
	m_fAfterAct = 0.f;
}

void CSupporterBase::move_ToTarget(CGameObject* pTarget, const Engine::_float & fTimeDelta)
{
	CTransform* pTargetTransform = pTarget->Get_Component<CTransform>(L"Transform", ID_DYNAMIC);

	_vec3 vDir = *pTargetTransform->Get_Info(INFO_POS) - *m_pTransform->Get_Info(INFO_POS);
	_float fDistance = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);

	vDir = vDir * m_fRunSpeed *  fTimeDelta;
	if (fDistance <= 5.f)
	{
		vDir = { 0.f, 0.f, 0.f };
		Set_AnimationSet(L"Stand");
	}
	else
	{
		Set_AnimationSet(L"Run");
	}
	m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), &vDir));
}

void CSupporterBase::look_Target(Engine::CGameObject * pObj)
{
	m_pTransform->Compute_LookAtTarget(pObj->Get_Pos());
}

inline void CSupporterBase::Free(void)
{
	CCharacterBase::Free();

	Safe_Release(m_pWeapon);
}
