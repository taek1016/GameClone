#include "stdafx.h"
#include "StatCom.h"

USING(Engine)

CStatCom::CStatCom(void)
	: CComponent()

	, m_bHit(false)
	, m_bDead(false)
	, m_bRun(true)

	, m_tInfo()
	, m_tDefaultInfo()
	, m_tLevelUpInfo()

	, m_iLevel(1)
	, m_iExp(0)
	, m_iLevelUpExp(200)
{
	m_tLevelUpInfo.tHP = HP_INFO(30, 30);
	m_tLevelUpInfo.tMP = MP_INFO(10, 10);
	m_tLevelUpInfo.tAttArmor = ATT_ARMOR_INFO(3, 1);
}

CStatCom::CStatCom(const CStatCom & rhs)
	: CComponent(rhs)

	, m_bHit(false)
	, m_bDead(false)
	, m_bRun(true)

	, m_tInfo(rhs.m_tInfo)
	, m_tDefaultInfo(rhs.m_tDefaultInfo)
	, m_tLevelUpInfo(rhs.m_tLevelUpInfo)

	, m_iLevel(rhs.m_iLevel)
	, m_iExp(rhs.m_iExp)
	, m_iLevelUpExp(rhs.m_iLevelUpExp)
{
}

CStatCom::~CStatCom(void)
{
}

const HP_INFO& CStatCom::Get_HP(void) const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tInfo.tHP;
}

const _float CStatCom::Get_HPPercent(void) const
{
	return m_tInfo.tHP.iHP / static_cast<_float>(m_tInfo.tHP.iMaxHP);
}

const MP_INFO& CStatCom::Get_MP(void) const
{
	return m_tInfo.tMP;
}

const _float CStatCom::Get_MPPercent(void) const
{
	return m_tInfo.tMP.iMP / static_cast<_float>(m_tInfo.tMP.iMaxMP);
}

const _bool & CStatCom::Get_Dead(void) const
{
	return m_bDead;
}

const Engine::_bool & CStatCom::Get_Hit(void) const
{
	return m_bHit;
}

const Engine::_bool & CStatCom::Get_Dodge(void) const
{
	return m_bDodge;
}

const Engine::_int & CStatCom::Get_Armor(void) const
{
	return m_tInfo.tAttArmor.iArmor;
}

const Engine::_int & CStatCom::Get_Att(void) const
{
	return m_tInfo.tAttArmor.iAtt;
}

const _float CStatCom::Get_Move(void) const
{
	if (m_bRun)
	{
		return m_tInfo.tMove.fRunSpeed;
	}
	else
	{
		return m_tInfo.tMove.fWalkSpeed;
	}
}

const _bool & CStatCom::Get_Run(void) const
{
	return m_bRun;
}

const Engine::_int & CStatCom::Get_Level(void) const
{
	return m_iLevel;
}

const Engine::_bool CStatCom::Get_Exp(const Engine::_int & iExp)
{
	m_iExp += iExp;
	if (m_iExp >= m_iLevelUpExp)
	{
		while (m_iExp >= m_iLevelUpExp)
		{
			m_iLevel++;
			m_iExp -= m_iLevelUpExp;
			m_iLevelUpExp = static_cast<_int>(m_iLevelUpExp * 1.5f);
		}

		calculate_LevelStat();
		return true;
	}

	return false;
}

void CStatCom::Set_Level(const _int& rhs)
{
	m_iLevel = rhs;
}

void CStatCom::Set_Run(const Engine::_bool& bRun)
{
	m_bRun = bRun;
}

void CStatCom::Use_Mana(const Engine::_float & fMana)
{
	m_tInfo.tMP.iMP -= static_cast<_int>(fMana);
}

void CStatCom::Revive(void)
{
	m_tInfo.tHP.iHP = m_tInfo.tHP.iMaxHP;
	m_tInfo.tMP.iMP = m_tInfo.tMP.iMaxMP;

	m_bDead = false;
}

void CStatCom::Set_Item(const UNIT_INFO & tInfo)
{
	m_tItemInfo = tInfo;

	_int iHPMinus = m_tInfo.tHP.iMaxHP - m_tInfo.tHP.iHP;
	_int iMPMinus = m_tInfo.tMP.iMaxMP - m_tInfo.tMP.iMP;

	calculate_LevelStat();
	m_tInfo = m_tInfo + m_tItemInfo;

	m_tInfo.tHP.iHP -= iHPMinus;
	m_tInfo.tMP.iMP -= iMPMinus;
}

void CStatCom::Set_TotalStat(const UNIT_INFO & rhs)
{
	set_HP(rhs.tHP);
	set_MP(rhs.tMP);
	set_Move(rhs.tMove);
	set_AttArmor(rhs.tAttArmor);
	set_Percent(rhs.tPercent);

	calculate_LevelStat();
}

void CStatCom::Hit(const _int & iDamage, const _float& fDodgeDebuf)
{
	if (m_bDead)
	{
		return;
	}

	if (false == m_bHit)
	{
		m_bHit = true;
	}

	m_tInfo.tHP.iHP -= iDamage;

	if (m_tInfo.tHP.iHP <= 0)
	{
		m_tInfo.tHP.iHP = 0;
		m_bDead = true;
	}
}

_bool CStatCom::calculate_Dodge(const _float fAddPercent)
{
	// 확률계산.
	_float iRandNum = (rand() % 101) / 100.f;

	if (iRandNum < (m_tInfo.tPercent.fDefaultDodgePercent - fAddPercent))
	{
		m_bDodge = true;
	}
	else
	{
		m_bDodge = false;
	}

	return m_bDodge;
}

void CStatCom::level_Up(void)
{
	calculate_LevelStat();
}

void CStatCom::calculate_LevelStat(void)
{
	m_tInfo = m_tDefaultInfo + m_tLevelUpInfo * (m_iLevel - 1);
}

void CStatCom::set_HP(const HP_INFO & rhs)
{
	m_tDefaultInfo.tHP = rhs;
}

void CStatCom::set_MP(const MP_INFO & rhs)
{
	m_tDefaultInfo.tMP = rhs;
}

void CStatCom::set_Move(const MOVE_INFO & rhs)
{
	m_tDefaultInfo.tMove = rhs;
}

void CStatCom::set_AttArmor(const ATT_ARMOR_INFO & rhs)
{
	m_tDefaultInfo.tAttArmor = rhs;
}

void CStatCom::set_Percent(const PERCENT_INFO & rhs)
{
	m_tDefaultInfo.tPercent = rhs;
}

void CStatCom::set_Resist(const RESIST_INFO & rhs)
{
	m_tDefaultInfo.tResist = rhs;
}

CStatCom * CStatCom::Create(void)
{
	CStatCom*	pInstance = new CStatCom();

	if (FAILED(pInstance->Initialize_Component()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CStatCom * CStatCom::Create(const UNIT_INFO & rhs)
{
	CStatCom*	pInstance = new CStatCom();

	pInstance->Set_TotalStat(rhs);

	if (FAILED(pInstance->Initialize_Component()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CStatCom::Clone(void)
{
	return new CStatCom(*this);
}

inline void CStatCom::Free(void)
{
	CComponent::Free();
}
