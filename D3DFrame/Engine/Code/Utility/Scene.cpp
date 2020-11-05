#include "Scene.h"

USING(Engine)

CScene::CScene(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBase()
	, m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

CScene::~CScene(void)
{
}

inline void CScene::Free(void)
{
	Safe_Release(m_pGraphicDev);
}
