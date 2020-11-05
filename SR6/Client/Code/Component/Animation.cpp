#include "stdafx.h"
#include "Animation.h"
#include "AnimationNode.h"

USING(Engine)

CAnimation::CAnimation()
{
	ZeroMemory(m_strAnimName, sizeof(_tchar) * 100);
}

CAnimation::~CAnimation()
{

}

CAnimation::CAnimation(const CAnimation & rhs)
	: CBase(rhs)
	,m_bStart(true)
{
	auto iter = rhs.m_ltAnimations.begin();
	while (iter != rhs.m_ltAnimations.end())
	{
		CAnimationNode* animNode = new CAnimationNode(*(*iter));
		m_ltAnimations.push_back((animNode));
		iter++;
	}
	ZeroMemory(m_strAnimName, 255);
	wcscpy_s(m_strAnimName, rhs.m_strAnimName);

	Initialize();
}

list<CAnimationNode*>::iterator CAnimation::GetAnimListIter()
{
	return m_ltAnimations.begin();
}

list<CAnimationNode*>::iterator CAnimation::GetAnimListEndIter()
{
	return m_ltAnimations.end();
}

void CAnimation::SetTransform(Engine::CTransform * transform)
{
	auto iter = m_ltAnimations.begin();
	while (iter != m_ltAnimations.end())
	{
		(*iter)->SetTransform(transform);
		iter++;
	}
}

void CAnimation::SetAnimName(_tchar * strName, int size)
{
	ZeroMemory(m_strAnimName, 100);
	wcscpy_s(m_strAnimName, sizeof(_tchar) * size, strName);
}

void CAnimation::DeleteAnimation(int index)
{
	auto iter = m_ltAnimations.begin();
	for (int i = 0; i < index; i++)
	{
		iter++;
	}
	delete *iter;
	*iter = nullptr;
	m_ltAnimations.erase(iter);
}

void CAnimation::Initialize()
{
	m_iter = m_ltAnimations.begin();
}

void CAnimation::Update(const float & fTimeDelta)
{
	if (m_bPlay)
	{
		(*m_iter)->Action(fTimeDelta);
		if ((*m_iter)->IsEnd())
		{
			m_iter++;
			if (m_iter == m_ltAnimations.end())
			{
				m_iter = m_ltAnimations.begin();
			}
			(*m_iter)->Play();
		}
	}
	return ;
}

void CAnimation::Play()
{
	if ((*m_iter)->IsEnd())
	{
		m_iter++;
		if (m_iter == m_ltAnimations.end())
		{
			m_iter = m_ltAnimations.begin();
		}
		(*m_iter)->Play();
	}
	(*m_iter)->Action(0);
}

void CAnimation::Stop()
{
	m_bStart = true;
	m_bPlay = false;
	(*m_iter)->Stop();
	m_iter = m_ltAnimations.begin();

}

void CAnimation::freeMem()
{
	//for_each(m_ltAnimations.begin(), m_ltAnimations.end(), CDeleteObj());
	/*for (auto iter : m_ltAnimations)
	{
		Safe_Release(iter);
	}
	m_ltAnimations.clear();*/
}

void CAnimation::AddAnimation(CAnimationNode * animNode)
{
	m_ltAnimations.push_back(animNode);
}


CAnimation * CAnimation::Create()
{
	CAnimation* anim = new CAnimation();
	anim->m_iter = anim->m_ltAnimations.begin();
	return anim;
}
void CAnimation::SaveData(HANDLE hFile)
{
	DWORD dwBytes = 0;
	WriteFile(hFile, m_strAnimName, 100, &dwBytes, nullptr);

	int listCount = m_ltAnimations.size();
	WriteFile(hFile, &listCount, sizeof(int), &dwBytes, nullptr);

	auto iter = m_ltAnimations.begin();
	while (iter != m_ltAnimations.end())
	{
		(*iter)->SaveData(hFile);
		iter++;
	}
}

void CAnimation::LoadData(HANDLE hFile)
{
	DWORD dwBytes = 0;
	ReadFile(hFile, m_strAnimName, 100, &dwBytes, nullptr);

	int size = 0;
	ReadFile(hFile, &size, sizeof(size), &dwBytes, nullptr);
	
	for (int i = 0; i < size; i++)
	{
		CAnimationNode* animNode = new CAnimationNode();
		animNode->LoadData(hFile);
		m_ltAnimations.push_back(animNode);
	}
	m_iter = m_ltAnimations.begin();
}

CAnimation * CAnimation::Clone()
{
	CAnimation* anim = new CAnimation();
	*anim = *this;
	anim->m_iter = anim->m_ltAnimations.begin();
	wcscpy_s(anim->m_strAnimName, 100, m_strAnimName);

	anim->m_ltAnimations.clear();

	auto iter = m_ltAnimations.begin();
	while (iter != m_ltAnimations.end())
	{
		CAnimationNode* node = new CAnimationNode(*(*iter));
		anim->m_ltAnimations.push_back(*iter);
		iter++;
	}
	anim->Initialize();
	return anim;
}
