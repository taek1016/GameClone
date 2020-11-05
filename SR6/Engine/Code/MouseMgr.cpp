#include "MouseMgr.h"

#include "Mouse.h"

USING(Engine)
IMPLEMENT_SINGLETON(CMouseManager)

CMouseManager::CMouseManager(void)
{
	ShowCursor(FALSE);
}

CMouseManager::~CMouseManager(void)
{
	ShowCursor(TRUE);
	freeMem();
}

void CMouseManager::Late_Initialize()
{
	for (auto iter : m_vecMouse)
	{
		if (nullptr == iter)
		{
			continue;
		}
		iter->Late_Initialize();
	}
}

HRESULT CMouseManager::Initialize_MouseMgr(const _int & iMaxIdx, const HWND& hWnd)
{
	freeMem();

	m_iCurMouse = 0;
	m_iMaxMouse = iMaxIdx;
	m_vecMouse.resize(m_iMaxMouse);

	m_hWnd = hWnd;

	return S_OK;
}

HRESULT CMouseManager::Set_CurMouse(const _int & iCurMouse)
{
	if (iCurMouse >= m_iMaxMouse)
	{
		return E_FAIL;
	}

	m_iCurMouse = iCurMouse;
	return S_OK;
}

_int CMouseManager::Update_Mouse(const _float & fTimeDelta)
{
	_int iExit = 0;

	if (m_vecMouse[m_iCurMouse])
	{
		iExit = m_vecMouse[m_iCurMouse]->Update_GameObject(fTimeDelta);
	}

	POINT pt;
	::GetCursorPos(&pt);
	::ScreenToClient(m_hWnd, &pt);

	m_vMouse.x = static_cast<_float>(pt.x);
	m_vMouse.y = static_cast<_float>(pt.y);
	m_vMouse.z = 0.f;

	return iExit;
}

const _vec3* CMouseManager::GetMousePos()
{
	return &m_vMouse;
}

inline void CMouseManager::freeMem()
{
	for (_int i = 0; i < m_iMaxMouse; ++i)
	{
		Safe_Release(m_vecMouse[i]);
	}
	m_vecMouse.clear();
}