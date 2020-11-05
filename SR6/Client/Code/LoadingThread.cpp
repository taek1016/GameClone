#include "stdafx.h"
#include "LoadingThread.h"

#include "SceneObject/Player.h"
#include "SceneObject/Terrain.h"
#include "SceneObject/Zombie.h"
#include "SceneObject/Wolf.h"
#include "SceneObject/Bullet.h"
#include "SceneObject/Iron.h"
#include "SceneObject/Tree.h"
#include "SceneObject/BossZombie.h"

#include "Component/Body.h"

#include "Effect/BloodParticle.h"
#include "Effect/GunParticle.h"
#include "Effect/Vomit.h"
#include "Effect/Fragment.h"
#include "Effect/FireWork.h"

USING(Engine)

CLoading::CLoading()
	: m_bFinish(false)
	, m_iCurCnt(0)
	, m_iMaxCnt(55)
{
	ZeroMemory(m_szLoading, sizeof(_tchar) * 256);
}

CLoading::~CLoading(void)
{
}

_uint	CALLBACK CLoading::Thread_Main(void* pArg)
{
	CLoading*		pLoading = (CLoading*)pArg;

	_uint iFlag = 0;

	EnterCriticalSection(pLoading->Get_Crt());

	switch (pLoading->Get_LoadingID())
	{
	case LOADING_STAGE:
		iFlag = pLoading->Loading_ForStage();
		break;

	case LOADING_BOSS:
		break;
	}

	CInGameObject* player = dynamic_cast<CInGameObject*>(DLL::pObjContainer->Add_Obj<CPlayer>(L"Player"));
	DLL::pObjContainer->Add_Obj<CTerrain>(L"Terrain");
	DLL::pObjContainer->Add_Obj<CZombie>(L"Zombie");
	DLL::pObjContainer->Add_Obj<CWolf>(L"Wolf");
	DLL::pObjContainer->Add_Obj<CIron>(L"Iron");
	DLL::pObjContainer->Add_Obj<CTree>(L"Tree");

	HANDLE hFile = CreateFile(
		L"../../Character.dat", /* 파일 경로 */
		GENERIC_READ,
		0,
		nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	player->LoadData(hFile);


	CloseHandle(hFile);

	CInGameObject* boss = dynamic_cast<CInGameObject*>(DLL::pObjContainer->Add_Obj<CBossZombie>(L"BossZombie"));

	hFile = CreateFile(
		L"../../Zombie.dat", /* 파일 경로 */
		GENERIC_READ,
		0,
		nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	boss->LoadData(hFile);

	CloseHandle(hFile);

	DLL::pPoolMgr->Add_Pool(POOL_BULLET, CBullet::Create());
	DLL::pPoolMgr->Add_Pool(POOL_PARTICLE, CBloodParticle::Create());
	DLL::pPoolMgr->Add_Pool(POOL_GUNFIRE, CGunParticle::Create());
	DLL::pPoolMgr->Add_Pool(POOL_FRAGMENT, CFragment::Create());
	DLL::pPoolMgr->Add_Pool(POOL_VOMIT, CVomit::Create());
	DLL::pPoolMgr->Add_Pool(POOL_FIREWORK, CFireWork::Create());
	
	LeaveCriticalSection(pLoading->Get_Crt());
	_endthreadex(0);

	DLL::pColMgr->Clear_List();

	return iFlag;
}

HRESULT CLoading::Ready_Loading(LOADINGID eLoading)
{
	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, Thread_Main, this, 0, NULL);

	m_eLoading = eLoading;

	return S_OK;
}

_uint CLoading::Loading_ForStage(void)
{
	_ulong dwCntZ = 129;
	_ulong dwCntX = 129;
	_ulong dwVtxInterval = 1;
	// 1
	DLL::pResourceMgr->Initialize_Buffer(RESOURCE_STATIC,
		L"Buffer_TerrainTex",
		Engine::BUFFER_TERRAINTEX,
		dwCntX,
		dwCntZ,
		dwVtxInterval);
	m_iCurCnt++;
	//2
	DLL::pResourceMgr->Initialize_Buffer(RESOURCE_STATIC,
		L"Buffer_CubeTex",
		Engine::BUFFER_CUBETEX);
	m_iCurCnt++;
	//3
	DLL::pResourceMgr->Initialize_Buffer(RESOURCE_STATIC,
		L"Buffer_TriCol",
		Engine::BUFFER_TRICOL);
	m_iCurCnt++;
	//4
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Barricade",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Objects/Barricade/Barricade.png"),
		E_FAIL);
	m_iCurCnt++;
	//5
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Cursor",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/Mouse/Cursor.png"),
		E_FAIL);
	m_iCurCnt++;
	//6
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Cursor_no",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/Mouse/Cursor_no.png"),
		E_FAIL);
	m_iCurCnt++;
	//7
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"PlayerRightArm",
		Engine::TEX_CUBE,
		L"../Bin/Texture/Player/Parts/Player0.dds"),
		E_FAIL);
	m_iCurCnt++;
	//8
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"PlayerBody",
		Engine::TEX_CUBE,
		L"../Bin/Texture/Player/Parts/Player1.dds"),
		E_FAIL);
	m_iCurCnt++;
	//9
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"PlayerHead",
		Engine::TEX_CUBE,
		L"../Bin/Texture/Player/Parts/Player2.dds"),
		E_FAIL);
	m_iCurCnt++;
	//10
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"PlayerRightLeg",
		Engine::TEX_CUBE,
		L"../Bin/Texture/Player/Parts/Player3.dds"),
		E_FAIL);
	m_iCurCnt++;
	//11
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"PlayerLeftArm",
		Engine::TEX_CUBE,
		L"../Bin/Texture/Player/Parts/Player4.dds"),
		E_FAIL);
	m_iCurCnt++;
	//12
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"PlayerLeftLeg",
		Engine::TEX_CUBE,
		L"../Bin/Texture/Player/Parts/Player5.dds"),
		E_FAIL);
	m_iCurCnt++;
	//13
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Texture_SkyBox",
		Engine::TEX_CUBE,
		L"../Bin/Texture/SkyBox/skybox.dds"
		),
		E_FAIL);
	m_iCurCnt++;
	//14
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"HP1",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/HP/HP1.png"),
		E_FAIL);
	m_iCurCnt++;
	//15
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"HP2",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/HP/HP2.png"),
		E_FAIL);
	m_iCurCnt++;
	//16
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"HP0",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/HP/HP0.png"),
		E_FAIL);
	m_iCurCnt++;
	//17
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Iron",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Objects/Stone/Stone%d.png", 5),
		E_FAIL);
	m_iCurCnt++;
	//18
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Tree",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Objects/Tree/Tree%d.png", 3),
		E_FAIL);
	m_iCurCnt++;
	//19
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Bullet",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Bullet/Bullet%d.png"),
		E_FAIL);
	m_iCurCnt++;
	//20
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"WoodIcon",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Material/Wood.png"),
		E_FAIL);
	m_iCurCnt++;
	//21
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"IronIcon",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Material/Stone.png"),
		E_FAIL);
	m_iCurCnt++;
	//22
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Slot",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/Slot/Slot%d.png", 2),
		E_FAIL);

	m_iCurCnt++;
	//23
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Craft",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/Craft/Craft%d.png", 2),
		E_FAIL);

	m_iCurCnt++;
	//24
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"GunFire",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Effect/GunFire/gunFire%d.png", 6),
		E_FAIL);

	m_iCurCnt++;
	//25
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"BloodParticle",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Effect/Blood.png"),
		E_FAIL);
	m_iCurCnt++;
	//26
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_LOGO,
		L"TitleBack",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/Title/BackGround/TitleBackground.png"),
		E_FAIL);
	m_iCurCnt++;
	//27
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_LOGO,
		L"PressEnter",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/Title/Press/0.png"),
		E_FAIL);
	m_iCurCnt++;
	//28
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"ZombieAttack",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Monster/Zombie/Attack/%d.png", 3),
		E_FAIL);
	m_iCurCnt++;
	//29
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"ZombieDie",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Monster/Zombie/Die/%d.png", 3),
		E_FAIL);
	m_iCurCnt++;
	//30
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"ZombieIdle",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Monster/Zombie/Idle/%d.png", 3),
		E_FAIL);
	m_iCurCnt++;
	//31
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"ZombieMove",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Monster/Zombie/Move/%d.png", 8),
		E_FAIL);
	m_iCurCnt++;
	//32
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Wall",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/Install/Wall/Barricade.png"),
		E_FAIL);
	m_iCurCnt++;
	//33
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"MachineGun",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/Install/Turret/0.png"),
		E_FAIL);
	m_iCurCnt++;
	//34
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Rifle",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Weapon/Rifle/%d.png", 3),
		E_FAIL);
	m_iCurCnt++;
	//35
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Numbers",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Font/Numbers/%d.png", 10),
		E_FAIL);
	m_iCurCnt++;
	//36
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Making",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Font/Making/0.png"),
		E_FAIL);
	m_iCurCnt++;
	//37
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"CannotMake",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Font/CannotMake/0.png"),
		E_FAIL);
	m_iCurCnt++;

	//38
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"TurretIdle",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Objects/Turret/Idle/%d.png", 8),
		E_FAIL);
	m_iCurCnt++;
	//39
    FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
	RESOURCE_STAGE,
		L"TurretUp",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Objects/Turret/Up/Fire%d.png", 4),
		E_FAIL);
		m_iCurCnt++;

	//40
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"TurretRightUp",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Objects/Turret/RightUp/Fire%d.png", 4),
		E_FAIL);
	m_iCurCnt++;
	//41
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"TurretRight",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Objects/Turret/Right/Fire%d.png", 4),
		E_FAIL);
	m_iCurCnt++;
	//42
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"TurretRightDown",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Objects/Turret/RightDown/Fire%d.png", 4),
		E_FAIL);
	m_iCurCnt++;
	//43
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"TurretDown",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Objects/Turret/Down/Fire%d.png", 4),
		E_FAIL);
	m_iCurCnt++;
	//44
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"TurretLeftDown",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Objects/Turret/LeftDown/Fire%d.png", 4),
		E_FAIL);
	m_iCurCnt++;
	//45
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"TurretLeft",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Objects/Turret/Left/Fire%d.png", 4),
		E_FAIL);
	m_iCurCnt++;
	//46
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"TurretLeftUp",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Objects/Turret/LeftUp/Fire%d.png", 4),
		E_FAIL);
	m_iCurCnt++;
	//47
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"ZombieFace",
		Engine::TEX_CUBE,
		L"../Bin/Texture/Monster/BossZombie/ZombieHead.dds"),
		E_FAIL);
	m_iCurCnt++;
	//48
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"ZombieBody",
		Engine::TEX_CUBE,
		L"../Bin/Texture/Monster/BossZombie/ZombieBody.dds"),
		E_FAIL);
	m_iCurCnt++;
	//49
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"ZombieArm",
		Engine::TEX_CUBE,
		L"../Bin/Texture/Monster/BossZombie/ZombieArm.dds"),
		E_FAIL);
	m_iCurCnt++;
	//50
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"ShotGun",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Weapon/Shotgun/%d.png", 16),
		E_FAIL);
	m_iCurCnt++;
	//51
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"ChainSaw",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Weapon/ChainSaw/%d.png", 2),
		E_FAIL);
	m_iCurCnt++;
	//52
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Fragment",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Effect/Fragment.png"),
		E_FAIL);
	m_iCurCnt++;

	//53
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Vomit",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Effect/vomit.png"),
		E_FAIL);
	m_iCurCnt++;
	
	//54
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"Hit",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/UI/Hit/0.png"
		),
		E_FAIL);
	m_iCurCnt++;

	//55
	FAILED_CHECK_RETURN(DLL::pResourceMgr->Initialize_Texture(
		RESOURCE_STAGE,
		L"FireWork",
		Engine::TEX_NORMAL,
		L"../Bin/Texture/Effect/FireWork.png"),
		E_FAIL);
	m_iCurCnt++;
	DLL::pSoundMgr->Initialize();
	m_iCurCnt++;

	m_bFinish = true;

	return 0;
}

CLoading* CLoading::Create(LOADINGID eLoading)
{
	CLoading*	pInstance = new CLoading;

	if (FAILED(pInstance->Ready_Loading(eLoading)))
		Safe_Release(pInstance);

	return pInstance;

}

void CLoading::freeMem(void)
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);
}

