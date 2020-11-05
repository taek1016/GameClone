#include "stdafx.h"
#include "FieldSkybox.h"

USING(Engine)

CFieldSkybox::CFieldSkybox(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSkyBox(pGraphicDev)
{
	set_Name(L"FieldStageSkybox");
}

CFieldSkybox::CFieldSkybox(const CFieldSkybox & rhs)
	: CSkyBox(rhs)
{
}

CFieldSkybox * CFieldSkybox::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFieldSkybox* pInstance = new CFieldSkybox(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();

	return pInstance;
}

Engine::CGameObject * CFieldSkybox::Clone(void)
{
	CFieldSkybox* pInstance = new CFieldSkybox(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
