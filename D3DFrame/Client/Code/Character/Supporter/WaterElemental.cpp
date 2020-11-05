#include "stdafx.h"
#include "WaterElemental.h"

#include "..\..\Item\Supporter\WaterElementalFist.h"

USING(Engine)

CWaterElemental::CWaterElemental(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSupporterBase(pGraphicDev)
{
	set_Name(L"WaterElemental");
	m_iCurPattern = WATER_ELE_ATTACK;
}

CWaterElemental::CWaterElemental(const CWaterElemental & rhs)
	: CSupporterBase(rhs)
{
}


void CWaterElemental::initialize_ActionCol(void)
{
	const _float fMoveRadius = 36.f;

	Add_Action(L"MeleeCol", 0.f, 4.5f);
	Add_Action(L"MonsterFollowCol", 0.f, 0.5f * fMoveRadius);
	Add_Action(L"FollowCol", 0.f, fMoveRadius);

}

void CWaterElemental::act_Determine(const Engine::_float & fTimeDelta)
{
	Set_AnimationSet(L"Stand");

	if (m_bAfterAct)
	{
		can_NextAct(fTimeDelta);
		return;
	}

	CGameObject* pPlayer = DLL::pObjMgr->Get_ObjList(L"Player")->front();
	determine_AI(pPlayer, fTimeDelta);

	switch (m_iCurPattern)
	{
	case CWaterElemental::WATER_ELE_PLAYER_FOLLOW:
		look_Target(pPlayer);
		move_ToTarget(pPlayer, fTimeDelta);
		break;

	case CWaterElemental::WATER_ELE_MONSTER_FOLLOW:
		look_Target(m_pTarget);
		move_ToTarget(m_pTarget, fTimeDelta);
		break;

	case CWaterElemental::WATER_ELE_ATTACK:
		attack_Act(fTimeDelta);
		break;
	}
}

void CWaterElemental::make_Weapon(void)
{
	m_pWeapon = CWaterElementalFist::Create(m_pGraphicDev);
	m_pWeapon->Set_ColliderMat(m_pTransform->Get_World(), &m_pMesh->Get_FrameByName("waterelemental_Bone103")->CombinedTransformationMatrix);
}

Engine::_bool CWaterElemental::determine_AI(CGameObject* pPlayer, const Engine::_float& fTimeDelta)
{
	m_fCurDetermineTime += fTimeDelta;

	if (nullptr != m_pTarget && dynamic_cast<CCharacterBase*>(m_pTarget)->Is_Dead())
	{
		m_pTarget = nullptr;
		Set_AnimationSet(L"Stand");
		m_iCurPattern = WATER_ELE_PLAYER_FOLLOW;
		return false;
	}

	if (m_fCurDetermineTime >= 0.5f)
	{
		m_fCurDetermineTime = 0.f;
		m_pTarget = nullptr;

		if (can_Act(L"FollowCol", pPlayer))
		{
			auto pMonsterList = DLL::pObjMgr->Get_ObjList(L"Monster");

			_float fDistance = FLT_MAX;
			for (auto iter : *pMonsterList)
			{
				_float fMeToMonster = D3DXVec3Length(&(*m_pTransform->Get_Info(INFO_POS) - *iter->Get_Pos()));
				if (fDistance > fMeToMonster)
				{
					fDistance = fMeToMonster;
					m_pTarget = iter;
				}
			}

			if (nullptr == m_pTarget || pMonsterList->empty())
			{
				m_iCurPattern = WATER_ELE_PLAYER_FOLLOW;
				return true;
			}

			if (can_Act(L"MeleeCol", m_pTarget))
			{
				m_iCurPattern = WATER_ELE_ATTACK;
			}
			else if (can_Act(L"MonsterFollowCol", m_pTarget))
			{
				m_iCurPattern = WATER_ELE_MONSTER_FOLLOW;
			}
			else
			{
				m_iCurPattern = WATER_ELE_PLAYER_FOLLOW;
			}
		}
		else
		{
			m_iCurPattern = WATER_ELE_PLAYER_FOLLOW;
		}

		return true;
	}

	return false;
}

void CWaterElemental::attack_Act(const Engine::_float & fTimeDelta)
{
	m_pWeapon->Set_Target(dynamic_cast<CCharacterBase*>(m_pTarget));

	if (m_pWeapon && false == m_bMeleeAtt)
	{
		m_pWeapon->AttackAct();
		m_bMeleeAtt = true;
	}

	look_Target(m_pTarget);
	Set_AnimationSet(L"Attack");

	m_fCurPatternTime += fTimeDelta;
	const _float fPatternTime = (745.f - 724.f) / 30.f * 0.95f;
	if (m_fCurPatternTime >= fPatternTime)
	{
		m_fCurPatternTime = 0.f;
		set_ActTime(2.f);
	}
}

CWaterElemental * CWaterElemental::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWaterElemental* pInstance = new CWaterElemental(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->initialize_ActionCol();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CWaterElemental::Clone(void)
{
	CWaterElemental* pInstance = new CWaterElemental(*this);

	pInstance->Late_Initialize();
	pInstance->initialize_ActionCol();
	pInstance->make_Weapon();

	return pInstance;
}
