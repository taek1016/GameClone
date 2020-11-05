#include "stdafx.h"
#include "LoadingThread.h"

USING(Engine)

CLoading::CLoading(void)
	: m_bFinish(false)
	, m_iCurCnt(0)
	, m_iMaxCnt(0)
{
	ZeroMemory(m_szLoading, sizeof(_tchar) * 256);
}

CLoading::~CLoading(void)
{
}

HRESULT CLoading::Initialize_LoadingThread(LOADINGID eLoading)
{
	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, Thread_Main, this, 0, NULL);

	m_eLoadingID = eLoading;

	return S_OK;
}

Engine::_uint CLoading::Loading_Data(void)
{
	DLL::pDataMgr->Load_Prefab(m_iCurCnt);

	m_bFinish = true;
	printf("Prefab Count : %d\n", m_iCurCnt);

	return 0;
}

Engine::_uint CLoading::Loading_Field(void)
{
	DLL::pDataMgr->Load_FieldData(m_iCurCnt);

	m_bFinish = true;
	printf("Field Count : %d\n", m_iCurCnt);

	return 0;
}

Engine::_uint CLoading::Loading_Dungeon(void)
{
	DLL::pDataMgr->Load_DungeonData(m_iCurCnt);

	m_bFinish = true;

	return 0;
}

void CLoading::Loading_DataCount(const Engine::_tchar * pPath)
{
	m_iMaxCnt = DLL::pDataMgr->GetDataCount(pPath);
}

Engine::_uint CLoading::Thread_Main(void * pArg)
{
	CLoading* pLoading = reinterpret_cast<CLoading*>(pArg);

	_uint iFlag = 0;

	EnterCriticalSection(pLoading->Get_Crt());

	switch (pLoading->Get_LoadingID())
	{
	case LOADING_DATA:
		pLoading->Loading_DataCount(L"PrefabCount");
		iFlag = pLoading->Loading_Data();
		break;

	case LOADING_FIELD:
		iFlag = pLoading->Loading_Field();
		break;

	case LOADING_DUNGEON:
		iFlag = pLoading->Loading_Dungeon();
		break;
	}

	LeaveCriticalSection(pLoading->Get_Crt());
	_endthreadex(0);

	return iFlag;
}

CLoading * CLoading::Create(LOADINGID eLoading)
{
	CLoading*	pInstance = new CLoading;

	if (FAILED(pInstance->Initialize_LoadingThread(eLoading)))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

inline void CLoading::Free(void)
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);
}
