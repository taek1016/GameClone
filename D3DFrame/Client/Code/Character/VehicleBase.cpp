#include "stdafx.h"
#include "VehicleBase.h"

#include "Character/Player.h"

USING(Engine)

CVehicleBase::CVehicleBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCharacterBase(pGraphicDev)
	, m_bRun(true)
	, m_bRiding(false)
	, m_bDead(false)
	, m_pRidingTarget(nullptr)
	, m_pRidingTargetTransform(nullptr)
	, m_fRunSpeed(0.f)
	, m_fWalkSpeed(0.f)
	, m_fTargetHeight(0.f)
	, m_StrSeatBoneName("")
{
}

CVehicleBase::CVehicleBase(const CVehicleBase & rhs)
	: CCharacterBase(rhs)
	, m_bRun(true)
	, m_bRiding(false)
	, m_bDead(false)
	, m_pRidingTarget(nullptr)
	, m_pRidingTargetTransform(nullptr)
	, m_fRunSpeed(rhs.m_fRunSpeed)
	, m_fWalkSpeed(rhs.m_fWalkSpeed)
	, m_fTargetHeight(rhs.m_fTargetHeight)
	, m_StrSeatBoneName(rhs.m_StrSeatBoneName)
{
}

HRESULT CVehicleBase::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	DLL::pResourcesMgr->Clone<CDynamicMesh>(RESOURCE_DYNAMIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"Shader", this, ID_STATIC);

	initialize_Animation();

	return S_OK;
}

HRESULT CVehicleBase::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pMesh = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);
	m_pShaderCom = Get_Component<CShader>(L"Shader", ID_STATIC);

	return S_OK;
}

Engine::_int CVehicleBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	set_PreAnimationKey();
	if (nullptr != m_pRidingTarget)
	{
		key_Input(fTimeDelta);
		pickUp_Target();
	}

	if (m_bDead)
	{
		DisEmbark();
		return DEAD_OBJ;
	}

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	play_Animation();
	m_pMesh->Play_Animation(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CVehicleBase::Ride_Vehicle(CPlayer * pCharacter)
{
	m_bRiding = true;
	m_pRidingTarget = pCharacter;
	Set_Pos(m_pRidingTarget->Get_Pos());
	m_pRidingTargetTransform = m_pRidingTarget->Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
}

void CVehicleBase::DisEmbark(void)
{
	m_bDead = true;
	m_bRiding = false;
	m_pRidingTarget = nullptr;
}

void CVehicleBase::set_SeatBoneName(const char* pName)
{
	m_StrSeatBoneName = pName;
}

void CVehicleBase::get_CameraRight(Engine::_vec3 * pRight)
{
	_matrix matViewToWorld;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matViewToWorld);
	D3DXMatrixInverse(&matViewToWorld, nullptr, &matViewToWorld);
	memcpy(pRight, matViewToWorld.m[0], sizeof(_vec3));
	D3DXVec3Normalize(pRight, pRight);
}

void CVehicleBase::pickUp_Target(void)
{
	if (m_pRidingTarget)
	{
		_matrix matResult;

		matResult = m_pMesh->Get_FrameByName(m_StrSeatBoneName.c_str())->
			CombinedTransformationMatrix * *m_pTransform->Get_World();

		_vec3 vPos;
		memcpy(&vPos, matResult.m[3], sizeof(_vec3));

		vPos.y += m_fTargetHeight;

		static _float fDelta = 0.f;
		fDelta += 1.f;

		m_pRidingTarget->Set_Pos(&vPos);
	}
}

void CVehicleBase::read_Data(void)
{
	m_fRunSpeed = get_ReadData(L"Run");
	m_fWalkSpeed = get_ReadData(L"Walk");
	
	_vec3 vScale;
	vScale.x = get_ReadData(L"ScaleX");
	vScale.y = get_ReadData(L"ScaleY");
	vScale.z = get_ReadData(L"ScaleZ");

	m_pTransform->Set_Scale(&vScale);

	m_fTargetHeight = get_ReadData(L"SeatHeight");
}

Engine::_float CVehicleBase::get_ReadData(const Engine::_tchar * pKey)
{
	const _int iMaxStr = 256;
	_tchar szValue[iMaxStr]{};
	GetPrivateProfileString(m_wStrName.c_str(), pKey, L"0.f", szValue, iMaxStr, L"../../Data/PrefabData/VehiclePrefab.ini");

	return static_cast<_float>(_wtof(szValue));
}
