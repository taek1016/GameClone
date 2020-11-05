#include "KeyMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr(void)
	: CBase()
{
}

CKeyMgr::~CKeyMgr(void)
{
}

HRESULT CKeyMgr::Register_Key(const _int iKey)
{
	auto findedKey = m_mapKey.find(iKey);

	if (m_mapKey.end() != findedKey)
	{
		return E_FAIL;
	}

	m_mapKey.insert(make_pair(iKey, 0x00000001 << m_iCurKeyCount++));

	return S_OK;
}

void CKeyMgr::Update()
{
	m_dwCurKey = 0;

	for (auto& iter : m_mapKey)
	{
		if (GetAsyncKeyState(iter.first) & 0x8000)
		{
			m_dwCurKey |= iter.second;
		}
	}
}

bool CKeyMgr::KeyDown(const _int iKey)
{
	auto findedKey = m_mapKey.find(iKey);

	// ���� ��.
	if (m_mapKey.end() == findedKey)
	{
		return false;
	}

	// ���� ������ ���� ���� ������ �� TRUE
	if (!(m_dwKeyDown & findedKey->second) && (m_dwCurKey & findedKey->second))
	{
		m_dwKeyDown |= findedKey->second;
		return true;
	}
	// ���� ������ �ְ� ���� ������ �ʾ��� �� FALSE
	if ((m_dwKeyDown & findedKey->second) && !(m_dwCurKey & findedKey->second))
	{
		m_dwKeyDown ^= findedKey->second;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyUp(const _int iKey)
{
	auto findedKey = m_mapKey.find(iKey);

	// �ƿ� Ű�� ���� ��
	if (m_mapKey.end() == findedKey)
	{
		return false;
	}

	// ���� ������ �ְ� ���� ������ �ʾ��� �� TRUE
	if ((m_dwKeyUp & findedKey->second) && !(m_dwCurKey & findedKey->second))
	{
		m_dwKeyUp ^= findedKey->second;
		return true;
	}
	// ���� ������ ���� ���� ������ �� FALSE
	if (!(m_dwKeyUp & findedKey->second) && (m_dwCurKey & findedKey->second))
	{
		m_dwKeyUp |= findedKey->second;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyPressing(const _int iKey)
{
	auto findedKey = m_mapKey.find(iKey);

	// �ƿ� Ű�� ���� ��
	if (m_mapKey.end() == findedKey)
	{
		return false;
	}

	if (m_dwCurKey & findedKey->second)
	{
		return true;
	}

	return false;
}

inline void CKeyMgr::freeMem()
{
	m_mapKey.clear();
}
