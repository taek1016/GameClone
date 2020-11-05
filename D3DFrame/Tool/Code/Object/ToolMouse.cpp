#include "stdafx.h"
#include "ToolMouse.h"

CToolMouse::CToolMouse(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMouse(pGraphicDev)
	, m_pGameObj(nullptr)
{
}

CToolMouse::~CToolMouse(void)
{
}

HRESULT CToolMouse::Late_Initialize()
{

	return S_OK;
}

HRESULT CToolMouse::Initialize_GameObject()
{
	return E_NOTIMPL;
}

Engine::_int CToolMouse::Update_GameObject(const Engine::_float & fTimeDelta)
{
	key_Input();

	if (m_pGameObj)
	{
		Engine::_vec3 vMousePos;
		DLL::pCalculate->ViewPortToProj(&vMousePos);
		DLL::pCalculate->ProjToView(&vMousePos, DLL::pCameraMgr->Get_Projection(), &vMousePos);
		m_pGameObj->Set_Pos(&vMousePos);
	}

	return 0;
}

void CToolMouse::Set_Target(CGameObject * pObj)
{
	m_pGameObj = pObj;
}

void CToolMouse::Set_TargetNull(void)
{
	m_pGameObj = nullptr;
}

void CToolMouse::key_Input(void)
{
}

CToolMouse* CToolMouse::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return new CToolMouse(pGraphicDev);
}
