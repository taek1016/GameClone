#include "stdafx.h"
#include "Rifle.h"

#include "SceneObject/Bullet.h"
#include "Effect/BloodParticle.h"
#include "Effect/GunParticle.h"
#include "SceneObject/PickableObject.h"

USING(Engine)

CRifle::CRifle(void)
	: CWeaponBase()
{
	SetName(L"Rifle");
}

CRifle::CRifle(const CRifle& rhs)
	: CWeaponBase(rhs)
{
	SetName(L"Rifle");
}

CRifle::~CRifle(void)
{
}

HRESULT CRifle::Late_Initialize()
{
	m_pTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, Get_Name()));

	return S_OK;
}

HRESULT CRifle::Initialize_GameObject()
{
	CComponent*	pComponent = nullptr;

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	m_vSidePos = { 0.3f, 0.f, 0.f };

	m_fDamage = 5.f;

	Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Set_Scale(&_vec3(3.f, 3.f, 1.f));

	return S_OK;
}

Engine::_int CRifle::Update_GameObject(const Engine::_float & fTimeDelta)
{
	m_fCurTime += fTimeDelta;
	if (m_bAttack)
	{
		m_fAttAction += m_fMaxAction * fTimeDelta * 7.f;

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

void CRifle::Attack(const Engine::_float& fTimeDelta)
{
	if (m_fCurTime >= m_fShotCool)
	{
		DLL::pSoundMgr->PlaySound(L"Rifle.wav", CSoundMgr::CHANNEL_ID::PLAYER);
		m_bAttack = true;
		m_fCurTime = 0.f;
		float fDist;
		CPickableObject* obj = DLL::pPickMgr->GetPickedObject(fTimeDelta, 100.f, &fDist);
		if (obj != nullptr && obj->Get_Type() == OBJ_MONSTER)
		{
			obj->Take_Damage(1);
		}
		m_fCurTime = 0.f;
		DLL::pCameraMgr->Shake_Camera(5);
	}
}

void CRifle::LoadData(HANDLE hFile)
{
}

void CRifle::Render_GameObject()
{
	auto pGraphic = DLL::pGraphicDev->GetDevice();

	_matrix matTrans, matScale, matRot;

	_matrix matWorld = *D3DXMatrixScaling(&matScale, 400.f, 400.f, 1.f) * *D3DXMatrixTranslation(&matTrans, 0.f, -100.f, 0.f);

	pGraphic->SetTransform(D3DTS_WORLD, &matWorld);

	m_pTexture->Render_Texture(static_cast<_int>(m_fAttAction));
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

CRifle* CRifle::Create(void)
{
	CRifle*	pInstance = new CRifle;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

Engine::CGameObject* CRifle::Clone(const Engine::_vec3* pPos)
{
	CRifle*	pInstance = new CRifle(*this);

	return pInstance;
}