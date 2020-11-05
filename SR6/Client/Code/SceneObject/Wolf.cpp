#include "stdafx.h"
#include "Wolf.h"

USING(Engine)

CWolf::CWolf(void)
	: CMonster()
{
	SetName(L"Zombie");
}

CWolf::CWolf(const CWolf & rhs)
	: CMonster(rhs)
{
}

CWolf::~CWolf(void)
{
}

HRESULT CWolf::Late_Initialize(void)
{
	
	return S_OK;
}

HRESULT CWolf::Initialize_GameObject(void)
{
	Engine::CComponent*	pComponent = nullptr;

	pComponent = DLL::pResourceMgr->Clone(RESOURCE_STATIC, L"Buffer_CubeTex");
	pComponent->Attach(this, ID_DYNAMIC);

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	return S_OK;
}

void CWolf::Render_GameObject(void)
{
	CTransform* pTransform = Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC);
	LPDIRECT3DDEVICE9 pDevice = DLL::pGraphicDev->GetDevice();

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	pDevice->SetTransform(D3DTS_WORLD, pTransform->Get_World());

	Get_Component<CVIBuffer>(COMPONENT_TYPE::BUFFER, ID_DYNAMIC)->Render_Buffer();
}

void CWolf::LoadData(HANDLE hFile)
{
}

CWolf * CWolf::Create(void)
{
	CWolf*	pInstance = new CWolf();

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	//pInstance->LoadData(INVALID_HANDLE_VALUE);

	return pInstance;
}

CGameObject * CWolf::Clone(const Engine::_vec3 * pPos)
{
	CWolf*	pInstance = new CWolf(*this);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (nullptr != pPos)
	{
		pInstance->Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC)->Set_Pos(pPos->x, pPos->y, pPos->z);
	}

	return pInstance;
}
