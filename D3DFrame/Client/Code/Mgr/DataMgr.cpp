#include "stdafx.h"
#include "DataMgr.h"

#include "Objects/StaticGameObject.h"
#include "Objects/Terrain.h"

#include "NaviMesh.h"

#include "Character/Character.h"

#include "Character/Player.h"

#include "Character/Monster/Boar.h"
#include "Character/Monster/DoomGuard.h"
#include "Character/Monster/Infernal.h"
#include "Character/Monster/Nefarian.h"
#include "Character/Monster/KodoBeast.h"

#include "Character/Vehicle/Chicken.h"
#include "Character/Vehicle/Gryphon.h"

#include "Character/NPC/NPC_juljin.h"
#include "Character/NPC/NPC_Thrall.h"

#include "Character/Supporter/WaterElemental.h"

#include "Objects/Skybox/FieldSkybox.h"

USING(Engine)

IMPLEMENT_SINGLETON(CClientDataMgr)

CClientDataMgr::CClientDataMgr(void)
	: CBase()
	, m_szDefaultPath(L"../../Data/Path/")
{
}

CClientDataMgr::~CClientDataMgr(void)
{
	Free();
}

HRESULT CClientDataMgr::Load_SceneChanger(void)
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	const _tchar* pType = L"SceneChanger";

	const int iMaxStr = 256;

	TCHAR szPath[iMaxStr]{};

	wsprintf(szPath, L"%s%s", m_szDefaultPath, L"SceneChanger.txt");

	wifstream fIn;

	fIn.open(szPath);

	if (fIn.fail())
	{
		return E_FAIL;
	}

	TCHAR szObjectKey[iMaxStr]{};
	TCHAR szObjectFilePath[iMaxStr]{};
	TCHAR szObjectImageCount[iMaxStr]{};
	TCHAR szObjectFileName[iMaxStr]{};

	TCHAR szToken = '|';

	FILE_INFO* pInfo = nullptr;

	CGameObject* pObj = nullptr;
	while (true)
	{
		fIn.getline(szObjectKey, iMaxStr, szToken);
		fIn.getline(szObjectImageCount, iMaxStr, szToken);
		fIn.getline(szObjectFileName, iMaxStr, szToken);
		fIn.getline(szObjectFilePath, iMaxStr);

		pInfo = new FILE_INFO;

		pInfo->wStrName = szObjectKey;
		pInfo->wStrFileName = szObjectFileName;
		pInfo->wStrFilePath = szObjectFilePath;
		pInfo->iResourceCount = _ttoi(szObjectImageCount);

		m_FileMap[pType].push_back(pInfo);

		if (fIn.eof())
		{
			break;
		}
	}

	TCHAR szFilePath[iMaxStr]{};
	for (auto& iter : m_FileMap[pType])
	{
		::ZeroMemory(szFilePath, sizeof(TCHAR) * iMaxStr);
		wsprintf(szFilePath, L"%s%s", iter->wStrFilePath.c_str(), iter->wStrFileName.c_str());

		DLL::pResourcesMgr->Initialize_Texture(
			pGraphicDev,
			RESOURCE_TEXTURE,
			iter->wStrName.c_str(),
			TEXTURETYPE::TEX_NORMAL,
			szFilePath
		);
	}

	return S_OK;
}

HRESULT CClientDataMgr::Load_Prefab(_int& iCurIdx)
{
	FAILED_CHECK_RETURN(load_Map(iCurIdx), E_FAIL);
	FAILED_CHECK_RETURN(load_Texture(iCurIdx), E_FAIL);
	FAILED_CHECK_RETURN(load_StaticMesh(iCurIdx), E_FAIL);
	FAILED_CHECK_RETURN(load_DynamicMesh(iCurIdx), E_FAIL);
	FAILED_CHECK_RETURN(load_Font(iCurIdx), E_FAIL);
	DLL::pSoundMgr->Initialize();

	return S_OK;
}

HRESULT CClientDataMgr::Load_FieldData(_int& iCurIdx)
{
	DLL::pObjMgr->Clear_List();

	load_FieldStageMap(iCurIdx);
	load_FieldDynamicObj(iCurIdx);

	return S_OK;
}

HRESULT CClientDataMgr::Load_DungeonData(_int& iCurIdx)
{
	return S_OK;
}

Engine::CGameObject * CClientDataMgr::Clone_Terrain(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_vec3 * pAngle, const Engine::_tchar * pKey)
{
	CTerrain* pTerrain = dynamic_cast<CTerrain*>(m_mapPrefab[L"Terrain"]->Clone());

	pTerrain->Initialize_Terrain(pPos, pScale, pAngle, pKey);
	pTerrain->Late_Initialize();

	return pTerrain;
}

Engine::CGameObject * CClientDataMgr::Clone_StaticMesh(const OBJECT_INFO & tInfo, const Engine::_float & fRadius)
{
	CStaticObject* pObj = dynamic_cast<CStaticObject*>(m_mapPrefab[tInfo.wStrRenderKey.c_str()]->Clone());
	
	auto pTransform = pObj->Get_Component<CTransform>(L"Transform", ID_DYNAMIC);

	pTransform->Set_Info(INFO::INFO_POS, &tInfo.tInfo.vPos);
	pTransform->Set_Scale(&tInfo.tInfo.vScale);
	pTransform->Set_Angle(&tInfo.tInfo.vAngle);

	pObj->Make_Collider(&tInfo.tInfo.vPos, fRadius);

	return pObj;
}

HRESULT CClientDataMgr::Clone_CharacterObj(const _tchar* pType, const _tchar * pName, const Engine::_vec3 * pPos)
{
	auto iter = m_mapPrefab.find(pName);

	if (m_mapPrefab.end() == iter)
	{
		return E_FAIL;
	}

	CCharacterBase* pObj = dynamic_cast<CCharacterBase*>(iter->second->Clone());
	pObj->Set_Position(pPos);

	DLL::pObjMgr->Add_GameObject(pType, pObj);

	return S_OK;
}

Engine::CGameObject * CClientDataMgr::Clone_DynamicObj(const Engine::_tchar * pName, const Engine::_vec3 * pPos)
{
	auto iter = m_mapPrefab.find(pName);

	if (m_mapPrefab.end() == iter)
	{
		return nullptr;
	}

	CCharacterBase* pObj = dynamic_cast<CCharacterBase*>(iter->second->Clone());
	pObj->Set_Position(pPos);

	return pObj;
}

HRESULT CClientDataMgr::Clone_Skybox(const Engine::_tchar * pName)
{
	auto iter = m_mapPrefab.find(pName);

	if (m_mapPrefab.end() == iter)
	{
		return E_FAIL;
	}

	CSkyBox* pSky = dynamic_cast<CSkyBox*>(iter->second->Clone());

	DLL::pObjMgr->Add_GameObject(L"Skybox", pSky);

	return S_OK;
}

Engine::_int CClientDataMgr::GetDataCount(const Engine::_tchar * pFileName)
{
	_int iCount;

	const int iMaxStr = 256;
	TCHAR szFullPath[iMaxStr]{};
	wsprintf(szFullPath, L"%s%s%s", m_szDefaultPath, pFileName, L".count");

	HANDLE hFile = CreateFile(szFullPath, GENERIC_READ, 0, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return E_FAIL;
	}
	DWORD dwBytes;
	ReadFile(hFile, &iCount, sizeof(Engine::_int), &dwBytes, NULL);

	CloseHandle(hFile);

	return iCount;
}

HRESULT CClientDataMgr::load_FieldStageMap(Engine::_int & iCurIdx)
{
	const _tchar* pPath = L"../../Data/FieldStage/StageField";

	HANDLE hFile = nullptr;

	const int iMaxStr = 256;
	TCHAR szFullPath[iMaxStr]{};
	wsprintf(szFullPath, L"%s%s", pPath, L".terrain");

	// 지형 데이터
	hFile = CreateFile(szFullPath, GENERIC_READ, 0, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return E_FAIL;
	}

	DWORD dwBytes = 0;

	TCHAR szName[iMaxStr]{};
	::ZeroMemory(szName, sizeof(TCHAR) * iMaxStr);

	_int iSize = 0;
	ReadFile(hFile, &iSize, sizeof(Engine::_int), &dwBytes, NULL);

	ReadFile(hFile, szName, sizeof(TCHAR) * iSize, &dwBytes, NULL);

	_vec3 vPos, vScale, vAngle;
	ReadFile(hFile, &vPos, sizeof(Engine::_vec3), &dwBytes, NULL);
	ReadFile(hFile, &vScale, sizeof(Engine::_vec3), &dwBytes, NULL);
	ReadFile(hFile, &vAngle, sizeof(Engine::_vec3), &dwBytes, NULL);

	CloseHandle(hFile);

	CTerrain* pTerrain = dynamic_cast<CTerrain*>(DLL::pDataMgr->Clone_Terrain(&vPos, &vScale, &vAngle, szName));

	wsprintf(szFullPath, L"%s%s", pPath, L".navi");

	// 지형 데이터
	hFile = CreateFile(szFullPath, GENERIC_READ, 0, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return E_FAIL;
	}

	const int iThreePoint = 3;
	_vec3 vPosition[3];
	while (true)
	{
		ReadFile(hFile, vPosition, sizeof(_vec3) * iThreePoint, &dwBytes, NULL);
		if (0 == dwBytes)
		{
			break;
		}

		pTerrain->Add_Cell(&vPosition[0], &vPosition[1], &vPosition[2]);
	}
	pTerrain->Link_NaviMesh();

	DLL::pObjMgr->Add_GameObject(L"Terrain", pTerrain);

	// 스테틱 메쉬 로딩
	wsprintf(szFullPath, L"%s%s", pPath, L".staticMeshdat");
	hFile = CreateFile(szFullPath, GENERIC_READ, 0, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return E_FAIL;
	}

	OBJECT_INFO tInfo{};
	_float fRadius;
	while (true)
	{
		::ZeroMemory(szName, sizeof(TCHAR) * iMaxStr);

		// 데이터 출력
		ReadFile(hFile, &tInfo, sizeof(OBJECTBASE_INFO), &dwBytes, NULL);

		if (0 == dwBytes)
		{
			break;
		}

		// 이름 출력
		ReadFile(hFile, &iSize, sizeof(Engine::_int), &dwBytes, NULL);
		ReadFile(hFile, szName, sizeof(TCHAR) * iSize, &dwBytes, NULL);
		szName[iSize] = '\0';

		tInfo.wStrRenderKey = szName;

		ReadFile(hFile, &fRadius, sizeof(_float), &dwBytes, NULL);

		DLL::pObjMgr->Add_GameObject(L"StaticObject", Clone_StaticMesh(tInfo, fRadius));
	}
	CloseHandle(hFile);


	return S_OK;
}

HRESULT CClientDataMgr::load_FieldDynamicObj(Engine::_int & iCurIdx)
{
	const _tchar* pPath = L"../../Data/FieldStage/";

	const _tchar* pFileName[] = { L"Player", L"Monster", L"NPC" };

	const _int iSize = sizeof(pFileName) / sizeof(pFileName[0]);

	HANDLE hFile = nullptr;

	const int iMaxStr = 256;
	TCHAR szFullPath[iMaxStr]{};

	DWORD dwBytes = 0;

	TCHAR szName[iMaxStr]{};
	::ZeroMemory(szName, sizeof(TCHAR) * iMaxStr);

	_int iNameSize;

	_vec3 vPos, vAngle;

	for (_int i = 0; i < iSize; ++i)
	{
		::ZeroMemory(szFullPath, sizeof(_tchar) * iMaxStr);

		wsprintf(szFullPath, L"%s%s%s", pPath, pFileName[i], L".dynamicObjdat");

		// 지형 데이터
		hFile = CreateFile(szFullPath, GENERIC_READ, 0, nullptr,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			return E_FAIL;
		}

		while (true)
		{
			ReadFile(hFile, &iNameSize, sizeof(_int), &dwBytes, NULL);

			if (0 == dwBytes)
			{
				break;
			}

			::ZeroMemory(szName, sizeof(_tchar) * iMaxStr);
			ReadFile(hFile, szName, sizeof(_tchar) * iNameSize, &dwBytes, NULL);

			ReadFile(hFile, &vPos, sizeof(_vec3), &dwBytes, NULL);
			ReadFile(hFile, &vAngle, sizeof(_vec3), &dwBytes, NULL);

			vPos.y += 1.f;
			Clone_CharacterObj(pFileName[i], szName, &vPos);

			iCurIdx++;
		}

		CloseHandle(hFile);
	}

	return S_OK;
}

HRESULT CClientDataMgr::load_Map(Engine::_int & iCurIdx)
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	CTerrain* pObj = CTerrain::Create(pGraphicDev);
	pObj->Initialize_GameObject();
	m_mapPrefab.emplace(L"Terrain", pObj);

	const _tchar* pDefaultPath = L"../../Resources/Map/";

	const _tchar* szNames[] = { L"FieldStage" };
	const int iCount = sizeof(szNames) / sizeof(szNames[0]);


	const int iMaxStr = 256;
	TCHAR szFileNames[iMaxStr]{};

	for (int i = 0; i < iCount; ++i)
	{
		::ZeroMemory(szFileNames, sizeof(TCHAR) * iMaxStr);
		wsprintf(szFileNames, L"%s%s", szNames[i], L".X");

		DLL::pResourcesMgr->Initialize_Meshes(
			pGraphicDev, 
			RESOURCE_STATIC, 
			szNames[i], 
			TYPE_STATIC, 
			pDefaultPath, 
			szFileNames
		);

		iCurIdx++;
	}

	return S_OK;
}

HRESULT CClientDataMgr::load_StaticMesh(_int& iCurIdx)
{
	const _tchar* pType = L"StaticMesh";

	const int iMaxStr = 256;

	TCHAR szPath[iMaxStr]{};

	wsprintf(szPath, L"%s%s", m_szDefaultPath, L"StaticMesh.txt");

	wifstream fIn;

	fIn.open(szPath);

	if (fIn.fail())
	{
		return E_FAIL;
	}

	TCHAR szObjectKey[iMaxStr]{};
	TCHAR szObjectFilePath[iMaxStr]{};
	TCHAR szObjectImageCount[iMaxStr]{};
	TCHAR szObjectFileName[iMaxStr]{};

	TCHAR szToken = '|';

	FILE_INFO* pInfo = nullptr;

	CGameObject* pObj = nullptr;
	while (true)
	{
		fIn.getline(szObjectKey, iMaxStr, szToken);
		fIn.getline(szObjectImageCount, iMaxStr, szToken);
		fIn.getline(szObjectFileName, iMaxStr, szToken);
		fIn.getline(szObjectFilePath, iMaxStr);

		if (fIn.eof())
		{
			break;
		}

		pInfo = new FILE_INFO;

		pInfo->wStrName			= szObjectKey;
		pInfo->wStrFileName		= szObjectFileName;
		pInfo->wStrFilePath		= szObjectFilePath;
		pInfo->iResourceCount	= _ttoi(szObjectImageCount);

		m_FileMap[pType].push_back(pInfo);
	}

	auto pGraphicDev = DLL::pGraphicDev->GetDevice();
	for (auto& iter : m_FileMap[pType])
	{
		DLL::pResourcesMgr->Initialize_Meshes(
			pGraphicDev, 
			RESOURCE_STATIC, 
			iter->wStrName.c_str(), 
			TYPE_STATIC, 
			iter->wStrFilePath.c_str(), 
			iter->wStrFileName.c_str()
		);

		pObj = CStaticObject::Create(pGraphicDev, iter->wStrName.c_str());
		pObj->Initialize_GameObject();
		m_mapPrefab.emplace(iter->wStrName.c_str(), pObj);

		iCurIdx++;
	}

	return S_OK;
}

HRESULT CClientDataMgr::load_Texture(_int& iCurIdx)
{
	const _tchar* pType = L"Texture";

	const int iMaxStr = 256;

	TCHAR szPath[iMaxStr]{};

	wsprintf(szPath, L"%s%s", m_szDefaultPath, L"Textures.txt");

	wifstream fIn;

	fIn.open(szPath);

	if (fIn.fail())
	{
		return E_FAIL;
	}

	TCHAR szObjectKey[iMaxStr]{};
	TCHAR szObjectFilePath[iMaxStr]{};
	TCHAR szObjectImageCount[iMaxStr]{};
	TCHAR szObjectFileName[iMaxStr]{};

	TCHAR szToken = '|';

	FILE_INFO* pInfo = nullptr;

	while (true)
	{
		fIn.getline(szObjectKey, iMaxStr, szToken);
		fIn.getline(szObjectImageCount, iMaxStr, szToken);
		fIn.getline(szObjectFileName, iMaxStr, szToken);
		fIn.getline(szObjectFilePath, iMaxStr);

		if (fIn.eof())
		{
			break;
		}

		pInfo = new FILE_INFO;

		pInfo->wStrName = szObjectKey;
		pInfo->wStrFileName = szObjectFileName;
		pInfo->wStrFilePath = szObjectFilePath;
		pInfo->iResourceCount = _ttoi(szObjectImageCount);

		m_FileMap[pType].push_back(pInfo);
	}

	auto pGraphicDev = DLL::pGraphicDev->GetDevice();
	TCHAR szFilePath[iMaxStr];
	for (auto& iter : m_FileMap[pType])
	{
		ZeroMemory(szFilePath, sizeof(TCHAR) * iMaxStr);
		wsprintf(szFilePath, L"%s%s", iter->wStrFilePath.c_str(), iter->wStrFileName.c_str());

		DLL::pResourcesMgr->Initialize_Texture(
			pGraphicDev,
			RESOURCE_TEXTURE,
			iter->wStrName.c_str(),
			TEXTURETYPE::TEX_NORMAL,
			szFilePath,
			iter->iResourceCount
		);

		iCurIdx++;
	}
	return S_OK;
}

HRESULT CClientDataMgr::load_DynamicMesh(_int& iCurIdx)
{
	const _tchar* pType = L"DynamicMesh";

	const int iMaxStr = 256;

	TCHAR szPath[iMaxStr]{};

	wsprintf(szPath, L"%s%s", m_szDefaultPath, L"DynamicMesh.txt");

	wifstream fIn;

	fIn.open(szPath);

	if (fIn.fail())
	{
		return E_FAIL;
	}

	TCHAR szObjectKey[iMaxStr]{};
	TCHAR szObjectFilePath[iMaxStr]{};
	TCHAR szObjectImageCount[iMaxStr]{};
	TCHAR szObjectFileName[iMaxStr]{};

	TCHAR szToken = '|';

	FILE_INFO* pInfo = nullptr;

	CGameObject* pObj = nullptr;
	while (true)
	{
		fIn.getline(szObjectKey, iMaxStr, szToken);
		fIn.getline(szObjectImageCount, iMaxStr, szToken);
		fIn.getline(szObjectFileName, iMaxStr, szToken);
		fIn.getline(szObjectFilePath, iMaxStr);

		if (fIn.eof())
		{
			break;
		}

		pInfo = new FILE_INFO;

		pInfo->wStrName = szObjectKey;
		pInfo->wStrFileName = szObjectFileName;
		pInfo->wStrFilePath = szObjectFilePath;
		pInfo->iResourceCount = _ttoi(szObjectImageCount);

		m_FileMap[pType].push_back(pInfo);
	}

	auto pGraphicDev = DLL::pGraphicDev->GetDevice();
	for (auto& iter : m_FileMap[pType])
	{
		DLL::pResourcesMgr->Initialize_Meshes(
			pGraphicDev,
			RESOURCE_DYNAMIC,
			iter->wStrName.c_str(),
			TYPE_DYNAMIC,
			iter->wStrFilePath.c_str(),
			iter->wStrFileName.c_str()
		);

		iCurIdx++;
	}

	// 플레이어
	add_Prefab<CPlayer>(pGraphicDev);

	// 몬스터
	add_Prefab<CBoar>(pGraphicDev);
	add_Prefab<CDoomGuard>(pGraphicDev);
	add_Prefab<CInfernal>(pGraphicDev);
	add_Prefab<CKodoBeast>(pGraphicDev);
	add_Prefab<CNefarian>(pGraphicDev);

	// 스카이박스
	add_Prefab<CFieldSkybox>(pGraphicDev);

	// 탈 것
	add_Prefab<CChicken>(pGraphicDev);
	add_Prefab<CGryphon>(pGraphicDev);

	// 소환수
	add_Prefab<CWaterElemental>(pGraphicDev);

	// NPC
	add_Prefab<CNPC_Zuljin>(pGraphicDev);
	add_Prefab<CNPC_Thrall>(pGraphicDev);

	DLL::pEffectMgr->Initialize_Effect(pGraphicDev);

	return S_OK;
}

HRESULT CClientDataMgr::load_Font(Engine::_int & iCurIdx)
{
	const _tchar* pType = L"Font";

	const int iMaxStr = 256;

	TCHAR szPath[iMaxStr]{};

	wsprintf(szPath, L"%s%s", m_szDefaultPath, L"Font.txt");

	std::locale::global(std::locale("Korean"));

	wifstream fIn;

	fIn.open(szPath);

	if (fIn.fail())
	{
		return E_FAIL;
	}

	TCHAR szObjectKey[iMaxStr]{};
	TCHAR szObjectFilePath[iMaxStr]{};
	TCHAR szObjectImageCount[iMaxStr]{};
	TCHAR szObjectFileName[iMaxStr]{};

	TCHAR szToken = '|';

	FILE_INFO* pInfo = nullptr;

	while (true)
	{
		fIn.getline(szObjectKey, iMaxStr, szToken);
		fIn.getline(szObjectImageCount, iMaxStr, szToken);
		fIn.getline(szObjectFileName, iMaxStr, szToken);
		fIn.getline(szObjectFilePath, iMaxStr);

		if (fIn.eof())
		{
			break;
		}

		pInfo = new FILE_INFO;

		pInfo->wStrName = szObjectKey;
		pInfo->wStrFileName = szObjectFileName;
		pInfo->wStrFilePath = szObjectFilePath;
		pInfo->iResourceCount = _ttoi(szObjectImageCount);

		m_FileMap[pType].push_back(pInfo);
	}

	auto pGraphicDev = DLL::pGraphicDev->GetDevice();
	TCHAR szFilePath[iMaxStr];

	for (auto& iter : m_FileMap[pType])
	{
		ZeroMemory(szFilePath, sizeof(TCHAR) * iMaxStr);
		wsprintf(szFilePath, L"%s%s", iter->wStrFilePath.c_str(), iter->wStrFileName.c_str());

		DLL::pResourcesMgr->Initialize_Texture(
			pGraphicDev,
			RESOURCE_TEXTURE,
			iter->wStrName.c_str(),
			TEXTURETYPE::TEX_NORMAL,
			szFilePath,
			iter->iResourceCount
		);

		const _tchar* pKey = iter->wStrName.c_str();
		DLL::pFontMgr->Add_SingleFont(L"KOverwatch", pKey, DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, pKey));

		iCurIdx++;
	}

	return S_OK;
}

inline void CClientDataMgr::Free(void)
{
	for (auto iter : m_mapPrefab)
	{
		Safe_Release(iter.second);
	}

	m_mapPrefab.clear();
}
