#include "stdafx.h"
#include "ShotGun.h"

#include "SceneObject/Bullet.h"
#include "Effect/BloodParticle.h"
#include "Effect/GunParticle.h"
#include "SceneObject/PickableObject.h"

USING(Engine)

CShotGun::CShotGun(void)
	: CWeaponBase()
{
	SetName(L"ShotGun");
}

CShotGun::CShotGun(const CShotGun& rhs)
	: CWeaponBase(rhs)
{
	SetName(L"ShotGun");
}

CShotGun::~CShotGun(void)
{
}

HRESULT CShotGun::Late_Initialize()
{
	m_pTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, Get_Name()));

	return S_OK;
}

HRESULT CShotGun::Initialize_GameObject()
{
	CComponent*	pComponent = nullptr;

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	m_vSidePos = { 0.3f, 0.f, 0.f };

	m_fDamage = 100.f;

	Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Set_Scale(&_vec3(3.f, 3.f, 1.f));


	return S_OK;
}

Engine::_int CShotGun::Update_GameObject(const Engine::_float & fTimeDelta)
{
	m_fCurTime += fTimeDelta;
	if (m_bAttack)
	{
		m_fAttAction += m_fMaxAction * fTimeDelta;
		if (static_cast<_int>(m_fAttAction) == 3)
		{
			float fDist;
			CPickableObject* obj = DLL::pPickMgr->GetPickedObject(fTimeDelta, 10.f, &fDist);
			if (obj != nullptr && obj->Get_Type() == OBJ_MONSTER)
			{
				obj->Take_Damage(m_fDamage);
			}
			DLL::pCameraMgr->Rebound_Camera();
		}
		if (m_fAttAction >= m_fMaxAction)
		{
			m_fAttAction = 0.f;
			m_bAttack = false;
		}
	}
	CTransform* pTransform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	CTransform* pPlayerTransform = m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);

	_vec3 vSide = *pPlayerTransform->Get_Info(INFO_POS) + m_vSidePos;
	pTransform->Set_Pos(vSide.x, vSide.y, vSide.z);
	pTransform->Set_Look(pPlayerTransform->Get_Info(INFO_LOOK));

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	if (DLL::pCameraMgr->Get_CurCamera() == FIRST_PERSON_VIEW)
	{
		DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);
	}
	return iExit;
}

void CShotGun::Attack(const Engine::_float& fTimeDelta)
{
	if (m_fCurTime >= m_fShotCool)
	{
		DLL::pSoundMgr->PlaySound(L"ShotGun.mp3", CSoundMgr::CHANNEL_ID::PLAYER);

		m_bAttack = true;
		m_fCurTime = 0.f;
		
		m_fCurTime = 0.f;
	}
}

void CShotGun::LoadData(HANDLE hFile)
{
}

void CShotGun::Render_GameObject()
{
	auto pGraphic = DLL::pGraphicDev->GetDevice();

	_matrix matTrans, matScale, matRot;

	_matrix matWorld = *D3DXMatrixScaling(&matScale, 600.f, 600.f, 1.f) * *D3DXMatrixTranslation(&matTrans, 0.f, 0.f, 0.f);

	pGraphic->SetTransform(D3DTS_WORLD, &matWorld);

	m_pTexture->Render_Texture(static_cast<_int>(m_fAttAction));
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

CShotGun* CShotGun::Create(void)
{
	CShotGun*	pInstance = new CShotGun;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

Engine::CGameObject* CShotGun::Clone(const Engine::_vec3* pPos)
{
	CShotGun*	pInstance = new CShotGun(*this);

	return pInstance;
}