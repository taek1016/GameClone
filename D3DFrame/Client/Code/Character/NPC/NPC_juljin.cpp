#include "stdafx.h"
#include "NPC_juljin.h"

#include "UI/DealUI.h"

USING(Engine)

CNPC_Zuljin::CNPC_Zuljin(LPDIRECT3DDEVICE9 pGraphicDev)
	: CNPCBase(pGraphicDev)
{
	set_Name(L"zuljin");
}

CNPC_Zuljin::CNPC_Zuljin(const CNPC_Zuljin & rhs)
	: CNPCBase(rhs)
{
}

void CNPC_Zuljin::initialize_NPCUI(void)
{
	m_pUI = CDealUI::Create(m_pGraphicDev);
}

CNPC_Zuljin * CNPC_Zuljin::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNPC_Zuljin* pInstance = new CNPC_Zuljin(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CNPC_Zuljin::Clone(void)
{
	CNPC_Zuljin* pInstance = new CNPC_Zuljin(*this);

	pInstance->Late_Initialize();
	pInstance->Add_MainCollider(pInstance->m_fMainColSize);

	return pInstance;
}
