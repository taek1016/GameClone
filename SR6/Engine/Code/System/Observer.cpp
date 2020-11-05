#include "Observer.h"
#include "Content.h"

USING(Engine)

CObserver::CObserver(void)
{
}

CObserver::~CObserver(void)
{
	freeMem();
}

void CObserver::Notify(_int iMessage, void* pData)
{
	for (auto iter : m_ObserverList)
	{
		iter->Update_Content(iMessage, pData);
	}
}

void CObserver::Subscribe(CContent* pContent)
{
	NULL_CHECK_MSG(pContent, L"Observer Subscribe is nullptr");

	pContent->AddRef();
	m_ObserverList.push_back(pContent);
}

void CObserver::UnSubscribe(CContent* pContent)
{
	NULL_CHECK_MSG(pContent, L"Observer UnSubscribe is nullptr");

	// 주소값으로 찾아옴
	auto iter = find(m_ObserverList.begin(), m_ObserverList.end(), pContent);

	if (m_ObserverList.end() == iter)
	{
		MSG_BOX("Observer UnSubscribe not exist");
		return;
	}

	Safe_Release(iter);
	m_ObserverList.erase(iter);
}

CObserver * CObserver::Create(void)
{
	return new CObserver();
}

void CObserver::freeMem(void)
{
	for_each(m_ObserverList.begin(), m_ObserverList.end(), Safe_Release<CContent*>);
}
