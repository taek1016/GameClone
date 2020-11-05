#include "stdafx.h"
#include "Portion.h"

USING(Engine)

CPortion::CPortion(void)
	: CUsableBase()
{
}

CPortion::CPortion(const CPortion & rhs)
	: CUsableBase(rhs)
{
}

CPortion::~CPortion(void)
{
}

HRESULT CPortion::Late_Initialize()
{
	return S_OK;
}

HRESULT CPortion::Initialize_GameObject()
{
	return S_OK;
}

Engine::_int CPortion::Update_GameObject(const Engine::_float & fTimeDelta)
{
	return 0;
}

void CPortion::Use_Item(void)
{
	//m_pGameObject->Get_Heal(this);
}

Engine::CGameObject* CPortion::Clone(const Engine::_vec3 * pPos)
{
	return nullptr;
}

void CPortion::Set_Obj(Engine::CGameObject * pObj)
{
}

void CPortion::LoadData(HANDLE hFile)
{
}

void CPortion::freeMem(void)
{
}
