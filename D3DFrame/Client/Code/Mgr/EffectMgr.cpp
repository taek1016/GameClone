#include "stdafx.h"
#include "EffectMgr.h"

#include "Effect/EffectBase.h"

#include "Effect/InfernalDeath.h"

#include "Effect/Particle/RedBloodParticle.h"
#include "Effect/Particle/GreenBloodParticle.h"

#include "Effect/LevelUpEffect.h"
#include "Effect/LevelUpSingleFloor.h"
#include "Effect/Particle/RightSide.h"
#include "Effect/Particle/LeftSide.h"

#include "Effect/StunEffect.h"

USING(Engine)
IMPLEMENT_SINGLETON(CEffectMgr)

CEffectMgr::~CEffectMgr(void)
{
	Free();
}

void CEffectMgr::Initialize_Effect(LPDIRECT3DDEVICE9 pGraphicDev)
{
	add_Effect<CRedBloodParticle>(pGraphicDev);
	add_Effect<CGreenBloodParticle>(pGraphicDev);

	add_Effect<CLevelUpEffect>(pGraphicDev);
	add_Effect<CLevelUpSingleFloor>(pGraphicDev);

	add_Effect<CStunEffect>(pGraphicDev);
}

CEffectBase * CEffectMgr::Get_Effect(const Engine::_tchar * pKey, const Engine::_vec3 * pPos)
{
	if (nullptr == find_Effect(pKey))
	{
		return nullptr;
	}

	CEffectBase* pInstance = find_EffectContainer(pKey);

	pInstance->Set_Pos(pPos);
	pInstance->Ready_ToGo();

	DLL::pObjMgr->Add_GameObject(L"Effect", pInstance);

	return pInstance;
}

void CEffectMgr::Back_Pool(const Engine::_tchar * pKey, CEffectBase * pEffect)
{
	auto iter = find_if(m_EffectContainer.begin(), m_EffectContainer.end(), CTag_Finder(pKey));

	if (m_EffectContainer.end() == iter)
	{
		return;
	}

	iter->second->push_back(pEffect);
}

CEffectBase* CEffectMgr::find_Effect(const Engine::_tchar * pKey)
{
	auto iter = find_if(m_OriEffectMap.begin(), m_OriEffectMap.end(), Engine::CTag_Finder(pKey));

	if (m_OriEffectMap.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

CEffectBase * CEffectMgr::find_EffectContainer(const Engine::_tchar * pKey)
{
	auto iter = find_if(m_EffectContainer.begin(), m_EffectContainer.end(), CTag_Finder(pKey));

	if (m_EffectContainer.end() == iter)
	{
		return nullptr;
	}

	if (iter->second->empty())
	{
		CEffectBase* pEffect = find_Effect(pKey);

		for (_int i = 0; i < m_iMakeCount; ++i)
		{
			iter->second->push_back(dynamic_cast<CEffectBase*>(pEffect->Clone()));
		}
	}

	CEffectBase* pEffect = iter->second->front();
	iter->second->pop_front();

	return pEffect;
}

inline void CEffectMgr::Free(void)
{
	for (auto iter : m_OriEffectMap)
	{
		Safe_Release(iter.second);
	}
	m_OriEffectMap.clear();
}
