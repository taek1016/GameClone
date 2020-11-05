#include "stdafx.h"
#include "Boar.h"

#include "Item/Monster/BoarNose.h"

USING(Engine)

CBoar::CBoar(LPDIRECT3DDEVICE9 pGraphicDev)
	: CAttackSecondMonster(pGraphicDev)
{
	set_Name(L"Boar");
}

CBoar::CBoar(const CBoar & rhs)
	: CAttackSecondMonster(rhs)
{
}

CBoar::~CBoar(void)
{
}

void CBoar::print_Name(void)
{
	_vec4 vPos(*m_pTransform->Get_Info(INFO_POS), 1.f);

	_vec3 vScale(30.f, 20.f, 1.f);
	make_PosToView(&vPos, vScale.x * 0.f, m_fHeight);

	DLL::pFontMgr->Print_Font(&_vec3(vPos), &vScale, 20, L"µÅÁö", D3DXCOLOR(0.f, 0.f, 1.f, 1.f));
}

void CBoar::make_Weapon(Engine::CGameObject * pTarget)
{
	m_pWeapon = CBoarNose::Create(m_pGraphicDev, dynamic_cast<CCharacterBase*>(DLL::pObjMgr->Get_ObjList(L"Player")->front()));
	m_pWeaponMatrix = &m_pMesh->Get_FrameByName("boar_Bone15_Jaw")->CombinedTransformationMatrix;
	m_pWeapon->Set_ColliderMat(m_pTransform->Get_World(), m_pWeaponMatrix);

	Add_Action(L"MeleeCol", 0.f, 3.f);
	Add_Action(L"FollowCol", 0.f, 12.f);
}

void CBoar::initialize_Bones(void)
{
}

void CBoar::act_AfterHit(const Engine::_float & fTimeDelta)
{
	if (m_bHit)
	{
		Set_AnimationSet(L"Hit");
		if (m_pMesh->Is_AnimationSetEnd())
		{
			Set_AnimationSet(L"Stand");
			m_bHit = false;
		}
		return;
	}

	CGameObject* pPlayer = DLL::pObjMgr->Get_ObjList(L"Player")->front();

	if (can_Act(L"MeleeCol", pPlayer))
	{
		look_Target(pPlayer);
		Set_AnimationSet(L"Attack");
		set_ActTime(3.f);

		if (m_pWeapon && m_pMesh->Is_AnimationSetEnd())
		{
			m_pWeapon->AttackAct();
		}
	}
	else if (can_Act(L"FollowCol", pPlayer))
	{
		look_Target(pPlayer);
		if (!CollideFunc::MainSphereCol(this, pPlayer))
		{
			move_ToPlayer(fTimeDelta);
			Set_AnimationSet(L"Run");
		}
	}
}

CBoar* CBoar::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBoar* pInstance = new CBoar(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CBoar::Clone(void)
{
	CBoar* pInstance = new CBoar(*this);

	pInstance->Late_Initialize();
	pInstance->make_Weapon(DLL::pObjMgr->Get_ObjList(L"Player")->front());
	pInstance->Add_MainCollider(pInstance->m_fMainColSize);

	return pInstance;
}
