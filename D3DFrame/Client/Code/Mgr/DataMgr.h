#ifndef DataMgr_h__
#define DataMgr_h__

#include "Base.h"

class CData;

class CClientDataMgr : public CBase
{
	DECLARE_SINGLETON(CClientDataMgr)

private:
	explicit							CClientDataMgr(void);
	virtual								~CClientDataMgr(void);

public:
	HRESULT								Load_SceneChanger(void);
	HRESULT								Load_Prefab(Engine::_int& iCurIdx);
	HRESULT								Load_FieldData(Engine::_int& iCurIdx);
	HRESULT								Load_DungeonData(Engine::_int& iCurIdx);

	Engine::CGameObject*				Clone_Terrain(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_vec3 * pAngle, const Engine::_tchar * pKey);
	Engine::CGameObject*				Clone_StaticMesh(const OBJECT_INFO& tInfo, const Engine::_float& fRadius);
	HRESULT								Clone_CharacterObj(const Engine::_tchar* pType, const Engine::_tchar* pName, const Engine::_vec3* pPos);
	Engine::CGameObject*				Clone_DynamicObj(const Engine::_tchar* pName, const Engine::_vec3* pPos);
	HRESULT								Clone_Skybox(const Engine::_tchar* pName);

	Engine::_int						GetDataCount(const Engine::_tchar* pFileName);

private:
	template<typename T>
	HRESULT add_Prefab(LPDIRECT3DDEVICE9 pGraphicDev)
	{
		T* pInstance = T::Create(pGraphicDev);

		const _tchar* pName = pInstance->Get_Name();
		auto iter = m_mapPrefab.find(pName);

		if (m_mapPrefab.end() != iter)
		{
			Engine::Safe_Release(pInstance);
			return E_FAIL;
		}

		m_mapPrefab.emplace(pName, pInstance);

		return S_OK;
	}

	HRESULT								load_FieldStageMap(Engine::_int& iCurIdx);
	HRESULT								load_FieldDynamicObj(Engine::_int& iCurIdx);

	HRESULT								load_Map(Engine::_int& iCurIdx);
	HRESULT								load_StaticMesh(Engine::_int& iCurIdx);
	HRESULT								load_Texture(Engine::_int& iCurIdx);
	HRESULT								load_DynamicMesh(Engine::_int& iCurIdx);
	HRESULT								load_Font(Engine::_int& iCurIdx);

private:
	const Engine::_tchar*				m_szDefaultPath;

	map<wstring, list<FILE_INFO*>>		m_FileMap;
	map<wstring, Engine::CGameObject*>	m_mapPrefab;

private:
	inline virtual void					Free(void);
};

#endif // DataMgr_h__
