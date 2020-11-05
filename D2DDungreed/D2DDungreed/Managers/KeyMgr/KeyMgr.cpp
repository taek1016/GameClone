#include "stdafx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr()
	: m_dwKeyDown(0)
	, m_dwCurKey(0)
	, m_dwKeyUp(0)
{
	AssertMember();
}

CKeyMgr::~CKeyMgr()
{
	m_dwCurKey	= 0;
	m_dwKeyDown = 0;
	m_dwKeyUp	= 0;

	AssertMember();
}

void CKeyMgr::Update()
{
	m_dwCurKey = 0;
	
	if (KEY_PRESS('W'))
	{
		m_dwCurKey |= KEY_UP;
	}

	if (KEY_PRESS('S'))
	{
		m_dwCurKey |= KEY_DOWN;
	}
	
	if (KEY_PRESS('A'))
	{
		m_dwCurKey |= KEY_LEFT;
	}
	
	if (KEY_PRESS('D'))
	{
		m_dwCurKey |= KEY_RIGHT;
	}

	if (KEY_PRESS('V'))
	{
		m_dwCurKey |= KEY_V;
	}

	if (KEY_PRESS('F'))
	{
		m_dwCurKey |= KEY_F;
	}

	if (KEY_PRESS(VK_LBUTTON))
	{
		m_dwCurKey |= KEY_LBUTTON;
	}

	if (KEY_PRESS(VK_RBUTTON))
	{
		m_dwCurKey |= KEY_RBUTTON;
	}

	if (KEY_PRESS(VK_RETURN))
	{
		m_dwCurKey |= KEY_RETURN;
	}

	if (KEY_PRESS(VK_SPACE))
	{
		m_dwCurKey |= KEY_SPACE;
	}

	if (KEY_PRESS(VK_TAB))
	{
		m_dwCurKey |= KEY_TAB;
	}

}

bool CKeyMgr::KeyDown(DWORD dwKey)
{
	if (!(m_dwKeyDown & dwKey) && (m_dwCurKey & dwKey))
	{
		m_dwKeyDown |= dwKey;
		return true;
	}
	if ((m_dwKeyDown & dwKey) && !(m_dwCurKey & dwKey))
	{
		m_dwKeyDown ^= dwKey;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyUp(DWORD dwKey)
{
	if ((m_dwKeyUp & dwKey) && !(m_dwCurKey & dwKey))
	{
		m_dwKeyUp ^= dwKey;
		return true;
	}

	if (!(m_dwKeyUp & dwKey) && (m_dwCurKey & dwKey))
	{
		m_dwKeyUp |= dwKey;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyPressing(DWORD dwKey)
{
	if (m_dwCurKey & dwKey)
	{
		return true;
	}

	return false;
}

void CKeyMgr::AssertMember() const
{
	assert(0 == m_dwKeyDown);
	assert(0 == m_dwKeyUp);
	assert(0 == m_dwCurKey);
}
