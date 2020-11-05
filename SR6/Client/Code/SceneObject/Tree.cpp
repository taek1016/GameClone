#include "stdafx.h"
#include "Tree.h"

USING(Engine)

CTree::CTree(void)
	: CGameObject()
{
	SetName(L"Tree");
}

CTree::CTree(const CTree & rhs)
	: CGameObject(rhs)
{
}

CTree::~CTree(void)
{
}

HRESULT CTree::Late_Initialize()
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

	Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Set_Scale(5.f, 5.f, 1.f);

	m_pPlayerCol = DLL::pSearchMgr->Get_Object(L"Player")->Get_Component<CCollider>(COLLIDER, ID_DYNAMIC);
	m_pMyCol = Get_Component<CSphere>(COLLIDER, ID_DYNAMIC);
	return S_OK;
}

HRESULT CTree::Initialize_GameObject()
{
	CComponent*	pComponent = nullptr;

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	pComponent = CSphere::Create(2.f);
	pComponent->Attach(this, ID_DYNAMIC);

	m_iIndex = rand() % 5;	// Iron 이미지 개수가 5

	m_pTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"Tree"));
	m_pTexture->Attach(this, ID_STATIC);

	m_pBuffer = dynamic_cast<CRcTex*>(DLL::pResourceMgr->Clone(RESOURCE_STATIC, L"Buffer_RcTex"));
	m_pBuffer->Attach(this, ID_STATIC);

	return S_OK;
}

Engine::_int CTree::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	if (m_pMyCol->Is_Collide(m_pPlayerCol))
	{
		if (DLL::pDirectInput->KeyPressing(DIK_T))
		{
			m_fGatherTime += fTimeDelta;

			if (m_fGatherTime >= m_fDieTime)
			{
				DLL::pSoundMgr->PlaySound(L"WoodGather.wav", CSoundMgr::CHANNEL_ID::EFFECT);
				DLL::pInventory->Add_Material(MATERIAL_WOOD);
				return DEAD_OBJ;
			}
		}
	}
	else
	{
		m_fGatherTime = 0.f;
	}

	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CTree::Render_GameObject(void)
{
	DLL::pCameraMgr->Make_Billboard(Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC));

	m_pTexture->Render_Texture(m_iIndex);
	m_pBuffer->Render_Buffer();
}

CTree * CTree::Create()
{
	CTree*	pInstance = new CTree;
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CTree::Clone(const Engine::_vec3 * pPos)
{
	CTree*	pInstance = new CTree(*this);

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

void CTree::LoadData(HANDLE hFile)
{
}
