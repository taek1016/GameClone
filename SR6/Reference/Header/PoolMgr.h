#ifndef PoolMgr_h__
#define PoolMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CPoolMgr : public CBase
{
	DECLARE_SINGLETON(CPoolMgr)

private:
	explicit	CPoolMgr(void) = default;
	virtual		~CPoolMgr(void);

public:
	HRESULT		Initialize_Pool(const _int& iPoolType, const _int& iPoolSize);

	HRESULT		Add_Pool(const _int& iCurType, CGameObject* pObj);

	template <typename T>
	T*		Get_Pool(const _int& iPoolType)
	{
		if (iPoolType >= m_iMaxPoolType)
		{
			return nullptr;
		}

		CGameObject* pInstance = m_vecPool[iPoolType].front();
		m_vecPool[iPoolType].pop_front();

		return dynamic_cast<T*>(pInstance);
	}

	HRESULT		Back_Pool(const _int& iPoolType, CGameObject* pObj);

private:
	_int									m_iMaxPoolType = 0;
	_int									m_iPoolSize = 0;
	vector<list<CGameObject*>>				m_vecPool;
	vector<CGameObject*>					m_vecOriginalPool;

private:
	inline virtual void freeMem();
};

END
#endif // PoolMgr_h__
