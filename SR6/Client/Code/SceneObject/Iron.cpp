#include "stdafx.h"
#include "Iron.h"

USING(Engine)

CIron::CIron(void)
	: CGameObject()
{
	SetName(L"Iron");
}

CIron::CIron(const CIron & rhs)
	: CGameObject(rhs)
{
}

CIron::~CIron(void)
{
}

HRESULT CIron::Late_Initialize()
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

	m_pPlayerCol = DLL::pSearchMgr->Get_Object(L"Player")->Get_Component<CCollider>(COLLIDER, ID_DYNAMIC);
	m_pMyCol = Get_Component<CSphere>(COLLIDER, ID_DYNAMIC);

	return S_OK;
}

HRESULT CIron::Initialize_GameObject()
{
	CComponent*	pComponent = nullptr;

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	pComponent = CSphere::Create(1.f);
	pComponent->Attach(this, ID_DYNAMIC);

	m_iIndex = rand() % 5;	// Iron 이미지 개수가 5

	m_pTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"Iron"));
	m_pTexture->Attach(this, ID_STATIC);

	m_pBuffer = dynamic_cast<CRcTex*>(DLL::pResourceMgr->Clone(RESOURCE_STATIC, L"Buffer_RcTex"));
	m_pBuffer->Attach(this, ID_STATIC);

	return S_OK;
}

Engine::_int CIron::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	if (m_pMyCol->Is_Collide(m_pPlayerCol))
	{
		if (DLL::pDirectInput->KeyPressing(DIK_T))
		{
			m_fGatherTime += fTimeDelta;

			if (m_fGatherTime >= m_fDieTime)
			{
				// 인벤토리에 아이템 추가
				DLL::pSoundMgr->PlaySound(L"StoneGather.wav", CSoundMgr::CHANNEL_ID::EFFECT);
				DLL::pInventory->Add_Material(MATERIAL_STONE);
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

void CIron::Render_GameObject(void)
{
	DLL::pCameraMgr->Make_Billboard(Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC));

	m_pTexture->Render_Texture(m_iIndex);
	m_pBuffer->Render_Buffer();
}

CIron * CIron::Create()
{
	CIron*	pInstance = new CIron;
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CIron::LoadData(HANDLE hFile)
{
}

CGameObject * CIron::Clone(const _vec3 * pPos)
{
	CIron*	pInstance = new CIron(*this);

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
