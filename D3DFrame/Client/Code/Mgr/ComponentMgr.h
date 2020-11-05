#ifndef ComponentMgr_h__
#define ComponentMgr_h__

#include "Base.h"

#include "Transform.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Sphere.h"
#include "ControllerBase.h"
#include "Component/StatCom.h"
#include "Component/RigidBody.h"
#include "Shader.h"
#include "Light.h"
#include "Item/ItemBase.h"

class CComponentMgr : public CBase
{
	DECLARE_SINGLETON(CComponentMgr)

private:
	explicit							CComponentMgr(void);
	virtual								~CComponentMgr(void);

public:
	HRESULT								Add_Component(const Engine::_tchar* pKey, Engine::CComponent* pCom);
	template <typename T>
	T* Get_Component(const Engine::_tchar* pKey)
	{
		auto iter = find_if(m_mapComponent.begin(), m_mapComponent.end(), Engine::CTag_Finder(pKey));

		if (m_mapComponent.end() == iter)
		{
			return nullptr;
		}

		return iter->second->Clone();
	}

private:
	map<wstring, Engine::CComponent*>	m_mapComponent;

private:
	inline virtual void					Free(void);
};
#endif // ComponentMgr_h__
