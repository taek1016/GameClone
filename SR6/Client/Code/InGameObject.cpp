#include "stdafx.h"
#include "InGameObject.h"

USING(Engine)

CInGameObject::CInGameObject()
	:CGameObject()
{

}

CInGameObject::CInGameObject(const CInGameObject& rhs)
	: CGameObject(rhs)
{
	for (size_t i = 0; i < rhs.m_vecChildObject.size(); i++)
	{
		CInGameObject* obj = dynamic_cast<CInGameObject*>(rhs.m_vecChildObject[i]->Clone(&_vec3(0, 0, 0))); 
		CTransform* transform = obj->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
		transform->SetParent(Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC));
		m_vecChildObject.push_back(obj);
	}
}

void CInGameObject::LoadData(HANDLE hFile)
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

	SetName(str);

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
		CInGameObject* obj = new CInGameObject();
		obj->LoadData(hFile);
		CTransform* transform = obj->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
		transform->SetParent(Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC));
		CComponent* pComponent = nullptr;
		
		
		switch (i)
		{
		case 0:
			pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"PlayerRightArm");
			break;
		case 1:
			pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"PlayerBody");
			break;
		case 2:
			pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"PlayerHead");
			break;
		case 3:
			pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"PlayerRightLeg");
			break;
		case 4:
			pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"PlayerLeftArm");
			break;
		case 5:
			pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"PlayerLeftLeg");
			break;
		}

		pComponent->Attach(obj, ID_STATIC);

		m_vecChildObject.push_back(obj);
	}
	int b = 0;
}

CGameObject * CInGameObject::Clone(const _vec3 * pPos /*= nullptr*/)
{
	CInGameObject* object = new CInGameObject(*this);
	return object;
}

Engine::_int CInGameObject::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);
	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);
	for (auto ele : m_vecChildObject)
	{
		ele->Update_GameObject(fTimeDelta);
		DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, ele);
	}
	return iExit;
}

void CInGameObject::Render_GameObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = DLL::pGraphicDev->GetDevice();
	CTransform* transform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	pDevice->SetTransform(D3DTS_WORLD, &(*Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC)->Get_World()));

	CTexture* texture = Get_Component<CTexture>(TEXTURE, ID_STATIC);
	if(texture != nullptr)
		texture->Render_Texture();

	CCubeTex* tex = Get_Component<Engine::CCubeTex>(BUFFER, ID_DYNAMIC);
	if (tex != nullptr)
		tex->Render_Buffer();

	for (auto ele : m_vecChildObject)
	{
		ele->Render_GameObject();
	}
	
	//CVIBuffer* pBuffer = Get_Component<CVIBuffer>(COMPONENT_TYPE::BUFFER, ID_DYNAMIC);

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//pBuffer->Render_Buffer();
}

CInGameObject * CInGameObject::Create()
{
	CInGameObject* obj = new CInGameObject();
	return obj;
}

void CInGameObject::freeMem()
{
	CGameObject::freeMem();

	auto iter = m_vecChildObject.begin();
	while (iter != m_vecChildObject.end())
	{
		Safe_Release((*iter));
		iter++;
	}
	
}
