#include "stdafx.h"
#include "Stage.h"

#include "Component/StaticCamera.h"
#include "Component/PersonCamera.h"
#include "Component/FieldMouse.h"

#include "InGameObject.h"

#include "UI/HpBar.h"

#include "SkyBox.h"

#include "Item/Inventory.h"
#include "SceneObject/Barricade.h"
#include "SceneObject/Turret.h"

#include "Event/SingleEvent.h"

USING(Engine)

CStage::CStage(void)
	: CScene()
{
	DLL::pSoundMgr->StopAll();
	DLL::pSoundMgr->PlayBGM(L"InGameBGM.mp3");
}

CStage::~CStage(void)
{
}

HRESULT CStage::Initialize_Scene(void)
{/*
	DLL::pObjContainer->Add_Obj<CTerrain>(L"Terrain");
	DLL::pObjContainer->Add_Obj<CZombie>(L"Zombie");
	DLL::pObjContainer->Add_Obj<CWolf>(L"Wolf");
	DLL::pObjContainer->Add_Obj<CIron>(L"Iron");
	DLL::pObjContainer->Add_Obj<CTree>(L"Tree");*/

	DLL::pUiMgr->Initialize_UI();
	DLL::pCraftingMgr->Initialize_Crafting();
	DLL::pObjContainer->Initialize_Managers(STAGE_MAP::STAGE_END, STAGE_OBJ::STAGE_OBJ_END);
	
	DLL::pUiMgr->Register_UI(L"HPBar", CHpBar::Create());

	DLL::pObjContainer->Clone(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_TERRAIN, L"Terrain");
	CGameObject *pPlayer = DLL::pObjContainer->Clone(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_PLAYER, L"Player");

	if (NULL != pPlayer)
	{
		_vec3 vUp = { 0.f, 1.f, 0.f };
		_vec3 vEye = { 0.f, 6.f, -6.f };

		DLL::pCameraMgr->Add_Camera<CPersonCamera>(FIRST_PERSON_VIEW, D3DXToRadian(90.f), WINCX / static_cast<_float>(WINCY), 1.f, 1000.f, 10.f);
		DLL::pCameraMgr->Add_Camera<CStaticCamera>(STATIC_CAMERA, D3DXToRadian(90.f), WINCX / static_cast<_float>(WINCY), 1.f, 1000.f, 10.f);

		DLL::pCameraMgr->Set_Object(pPlayer);
		DLL::pCameraMgr->Late_Initialize(&vEye,
			pPlayer->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_Info(INFO_POS),
			&vUp);

		DLL::pMouseMgr->Add_Mouse<CFieldMouse>(FIELD_MOUSE);
		DLL::pMouseMgr->Late_Initialize();

		DLL::pCameraMgr->Set_CurCamera(FIRST_PERSON_VIEW);
	}

	pPlayer->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Set_Pos(&_vec3(18.f, 1.f, 83.f));

	DLL::pObjContainer->Clone(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_OBJECTS, L"Iron", &_vec3(26.f, 1.f, 80.f));
	DLL::pObjContainer->Clone(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_OBJECTS, L"Iron", &_vec3(25.f, 1.f, 81.f));
	DLL::pObjContainer->Clone(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_OBJECTS, L"Iron", &_vec3(23.f, 1.f, 82.f));

	DLL::pObjContainer->Clone(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_OBJECTS, L"Tree", &_vec3(17.f, 1.f, 90.f));
	DLL::pObjContainer->Clone(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_OBJECTS, L"Tree", &_vec3(28.f, 1.f, 95.f));
	DLL::pObjContainer->Clone(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_OBJECTS, L"Tree", &_vec3(23.f, 1.f, 93.f));

	_float fX, fY, fZ;
	_vec3 vPos;
	for (_int i = 0; i < 20; ++i)
	{
		fX = static_cast<_float>(rand() % 40 + 15);
		fY = static_cast<_float>(1);
		fZ = static_cast<_float>(rand() % 25 + 120);

		vPos = _vec3(fX, fY, fZ);
		
		auto pObj = DLL::pObjContainer->Clone(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_MONSTER, L"Zombie", &vPos);

		DLL::pPickMgr->Add_Object(dynamic_cast<CPickableObject*>(pObj));
	}
	DLL::pObjMgr->Add_GameObject(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_OBJECTS, CSkyBox::Create());

	auto pGraphic = DLL::pGraphicDev->GetDevice();
	pGraphic->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pGraphic->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	DLL::pInventory->Initialize_Inventory();

	CCrafting* pCraft = CCrafting::Create();
	pCraft->Setup_Craft(CBarricade::Create(), 1, 1);
	DLL::pCraftingMgr->Register_Crafting(L"Barricade", pCraft);

	pCraft = CCrafting::Create();
	pCraft->Setup_Craft(CTurret::Create(), 1, 1);
	DLL::pCraftingMgr->Register_Crafting(L"Turret", pCraft);

	DLL::pEventMgr->Register_Event(L"ZombieRun", CSingleEvent::Create());

	return S_OK;
}

_int CStage::Update_Scene(const _float & fTimeDelta)
{
	DLL::pEventMgr->Update_Event(fTimeDelta);

	_int iExit = DLL::pObjMgr->Update_Objects(fTimeDelta);

	DLL::pMouseMgr->Update_Mouse(fTimeDelta);
	DLL::pUiMgr->Update_Ui(fTimeDelta);
	DLL::pInventory->Update_Inventory(fTimeDelta);
	DLL::pCraftingMgr->Update_Crafting(fTimeDelta);

	return iExit;
}

void CStage::Render_Scene(void)
{
	//obj->Render_GameObject();
}

CStage * CStage::Create(void)
{
	CStage* pInstance = new CStage;

	if (FAILED(pInstance->Initialize_Scene()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CStage::freeMem(void)
{
}
