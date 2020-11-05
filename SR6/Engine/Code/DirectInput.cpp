#include "DirectInput.h"

USING(Engine)
IMPLEMENT_SINGLETON(CDirectInput)

CDirectInput::CDirectInput(void)
{

}

CDirectInput::~CDirectInput(void)
{
	freeMem();
}

_bool CDirectInput::KeyDown(const _ubyte byKeyID)
{
	_ubyte	bCurKeyState = (_ubyte)(m_byKeyState[byKeyID] & 0x80);

	//	���� ���� �� ���� ���� ������ �� true
	if (!(m_bKeyDown[byKeyID]) && (bCurKeyState))
	{
		m_bKeyDown[byKeyID] = true;
		return true;
	}

	//	���� ���� �� �ְ� ���� ������ �ʾ��� �� false
	if (m_bKeyDown[byKeyID] && !bCurKeyState)
	{
		m_bKeyDown[byKeyID] = false;
		return false;
	}

	return false;
}

_bool CDirectInput::KeyUp(const _ubyte byKeyID)
{
	_ubyte	bCurKeyState = (_ubyte)(m_byKeyState[byKeyID] & 0x80);

	//	���� ���� �� �ְ� ���� ������ �ʾ��� �� true;
	if (m_bKeyUp[byKeyID] && !bCurKeyState)
	{
		m_bKeyUp[byKeyID] = false;
		return true;

	}

	if (!m_bKeyUp[byKeyID] && bCurKeyState)
	{
		m_bKeyUp[byKeyID] = true;
		return false;
	}

	return false;
}

_bool CDirectInput::KeyPressing(const _ubyte byKeyID)
{
	return  (m_byKeyState[byKeyID] & 0x80);
}

_bool CDirectInput::MouseDown(MOUSEKEYSTATE eMouse)
{
	_ubyte	bCurKeyState = static_cast<_ubyte>(m_tMouseState.rgbButtons[eMouse] & 0x80);

	if (!(m_bMouseDown[eMouse]) && (bCurKeyState))
	{
		m_bMouseDown[eMouse] = true;
		return true;
	}

	if (m_bMouseDown[eMouse] && !bCurKeyState)
	{
		m_bMouseDown[eMouse] = false;
		return false;
	}

	return false;
}

_bool CDirectInput::MouseUp(MOUSEKEYSTATE eMouse)
{
	_ubyte	bCurKeyState = static_cast<_ubyte>(m_tMouseState.rgbButtons[eMouse] & 0x80);

	//	���� ���� �� �ְ� ���� ������ �ʾ��� �� true;
	if (m_bMouseUp[eMouse] && !bCurKeyState)
	{
		m_bMouseUp[eMouse] = false;
		return true;

	}

	if (!m_bMouseUp[eMouse] && bCurKeyState)
	{
		m_bMouseUp[eMouse] = true;
		return false;
	}

	return false;
}

_bool CDirectInput::MousePress(MOUSEKEYSTATE eMouse)
{
	return  (m_tMouseState.rgbButtons[eMouse] & 0x80);
}

HRESULT CDirectInput::Initialize_InputDev(HINSTANCE hInst, HWND hWnd)
{
	// DInput �İ�ü�� �����ϴ� �Լ�
	FAILED_CHECK_RETURN(DirectInput8Create(hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pInputSDK,
		NULL), E_FAIL);

	// Ű���� ��ü ����
	FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr), E_FAIL);

	// ������ Ű���� ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// ��ġ�� ���� �������� �������ִ� �Լ�, (Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pKeyBoard->Acquire();


	// ���콺 ��ü ����
	FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr), E_FAIL);

	// ������ ���콺 ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// ��ġ�� ���� �������� �������ִ� �Լ�, Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pMouse->Acquire();

	return S_OK;
}

void CDirectInput::Set_InputDev(void)
{
	m_pKeyBoard->GetDeviceState(256, m_byKeyState);
	m_pMouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);
}

void CDirectInput::freeMem(void)
{
	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pMouse);
	Safe_Release(m_pInputSDK);
}