#ifndef ToolObjMgr_h__
#define ToolObjMgr_h__

#include "Engine_Defines.h"
#include "ToolObjContainer.h"

BEGIN(Engine)
class CGameObject;
END


class CToolObjMgr
{
	DECLARE_SINGLETON(CToolObjMgr)

private:
	explicit					CToolObjMgr(void);
	virtual						~CToolObjMgr(void);

public:
	void						Update(const float fTimeDelta);
	void						Render(void);

	void						Add_ObjList(const Engine::_tchar* pType, const Engine::_tchar* pKey, Engine::CGameObject* pObj);
	Engine::CGameObject*		Add_Prefab(const Engine::_tchar* pKey, Engine::CGameObject* pObj);
	
	void						Delete_Obj(const Engine::_tchar* pType, const Engine::_tchar* pKey);

	void						Set_PrefabObj(const Engine::_tchar* pKey);
	Engine::CGameObject*		Get_CurPrefabObj(void);

	void						Cancel_PrefabObj(void);
	
	Engine::CGameObject*		Clone(const Engine::_tchar* pKey);
	const map<const Engine::_tchar*, Engine::CGameObject*>*	Get_Map(const Engine::_tchar* pKey);
	const map<const Engine::_tchar*, Engine::CGameObject*>*	Get_PrefabMap(void);

	template <typename T>
	T*	Get_Obj(const Engine::_tchar* pType, const Engine::_tchar* pKey)
	{
		auto iter = find_if(m_mapObjList.begin(), m_mapObjList.end(), Engine::CTag_Finder(pType));

		if (m_mapObjList.end() == iter)
		{
			return nullptr;
		}

		return dynamic_cast<T*>(iter->second->Get_Obj(pKey));
	}

	template <typename T>
	T*	Get_PrefabObj(const Engine::_tchar* pKey)
	{
		auto iter = find_if(m_mapPrefab.begin(), m_mapPrefab.end(), Engine::CTag_Finder(pKey));

		if (m_mapPrefab.end() == iter)
		{
			return nullptr;
		}

		return dynamic_cast<T*>(iter->second);
	}


private:
	map<const Engine::_tchar*, CToolObjContainer*>		m_mapObjList;
	map<const Engine::_tchar*, Engine::CGameObject*>	m_mapPrefab;

	Engine::CGameObject*								m_pPrefabObj;
};

#endif // ToolObjMgr_h__
