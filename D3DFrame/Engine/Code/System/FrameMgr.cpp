#include "FrameMgr.h"

#include "System/Frame.h"

USING(Engine)
IMPLEMENT_SINGLETON(CFrameMgr)

Engine::CFrameMgr::CFrameMgr(void)
	: CBase()
	, m_bInitialized(false)
{
}

Engine::CFrameMgr::~CFrameMgr(void)
{
	Free();
}

_bool Engine::CFrameMgr::IsPermit_Call(const _int iFrameTag, const _float fTimeDelta)
{
	CFrame*	pFrame = Find_Frame(iFrameTag);
	NULL_CHECK_RETURN(pFrame, false);

	return pFrame->IsPermit_Call(fTimeDelta);
}

HRESULT Engine::CFrameMgr::Ready_Frame(const _int iFrameTag, const _float fCallLimit)
{
	CFrame*	pFrame = Find_Frame(iFrameTag);

	if (nullptr != pFrame)
		return E_FAIL;

	pFrame = CFrame::Create(fCallLimit);
	NULL_CHECK_RETURN(pFrame, E_FAIL);

	m_vecFrame[iFrameTag] = pFrame;

	return S_OK;
}

void CFrameMgr::Initialize_Frame(const _int iFrameSize)
{
	m_vecFrame.resize(iFrameSize);
}

CFrame* Engine::CFrameMgr::Find_Frame(const _int iFrameTag)
{
	auto iter = m_vecFrame[iFrameTag];

	if (nullptr == iter)
	{
		return nullptr;
	}

	return iter;
}

void Engine::CFrameMgr::Free(void)
{
	for_each(m_vecFrame.begin(), m_vecFrame.end(), Safe_Release<CFrame*>);
	m_vecFrame.clear();
}