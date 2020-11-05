#include "stdafx.h"
#include "Terrain.h"

USING(Engine)

CTerrain::CTerrain(void)
	: CGameObject()
{
	SetName(L"Terrain");
}

CTerrain::CTerrain(const CTerrain & rhs)
	: CGameObject(rhs)
{
	SetName(L"Terrain");
}

CTerrain::~CTerrain(void)
{

}

HRESULT CTerrain::Initialize_GameObject(void)
{
	Engine::CComponent*		pComponent = nullptr;

	pComponent = DLL::pResourceMgr->Clone(RESOURCE_STATIC, L"Buffer_TerrainTex");

	NULL_CHECK_RETURN(pComponent, E_FAIL);

	HANDLE hFile = CreateFile(
		L"../../Terrain.dat", /* 파일 경로 */
		GENERIC_READ,
		0,
		nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return 0;

	pComponent->LoadData(hFile);

	CloseHandle(hFile);
	pComponent->Attach(this, ID_STATIC);

	pComponent = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->Attach(this, ID_DYNAMIC);

	return S_OK;
}

_int CTerrain::Update_GameObject(const _float& fTimeDelta)
{
	Engine::CGameObject::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(Engine::RENDER_NONALPHA, this);

	return 0;
}

void CTerrain::Render_GameObject(void)
{
	CTexture*		pTextureCom = Get_Component<CTexture>(TEXTURE, ID_STATIC);

	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_WORLD, 
		Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_World());

	Get_Component<CTerrainTex>(BODY, ID_STATIC)->Render_Buffer();
}


CTerrain* CTerrain::Create()
{
	CTerrain*	pInstance = new CTerrain();

	if (FAILED(pInstance->Initialize_GameObject()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

void CTerrain::freeMem(void)
{
	Engine::CGameObject::freeMem();
}

void CTerrain::LoadData(HANDLE hFile)
{
}

CGameObject * CTerrain::Clone(const _vec3 * pPos)
{
	CTerrain* pInstance = new CTerrain(*this);

	if (FAILED(pInstance->Initialize_GameObject()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}