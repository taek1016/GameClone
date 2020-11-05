#ifndef EffectMgr_h__
#define EffectMgr_h__

#include "Base.h"

class CEffectBase;

class CEffectMgr : public CBase
{
	DECLARE_SINGLETON(CEffectMgr)

private:
	explicit										CEffectMgr(void) = default;
	virtual											~CEffectMgr(void);

public:
	void											Initialize_Effect(LPDIRECT3DDEVICE9 pGraphicDev);
	CEffectBase*									Get_Effect(const Engine::_tchar* pKey, const Engine::_vec3* pPos);
	void											Back_Pool(const Engine::_tchar* pKey, CEffectBase* pEffect);

private:
	CEffectBase*									find_Effect(const Engine::_tchar* pKey);
	CEffectBase*									find_EffectContainer(const Engine::_tchar* pKey);

	template <typename T>
	HRESULT add_Effect(LPDIRECT3DDEVICE9 pGraphicDev)
	{
		T* pInstance = T::Create(pGraphicDev);

		if (nullptr != find_Effect(pInstance->Get_Name()))
		{
			Engine::Safe_Release(pInstance);
			return E_FAIL;
		}

		m_OriEffectMap.emplace(pInstance->Get_Name(), pInstance);

		m_EffectContainer.emplace(pInstance->Get_Name(), new list<CEffectBase*>);
		for (_int i = 0; i < m_iMakeCount; ++i)
		{
			m_EffectContainer[pInstance->Get_Name()]->push_back(dynamic_cast<CEffectBase*>(pInstance->Clone()));
		}

		return S_OK;
	}

	map<const Engine::_tchar*, CEffectBase*>		m_OriEffectMap;
	map<const Engine::_tchar*, list<CEffectBase*>*>	m_EffectContainer;
	const Engine::_int								m_iMakeCount = 16;

private:
	inline virtual void								Free(void) override;
};

#endif // EffectMgr_h__
