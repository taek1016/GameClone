#include "stdafx.h"
#include "ChainSaw.h"

USING(Engine)

CChainSaw::CChainSaw(void)
	: CWeaponBase()
{
	SetName(L"ChainSaw");
}

CChainSaw::CChainSaw(const CChainSaw& rhs)
	: CWeaponBase(rhs)
{
	SetName(L"ChainSaw");
}

CChainSaw::~CChainSaw(void)
{
}

HRESULT CChainSaw::Late_Initialize()
{
	m_pTransform = Get_Component<Engine::CTransform>(TRANSFORM, ID_DYNAMIC);

	m_pTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"ChainSaw"));

	CComponent* pComponent = CSphere::Create(6.f);
	pComponent->Attach(this, ID_DYNAMIC);
	m_pCollider = Get_Component<CCollider>(COLLIDER, ID_DYNAMIC);
	m_pCollider->Set_Transform(m_pTransform);

	return S_OK;
}

HRESULT CChainSaw::Initialize_GameObject()
{
	CComponent*	pComponent = nullptr;

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	m_fDamage = 8.f;
	m_vSidePos = { 0.3f, 0.f, 0.f };

	Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Set_Scale(&_vec3(3.f, 3.f, 1.f));

	return S_OK;
}

Engine::_int CChainSaw::Update_GameObject(const _float& fTimeDelta)
{
	m_fCurTime += fTimeDelta;
	if (m_bAttack)
	{
		m_fAttAction += m_fMaxAction * fTimeDelta * 5.f;
		if (m_fAttAction >= m_fMaxAction)
		{
			m_fAttAction = 0.f;
			m_bAttack = false;
		}
	}

	DLL::pSoundMgr->PlaySound(L"ChainSawIdle.mp3", CSoundMgr::CHANNEL_ID::PLAYER);
	CTransform* pTransform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	CTransform* pPlayerTransform = m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);

	_vec3 vSide = *pPlayerTransform->Get_Info(INFO_POS) + m_vSidePos;
	pTransform->Set_Pos(vSide.x, vSide.y, vSide.z);
	pTransform->Set_Look(pPlayerTransform->Get_Info(INFO_LOOK));

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return iExit;
}

void CChainSaw::Attack(const _float& fTimeDelta)
{
	if (m_fCurTime >= m_fAttackCool)
	{
		DLL::pSoundMgr->PlaySound(L"ChainSawAttack.mp3", CSoundMgr::CHANNEL_ID::PLAYER);
		DLL::pSoundMgr->SetVolume(CSoundMgr::CHANNEL_ID::PLAYER, 0.5f);
		m_fCurTime = 0.f;
		m_bAttack = true;
		DLL::pColMgr->Collide_Melee_Attack(this, 1.f);
	}
}

void CChainSaw::Render_GameObject()
{
	_matrix matTrans, matScale, matRot;

	_matrix matWorld = *D3DXMatrixScaling(&matScale, 400.f, 400.f, 1.f) * *D3DXMatrixTranslation(&matTrans, 50.f, -100.f, 0.f);

	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);

	m_pTexture->Render_Texture(static_cast<_int>(m_fAttAction));
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

CChainSaw * CChainSaw::Create(void)
{
	CChainSaw*	pInstance = new CChainSaw;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

Engine::CGameObject* CChainSaw::Clone(const _vec3* pPos)
{
	return new CChainSaw(*this);
}

void CChainSaw::LoadData(HANDLE hFile)
{
}

