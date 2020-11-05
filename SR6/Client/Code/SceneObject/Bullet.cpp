#include "stdafx.h"
#include "Bullet.h"

USING(Engine)

CBullet::CBullet(void)
	: CGameObject()
{
	SetName(L"Bullet");
}

CBullet::CBullet(const CBullet & rhs)
	: CGameObject(rhs)
	, m_fSpeed(rhs.m_fSpeed)
	, m_fDieTime(rhs.m_fDieTime)
	, m_fLifeTime(0.f)
{
}

CBullet::~CBullet(void)
{
}

HRESULT CBullet::Initialize_GameObject()
{
	CComponent* pComponent = nullptr;

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	pComponent = DLL::pResourceMgr->Clone(STAGE_DEFAULT, L"Buffer_TriCol");
	pComponent->Attach(this, ID_DYNAMIC);

	pComponent = CSphere::Create(0.3f);
	pComponent->Attach(this, ID_DYNAMIC);

	return S_OK;
}

HRESULT CBullet::Late_Initialize()
{
	m_pCollider = Get_Component<CCollider>(COLLIDER, ID_DYNAMIC);
	m_pTransform = Get_Component<Engine::CTransform>(TRANSFORM, ID_DYNAMIC);
	Get_Component<CCollider>(COLLIDER, ID_DYNAMIC)->Set_Transform(m_pTransform);

	return S_OK;
}

Engine::_int CBullet::Update_GameObject(const _float& fTimeDelta)
{
	m_fLifeTime += fTimeDelta;
	if (m_fLifeTime >= m_fDieTime)
	{
		Set_Dead();
	}

	_vec3 vDir = *D3DXVec3Normalize(&m_vLook, &m_vLook) * m_fSpeed * fTimeDelta;

	m_pTransform->Move_Pos(&vDir);

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	DLL::pColMgr->Collide_Range_Attack(this, 3.f);

	if (m_bDead)
	{
		m_fLifeTime = 0.f;
		m_bDead = false;

		DLL::pPoolMgr->Back_Pool(POOL_BULLET, this);
		return BACK_POOL;
	}

	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBullet::Render_GameObject()
{
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_WORLD, Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC)->Get_World());

	DLL::pResourceMgr->Render_Texture(RESOURCE_STAGE, L"Bullet");
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

void CBullet::Set_Info(const Engine::_vec3 * pPos, const Engine::_vec3* pLook, const _float fSpeed, const Engine::_float fDamage)
{
	Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Set_Pos(pPos->x, pPos->y, pPos->z);
	m_vLook = *pLook;
	m_fSpeed = fSpeed;
	m_fDamage = fDamage;
}

CBullet * CBullet::Create(void)
{
	CBullet*	pInstance = new CBullet();

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBullet::Clone(const _vec3 * pPos)
{
	CBullet*	pInstance = new CBullet(*this);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBullet::LoadData(HANDLE hFile)
{
}
