#include "stdafx.h"
#include "Player.h"

#include "Component/PlayerController.h"
#include "Item/Rifle.h"
#include "ComponentMgr.h"

#include "Effect/FireWork.h"

#include "SceneObject/PickableObject.h"
#include <iostream>

USING(Engine)

CPlayer::CPlayer(void)
	: CInGameObject()
	, m_iHp(1000)
	, m_iMaxHp(1000)
{
	SetName(L"Player");
}

CPlayer::CPlayer(const CPlayer & rhs)
	: CInGameObject(rhs)
	, m_iHp(rhs.m_iHp)
	, m_iMaxHp(rhs.m_iMaxHp)
{
	SetName(L"Player");
}

CPlayer::~CPlayer(void)
{
}

HRESULT CPlayer::Late_Initialize(void)
{
	for (_int i = 0; i < ID_END; ++i)
	{
		for (auto iter : m_vecComponent[i])
		{
			if (nullptr == iter)
			{
				continue;
			}

			if (FAILED(iter->Late_Initialize()))
			{
				return E_FAIL;
			}
		}
	}
	Take_Damage(0.f);
	return S_OK;
}

HRESULT CPlayer::Initialize_GameObject(void)
{
	FAILED_CHECK_RETURN(Create_Component(), E_FAIL);



	return S_OK;
}

Engine::_int CPlayer::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (0 >= m_iHp)
	{
		//DLL::pCameraMgr->Set_CurCamera(CAMERA_ENUM::DYNAMIC_CAMERA);
	}
	_int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);
	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);
	for (auto ele : m_vecChildObject)
	{
		ele->Update_GameObject(fTimeDelta);
		DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, ele);
	}

	DLL::pCameraMgr->Update_Camera(fTimeDelta);

	if (m_pPickedObj)
	{
		CTransform* transform = m_pPickedObj->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
		CTransform* myTransform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
		_vec3 vPos = *myTransform->Get_Info(INFO_POS);
		_vec3 vLook = *myTransform->Get_Info(INFO_LOOK);
	}

	if (DLL::pDirectInput->KeyDown(DIK_Z))
	{
		_vec3 pos;
		pos.x = rand() % 100;
		pos.z = rand() % 100;
		pos.y = 100;

		DLL::pSoundMgr->PlaySound(L"FireWork.mp3", CSoundMgr::CHANNEL_ID::MONSTER);

		CFireWork* particle = dynamic_cast<CFireWork*>(DLL::pPoolMgr->Get_Pool<CFireWork>(POOL_FIREWORK));
		DLL::pObjMgr->Add_GameObject(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_PARTICLE, particle);
		CTransform* transform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
		particle->SetBombPoint(*transform->Get_Info(INFO_POS) + pos);
		particle->Reset_AllParticles();
	}

	if (m_pPickedObj == nullptr)
	{
		_float fDist = 0.f;
		CPickableObject* obj = DLL::pPickMgr->GetPickedObject(fTimeDelta, 2.f, &fDist);
		if (obj != nullptr)
		{
			if (DLL::pDirectInput->KeyDown(DIK_T))
			{
				obj->PickUp(this);
				m_pPickedObj = obj;
			}
		}
	}
	else
	{
		if (DLL::pDirectInput->KeyDown(DIK_T))
		{
			m_pPickedObj->Drop();
			m_pPickedObj = nullptr;
		}
	}

	//DLL::pColMgr->Collide_Push_Obj(this, 2.f);
#ifdef _DEBUG
	static _float fDelta = 0.f;
	fDelta += fTimeDelta;
	if (fDelta >= 1.f)
	{
		fDelta = 0.f;
		_vec3 vPos = *Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_Info(INFO_POS);
		printf("%f %f %f\n", vPos.x, vPos.y, vPos.z);
	}
#endif // _DEBUG

	return iExit;
}

void CPlayer::Render_GameObject(void)
{
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_WORLD, Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC)->Get_World());

	int i = 0;
	for (auto& ele : m_vecChildObject)
	{
		//tex->Render_Texture(i++);
		ele->Render_GameObject();
	}
}

void CPlayer::Attack(const _float& fTimeDelta)
{
	m_pWeapon->Attack(fTimeDelta);
}

void CPlayer::Take_Damage(const _float & fDamage)
{
	m_iHp -= static_cast<_int>(fDamage);
	_float fData = m_iHp / static_cast<_float>(m_iMaxHp);
	DLL::pUiMgr->Set_Data(L"HPBar", fData);
	DLL::pUiMgr->Activate_HitBox();
}

void CPlayer::Set_PickableObj(CPickableObject * pObj)
{
	CTransform* pPlayerTransform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	_vec3 vLook = *pPlayerTransform->Get_Info(INFO_LOOK);
	_vec3 vPlayerPos = *pPlayerTransform->Get_Info(INFO_POS);
	D3DXVec3Normalize(&vLook, &vLook);

	pObj->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Set_Pos(&(vLook * 5.f + vPlayerPos));
	DLL::pPickMgr->Add_Object(pObj);
	DLL::pColMgr->Add_Obj(pObj);
	DLL::pObjMgr->Add_GameObject(STAGE_DEFAULT, STAGE_OBJ::STAGE_OBJECTS, pObj);
}

CPlayer* CPlayer::Create(void)
{
	CPlayer* pInstance = new CPlayer;

	return pInstance;
}

void CPlayer::AirBorne()
{
	CPlayerController* controller = Get_Component<CPlayerController>(CONTROLLER, ID_DYNAMIC);
	controller->AirBorne();
}

inline CInGameObject* CPlayer::Clone(const Engine::_vec3 * pPos)
{
	CPlayer* pInstance = new CPlayer(*this);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	if (nullptr != pPos)
	{
		pInstance->Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC)->Set_Pos(pPos);
	}

	return pInstance;
}

inline void CPlayer::freeMem()
{
	CInGameObject::freeMem();
}

void CPlayer::LoadData(HANDLE hFile)
{
	CInGameObject::LoadData(hFile);
}

HRESULT CPlayer::Create_Component(void)
{
	Engine::CComponent*	pComponent = nullptr;
	pComponent = CPlayerController::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	pComponent = CRigidBody::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	pComponent = CSphere::Create(3.f);
	pComponent->Attach(this, ID_DYNAMIC);

	return S_OK;
}