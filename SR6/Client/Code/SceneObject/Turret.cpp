#include "stdafx.h"
#include "Turret.h"
#include <iostream>
CTurret::CTurret()
	: CPickableObject()
{
}

CTurret::CTurret(const CTurret & rhs)
	: CPickableObject(rhs)
{
}

Engine::_int CTurret::Update_GameObject(const Engine::_float & fTimeDelta)
{
	CPickableObject::Update_GameObject(fTimeDelta);

	if(m_CurState != DIR_IDLE)
		m_fCurFrame += fTimeDelta * m_fMaxFrame / 0.2f;
	else
		m_fCurFrame += fTimeDelta * m_fMaxFrame;

	if (m_fCurFrame >= m_fMaxFrame)
	{
		m_fCurFrame = 0.f;
	}

	m_fSearchTime += fTimeDelta;

	list<CGameObject*> nearList;
	m_pTarget = DLL::pSearchMgr->Find_NearObj(this, &nearList, m_fAttackDistance);

	if (m_pTarget != nullptr)
	{
		CTransform* transform  = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
		CTransform* targetTransform = m_pTarget->Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC);
		_vec3 vMyPos = *transform->Get_Info(INFO_POS);
		_vec3 vLength = vMyPos - *targetTransform->Get_Info(INFO_POS);

		if (D3DXVec3Length(&vLength) > m_fAttackDistance)
		{
			m_pTarget = nullptr;
			m_fSearchTime = 1;
		}
		
		_vec3 look = _vec3(0, 0, 1);
		CTransform* playerTransform = DLL::pSearchMgr->Get_Object(L"Player")->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
		if (playerTransform->Get_Info(INFO_POS)->z > transform->Get_Info(INFO_POS)->z)
			look = _vec3(0, 0, -1);
		_vec3 dir = *targetTransform->Get_Info(INFO_POS) - *transform->Get_Info(INFO_POS);
		D3DXVec3Normalize(&dir, &dir);

		_float angle = D3DXVec3Dot(&look, &dir);
		angle = acos(angle);
		angle = D3DXToDegree(angle);

		angle = dir.x < 0 ? 360 - angle : angle;
		
		int state = angle / 45;
		if (state >= DIR_END-1)
			state = DIR_END-1;
		SetState((ATTACK_DIR)state);
		m_fAttackTime += fTimeDelta;
		if (m_fAttackTime > 0.3f)
		{
			DLL::pSoundMgr->PlaySound(L"Turret.mp3", CSoundMgr::CHANNEL_ID::EFFECT);
			DLL::pSoundMgr->SetVolume(CSoundMgr::CHANNEL_ID::EFFECT, 0.2f);
 			m_pTarget->Take_Damage(3);
			m_fAttackTime = 0;
		}
	}
	else
	{
		SetState(DIR_IDLE);
	}

	return Engine::_int();
}

void CTurret::Render_GameObject()
{
	CTransform* transform = Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC);
	

	CTransform* playerTransform = DLL::pSearchMgr->Get_Object(L"Player")->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);

	if (playerTransform->Get_Info(INFO_POS)->z > transform->Get_Info(INFO_POS)->z)
	{
		_vec3 v = *transform->Get_Scale();
		transform->Set_Scale(&_vec3(v.x, v.y, -1));
	}
	else
	{
		_vec3 v = *transform->Get_Scale();
		transform->Set_Scale(&_vec3(v.x, v.y, 1));
	}

	if (!m_bIsPicked)
	{
		transform->Set_Scale(6, 6, 1);
	}
	else
	{
		transform->Set_Scale(1, 1, 1);
	}
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_WORLD, &(*Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC)->Get_World()));
	m_pCurTexture->Render_Texture(m_fCurFrame);

	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

HRESULT CTurret::Initialize_GameObject()
{
	CPickableObject::Initialize_GameObject();
	CComponent* pComponent = nullptr;

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	dynamic_cast<CTransform*>(pComponent)->Set_Scale(&_vec3(6, 6, 1));



	m_pTexture[0] = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"TurretUp"));
	m_pTexture[1] = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"TurretRightUp"));
	m_pTexture[2] = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"TurretRight"));
	m_pTexture[3] = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"TurretRightDown"));
	m_pTexture[4] = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"TurretDown"));
	m_pTexture[5] = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"TurretLeftDown"));
	m_pTexture[6] = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"TurretLeft"));
	m_pTexture[7] = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"TurretLeftUp"));
	m_pTexture[8] = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"TurretIdle"));

	for(int i=0;i<8;i++)
		m_iStatusAction[i] = 4;
	m_iStatusAction[8] = 8;

	pComponent = CSphere::Create(0.6f);
	pComponent->Attach(this, ID_DYNAMIC);

	m_fAttackDistance = 20.f;

	SetState(DIR_IDLE);
	return S_OK;
}

HRESULT CTurret::Late_Initialize()
{
	return S_OK;
}

bool CTurret::IsPicked()
{
	return false;
}

CGameObject * CTurret::Clone(const Engine::_vec3 * pPos)
{
	CTurret*	pInstance = new CTurret(*this);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	_tchar wName[MAX_STR]{};

	wsprintf(wName, L"%s%d", Get_Name(), m_iCloneNum++);

	pInstance->SetName(wName);

	if (nullptr != pPos)
	{
		pInstance->Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC)->Set_Pos(pPos->x, pPos->y, pPos->z);
	}
	DLL::pColMgr->Add_Obj(pInstance);
	return pInstance;
}

CTurret * CTurret::Create()
{
	CTurret*	pInstance = new CTurret;
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTurret::freeMem()
{
	CPickableObject::freeMem();
}

void CTurret::SetState(ATTACK_DIR dir)
{
	if (m_CurState == dir)
		return;
	m_CurState = dir;
	m_pCurTexture = m_pTexture[static_cast<int>(dir)];
	m_fMaxFrame = m_iStatusAction[static_cast<int>(dir)];
	m_fCurFrame = 0.f;
}
