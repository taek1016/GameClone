#include "Management.h"

USING(Engine)
IMPLEMENT_SINGLETON(CManagement)

Engine::CManagement::CManagement(void)
	: CBase()
{
}

Engine::CManagement::~CManagement(void)
{
	Free();
}

_int CManagement::Update_Scene(const _float& fTimeDelta)
{
	_int iExit = m_pScene->Update_Scene(fTimeDelta);

	return iExit;
}

void Engine::CManagement::Render_Scene(void)
{
	if (nullptr == m_pScene)
	{
		return;
	}

	m_pScene->Render_Scene();
}


void Engine::CManagement::Free(void)
{
	Safe_Release(m_pScene);
}