#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject()
	: m_tInfo{}

	, m_wStrObjectKey()
	, m_wStrObjectStatus()

	, m_tMainRect{}

	, m_tFrame{}

	, m_eObjType(OBJECT_TYPE::OBJECT_END)
{
	AssertMember();
	m_tInfo.SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
}

CGameObject::~CGameObject()
{
	m_wStrObjectKey.clear();
	AssertMember();
}

void CGameObject::Animate()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta();

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		m_tFrame.fCurFrame = 0.f;
	}
}

void CGameObject::AssertMember()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_tInfo.matWorld.m[i][j] = 0;
		}
	}

	m_tInfo.SetInitial();
	
	m_tMainRect.bottom = 0;
	m_tMainRect.left = 0;
	m_tMainRect.right = 0;
	m_tMainRect.top = 0;

	m_tInfo.iColorValue = 0;

#ifdef _DEBUG
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			assert(0 == m_tInfo.matWorld.m[i][j]);
		}
	}
	assert(0 == m_tInfo.iColorValue);

	for (int i = 0; i < 3; ++i)
	{
		assert(0 == m_tInfo.vDir[i]);
		assert(0 == m_tInfo.vLook[i]);
		assert(0 == m_tInfo.vPos[i]);
		assert(0 == m_tInfo.vSize[i]);
	}

	assert(0 == m_tMainRect.bottom);
	assert(0 == m_tMainRect.top);
	assert(0 == m_tMainRect.left);
	assert(0 == m_tMainRect.right);

	assert(0 == m_wStrObjectKey.size());

#endif // _DEBUG
}