#include "stdafx.h"
#include <iostream>
#include "BossZombie.h"
#include "Component/Body.h"
#include "Effect/Fragment.h"
#include "Effect/BloodParticle.h"
#include "Component/BossController.h"

CBossZombie::CBossZombie()
	:CMonster()
{
}

CBossZombie::CBossZombie(const CBossZombie & rhs)
	: CMonster(rhs)
{
}

Engine::_int CBossZombie::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (m_iHP <= 0)
	{
		DLL::pPickMgr->Delete_Object(Get_Name());
		return DEAD_OBJ;
	}
	cout << m_iHP << endl;
	CInGameObject::Update_GameObject(fTimeDelta);
	CBody* body = Get_Component<CBody>(BODY, ID_DYNAMIC);
	body->PlayAnimation(L"Move");

	CBossController* controller = Get_Component<CBossController>(CONTROLLER, ID_DYNAMIC);

	m_fJumpTime += fTimeDelta;
	
	if (m_fJumpTime > m_fJumpDelay)
	{
		m_fJumpTime = 0;
		controller->Jump();
	}

	m_matBill = *Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_World();
	return Engine::_int();
}

void CBossZombie::Render_GameObject()
{
	CMonster::Render_GameObject();
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_WORLD, Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC)->Get_World());
}

HRESULT CBossZombie::Initialize_GameObject()
{
	CInGameObject::Initialize_GameObject();
	m_vecVertices.push_back(_vec3(-1.f, 2.6f, 0.f));
	m_vecVertices.push_back(_vec3(1.f, 2.6f, 0.f));
	m_vecVertices.push_back(_vec3(1.f, 0.f, 0.f));
	m_vecVertices.push_back(_vec3(-1.f, 0.f, 0.f));



	Engine::CComponent*	pComponent = nullptr;

	pComponent = CBossController::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	pComponent = CRigidBody::Create();
	pComponent->Attach(this, ID_STATIC);

	m_fJumpDelay = 15;
	m_iHP = 2500;
	m_fDamage = 5;
	return S_OK;
}

void CBossZombie::Take_Damage(const _float & fDamage)
{
	m_iHP -= static_cast<_int>(fDamage);
	printf("%d\n", m_iHP);

	CBloodParticle* particle = dynamic_cast<CBloodParticle*>(DLL::pPoolMgr->Get_Pool<CBloodParticle>(POOL_PARTICLE));
	DLL::pObjMgr->Add_GameObject(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_PARTICLE, particle);
	CTransform* transform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	particle->SetEmitPoint(*transform->Get_Info(INFO_POS));
	particle->Reset_AllParticles();
}

CBossZombie * CBossZombie::Create()
{
	CBossZombie* pInstance = new CBossZombie;
	pInstance->SetName(L"BossZombie");
	return pInstance;
}

CBossZombie * CBossZombie::Clone(const Engine::_vec3 * pPos)
{
	CBossZombie* pInstance = new CBossZombie(*this);

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

void CBossZombie::LoadData(HANDLE hFile)
{
	DWORD dwBytes = 0;
	int size;
	_tchar str[255];
	ZeroMemory(str, 255);
	m_bIsChild = false;
	ReadFile(hFile, &m_bIsChild, sizeof(m_bIsChild), &dwBytes, nullptr);
	int a;
	ReadFile(hFile, &a, 4, &dwBytes, nullptr);

	ReadFile(hFile, &size, sizeof(size), &dwBytes, nullptr);
	ReadFile(hFile, str, 255, &dwBytes, nullptr);

	if(!m_bIsChild)
		SetName(L"BossZombie");

	COMPONENT_TYPE	type;
	CComponent*		component;

	for (int i = 0; i < 2; i++)
	{
		ReadFile(hFile, &size, sizeof(size), &dwBytes, nullptr);
		for (int j = 0; j < size; j++)
		{
			ReadFile(hFile, &type, sizeof(type), &dwBytes, nullptr);
			component = CComponentMgr::GetInstance()->CreateComponent(this, type);
			component->LoadData(hFile);
			component->SetGameObject(this);
			if (type == TRANSFORM)
			{
				//dynamic_cast<CTransform*>(component)->m_
			}
			m_vecComponent[i][type] = component;
		}
	}

	ReadFile(hFile, &size, sizeof(size), &dwBytes, nullptr);

	for (int i = 0; i < size; i++)
	{
		CInGameObject* obj = CInGameObject::Create();
		obj->LoadData(hFile);
		CTransform* transform = obj->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
		transform->SetParent(Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC));
		CComponent* pComponent = nullptr;

		switch (i)
		{
		case 0:
			pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"ZombieArm");
			break;
		case 1:
			pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"ZombieBody");
			break;
		case 2:
			pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"ZombieFace");
			break;
		case 3:
			pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"ZombieArm");
			break;
		case 4:
			pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"ZombieArm");
			break;
		case 5:
			pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"ZombieArm");
			break;
		}

		pComponent->Attach(obj, ID_STATIC);


		m_vecChildObject.push_back(obj);

		
	}
	CAnimator* animator = Get_Component<CAnimator>(ANIMATOR, ID_DYNAMIC);
	animator->SetAnimTransform();
}
