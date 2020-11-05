#include "stdafx.h"
#include "AnimationNode.h"
#include "Animation.h"
#include "Animator.h"
#include "Body.h"
#include "InGameObject.h"

CBody::CBody()
{
}

CBody::CBody(const CBody & rhs)
	:CComponent(rhs),
	m_AnimState(rhs.m_AnimState)
{
	if (!rhs.m_vecObjNames.empty())
	{
		auto iter = rhs.m_vecObjNames.begin();
		while (iter != rhs.m_vecObjNames.end())
		{
			wstring str = (*iter);
			m_vecObjNames.push_back(str);
			iter++;
		}
	}

	auto iter = rhs.m_vecAnimators.begin();
	while (iter != rhs.m_vecAnimators.end())
	{
		CAnimator* animator = dynamic_cast<CAnimator*>((*iter)->Clone());
		m_vecAnimators.push_back(animator);
		iter++;
	}


}

void CBody::PlayAnimation(_tchar * animKey)
{
	auto iter = m_vecAnimators.begin();
	while (iter != m_vecAnimators.end())
	{
		(*iter)->ChangeAnim(animKey);
		(*iter)->Play();
		iter++;
	}
}

void CBody::PlayArmAnimation(_tchar * animKey)
{
	for (int i = 0; i < 2; i++)
	{
		m_vecAnimators[i]->ChangeAnim(animKey);
		m_vecAnimators[i]->Play();
	}
}

void CBody::PlayLegAnimation(_tchar * animKey)
{
	for (int i = 2; i < 4; i++)
	{
		m_vecAnimators[i]->ChangeAnim(animKey);
		m_vecAnimators[i]->Play();
	}
}

void CBody::StopAnimation()
{
	auto iter = m_vecAnimators.begin();
	while (iter != m_vecAnimators.end())
	{
		(*iter)->Stop();
		iter++;
	}
}

void CBody::AddAnimator(CAnimator* animator)
{
	m_vecAnimators.push_back(animator);
}

void CBody::RemoveAnimator(int index)
{
	auto iter = m_vecAnimators.begin();
	iter += index;

	m_vecAnimators.erase(iter);
}

void CBody::SetPartAnimation(int index, CAnimator* animator)
{
	
}

void CBody::freeMem(void)
{
	auto iter = m_vecAnimators.begin();
	while (iter != m_vecAnimators.end())
	{
		Safe_Release((*iter));
		iter++;
	}
	m_vecAnimators.clear();
	CComponent::freeMem();
	
}


void CBody::LoadData(HANDLE hFile)
{

	DWORD dwBytes = 0;
	int size = 0;
	int strSize = 0;
	_tchar str[255];
	wstring objName;
	ReadFile(hFile, &size, sizeof(size), &dwBytes, nullptr);
	for (int i = 0; i < size; i++)
	{
		ZeroMemory(str, 255);
		ReadFile(hFile, &strSize, sizeof(strSize), &dwBytes, nullptr);
		ReadFile(hFile, str, strSize, &dwBytes, nullptr);

		m_vecObjNames.push_back(str);
	}
}

_int CBody::Update_Component(const float & fDeltaTime)
{
	if (!m_vecObjNames.empty())
	{
		for (auto ele : m_vecObjNames)
		{
			CInGameObject* obj = dynamic_cast<CInGameObject*>(m_pGameObject->GetChildObject(ele.c_str()));
			CAnimator* animator = obj->Get_Component<CAnimator>(ANIMATOR, ID_DYNAMIC);
			m_vecAnimators.push_back(animator);
			animator->SetAnimTransform();
		}
		m_vecObjNames.clear();
	}

	return 0;
}

CBody * CBody::Clone()
{
	return new CBody(*this);
}

CBody* CBody::Create()
{
	CBody* body = new CBody();
	body->m_eComType = COMPONENT_TYPE::BODY;
	return body;
}
