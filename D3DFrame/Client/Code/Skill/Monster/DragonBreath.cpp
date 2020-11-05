#include "stdafx.h"
#include "DragonBreath.h"

#include "Character/Character.h"

USING(Engine)

CDragonBreath::CDragonBreath(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTextureSkillBase(pGraphicDev)
	, m_bDamageGive(false)
	, m_fLength(2.f)
{
	set_Name(L"DragonBreath");
	set_Index(5.f);
	Set_Damage(3);
}

CDragonBreath::CDragonBreath(const CDragonBreath & rhs)
	: CTextureSkillBase(rhs)
	, m_bDamageGive(false)
	, m_fLength(rhs.m_fLength)
{
}

Engine::_bool CDragonBreath::collide_Object(const Engine::_vec3 * pPos)
{
	const _float fDistance = D3DXVec3Length(&(*pPos - *m_pTransform->Get_Info(INFO_POS)));

	const _float fRadius = m_vScale.x * 0.5f;

	if (fRadius <= fDistance)
	{
		return true;
	}

	return false;
}

void CDragonBreath::check_TextureIndex(const Engine::_float & fTimeDelta)
{
	m_fCurIndex += fTimeDelta;
	if (m_fCurIndex >= m_fMaxSize)
	{
		m_bDead = true;
		return;
	}

	auto pPos = m_pTransform->Get_Info(INFO_POS);
	_vec3 vPos = *pPos + m_vDir * m_fLength;
	_vec3 vMovePos = DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIndex, pPos, &(m_vDir * m_fLength));

	if (vPos.y <= vMovePos.y)
	{
		vPos = vMovePos;
	}

	m_pTransform->Set_Info(INFO_POS, &vPos);

	m_pTransform->Set_Scale(&m_vScale);
	
	const _float fMagValue = 0.1f;
	m_vScale += _vec3(fMagValue, fMagValue * 0.5f, fMagValue);
}

void CDragonBreath::dead_Action(const Engine::_float & fTimeDelta)
{
}

void CDragonBreath::act_Determine(const Engine::_float & fTimeDelta)
{
	if (false == m_bDamageGive)
	{
		m_bDamageGive = true;

		list<CGameObject*>* pList = DLL::pObjMgr->Get_ObjList(L"Player");
		for (auto iter : *pList)
		{
			if (collide_Object(iter->Get_Pos()))
			{
				dynamic_cast<CCharacterBase*>(iter)->Hit(m_iDamage);
			}
		}
	}
}

CDragonBreath * CDragonBreath::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDragonBreath* pInstance = new CDragonBreath(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}

	pInstance->m_vScale = _vec3(5.f, 5.f, 5.f);
	return pInstance;
}

Engine::CGameObject * CDragonBreath::Clone(void)
{
	CDragonBreath* pInstance = new CDragonBreath(*this);

	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}
