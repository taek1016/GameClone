#include "stdafx.h"
#include "SummonVehicleBase.h"

#include "Character/Player.h"
#include "Character/VehicleBase.h"

USING(Engine)
CSummonVehicleBase::CSummonVehicleBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSummonSkillBase(pGraphicDev)
{
}

CSummonVehicleBase::CSummonVehicleBase(const CSummonVehicleBase & rhs)
	: CSummonSkillBase(rhs)
{
}

HRESULT CSummonVehicleBase::Initialize_GameObject(void)
{
	return S_OK;
}

HRESULT CSummonVehicleBase::Late_Initialize(void)
{
	return S_OK;
}

Engine::_int CSummonVehicleBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front());

	auto pPlayerPos = pPlayer->Get_Pos();
	auto pVehicle = dynamic_cast<CVehicleBase*>(DLL::pDataMgr->Clone_DynamicObj(m_wStrName.c_str(), pPlayerPos));
	pPlayer->DisEmbark();
	pPlayer->Ride_Target(pVehicle);
	pVehicle->Get_Component<CTransform>(L"Transform", ID_DYNAMIC)->Set_Angle(pPlayer->Get_Component<CTransform>(L"Transform", ID_DYNAMIC)->Get_Angle());

	DLL::pObjMgr->Add_GameObject(L"Vehicle", pVehicle);

	summon_Effect(pPlayerPos);

	return DEAD_OBJ;
}

void CSummonVehicleBase::Render_GameObject(void)
{
}
