#include "stdafx.h"
#include "Animator.h"
#include "Animation.h"

USING(Engine)

CAnimator::CAnimator()
{
}

CAnimator::CAnimator(const CAnimator & rhs)
	:CComponent(rhs)
{
	auto iter = rhs.m_mapAnimation.begin();
	while (iter != rhs.m_mapAnimation.end())
	{
		CAnimation* animation = (*iter).second->Clone();
		CTransform* transform = m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
		transform->AddRef();
		animation->SetTransform(transform);
		
		m_mapAnimation.insert(make_pair((*iter).first, animation));
		iter++;
	}
}

void CAnimator::AddAnimation(_tchar *animKey, CAnimation * anim)
{
	auto iter = find_if(m_mapAnimation.begin(), m_mapAnimation.end(), [&animKey](std::map<wstring, CAnimation*>::value_type const& itr)->bool
	{
		return animKey == itr.first ? true : false;
	});
	if (iter != m_mapAnimation.end())
	{
		Safe_Release((*iter).second);
		m_mapAnimation.erase(iter);
	}
	m_mapAnimation.emplace(make_pair(animKey, anim));
	
	

	anim->SetTransform(m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC));
}

void CAnimator::Play()
{
	m_pCurAnimation->Play();
}

void CAnimator::ChangeAnim(const _tchar * animKey)
{
	auto iter = find_if(m_mapAnimation.begin(), m_mapAnimation.end(), [&animKey](std::map<wstring, CAnimation*>::value_type const& itr)->bool
	{
		return animKey == itr.first ? true : false;
	});
	if (iter == m_mapAnimation.end())
	{
		return;
	}
	/*if(m_pCurAnimation != nullptr)
		m_pCurAnimation->Stop();*/
	if (m_pCurAnimation == nullptr)
	{
		m_pCurAnimation = m_mapAnimation[animKey];
		
		m_pCurAnimation->Start();
		m_pCurAnimation->Initialize();
		return;
	}
	if (wcscmp(m_pCurAnimation->GetAnimName(), m_mapAnimation[animKey]->GetAnimName()) != 0)
	{
		m_pCurAnimation = m_mapAnimation[animKey];
		m_pCurAnimation->Start();
		m_pCurAnimation->Initialize();
	}
}

void CAnimator::Stop()
{
	if(m_pCurAnimation != nullptr)
		m_pCurAnimation->Stop();
}

int CAnimator::Update_Component(const float& fDeltaTime)
{
	return 0;
}


CAnimator * CAnimator::Create()
{
	CAnimator* animator = new CAnimator();
	animator->m_eComType = COMPONENT_TYPE::ANIMATOR;
	return animator;
}

void CAnimator::LoadData(HANDLE hFile)
{
	DWORD dwBytes = 0;
	_tchar strKey[255];
	int mapSize;
	ReadFile(hFile, &mapSize, sizeof(mapSize), &dwBytes, nullptr);
	for(int i=0;i<mapSize;i++)
	{
		CAnimation* anim = CAnimation::Create();

		int size;
		ReadFile(hFile, &size, sizeof(size), &dwBytes, nullptr);
		ReadFile(hFile, strKey, 255, &dwBytes, nullptr);
		
		anim->LoadData(hFile);
		anim->SetTransform(m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC));
		m_mapAnimation.emplace(strKey, anim);
	}
}

void CAnimator::SetAnimTransform()
{
	auto iter = m_mapAnimation.begin();
	while (iter != m_mapAnimation.end())
	{
		CTransform* transform = m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
		(*iter).second->SetTransform(transform);
		iter++;
	}
}

HRESULT CAnimator::Attach(CGameObject * pObj, COMPONENTID com_ID)
{
	m_pGameObject = pObj;
	m_pGameObject->Add_Component(COMPONENT_TYPE::ANIMATOR, this, com_ID);
	return E_NOTIMPL;
}

CComponent* CAnimator::Clone()
{
	return new CAnimator(*this);
}

void CAnimator::freeMem(void)
{
	CComponent::freeMem();
	for_each(m_mapAnimation.begin(), m_mapAnimation.end(), CDeleteMap());
	m_mapAnimation.clear();
}