#include "stdafx.h"
#include "ToolContainerMgr.h"



USING(Engine)
IMPLEMENT_SINGLETON(CToolContainer)

CToolContainer::CToolContainer(void)
{
}

CToolContainer::~CToolContainer(void)
{
	Free();
}

void CToolContainer::Add_Tool(const Engine::_tchar * pKey, CDialogEx* pTool)
{
	auto iter = find_if(m_mapContainer.begin(), m_mapContainer.end(), CTag_Finder(pKey));

	if (m_mapContainer.end() != iter)
	{
		return;
	}

	m_mapContainer.insert(make_pair(pKey, pTool));
}

inline void CToolContainer::Free(void)
{
	m_mapContainer.clear();
}