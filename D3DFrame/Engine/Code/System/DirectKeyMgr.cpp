#include "DirectKeyMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CDirectInput)

CDirectInput::CDirectInput(void)
	: CBase()
{
	const _int iSize = 256;
	::ZeroMemory(m_byKeyState, sizeof(_byte) * iSize);
	::ZeroMemory(m_bKeyDown, sizeof(_bool) * iSize);
	::ZeroMemory(m_bKeyUp, sizeof(_bool) * iSize);

	::ZeroMemory(m_bMouseDown, sizeof(_bool) * MOUSEKEYSTATE::DIM_END);
	::ZeroMemory(m_bMouseUp, sizeof(_bool) * MOUSEKEYSTATE::DIM_END);
}

CDirectInput::~CDirectInput(void)
{
	Free();
}

_bool CDirectInput::KeyDown(const _ubyte byKeyID)
{
	_ubyte	bCurKeyState = (_ubyte)(m_byKeyState[byKeyID] & 0x80);

	//	전에 누른 적 없고 현재 눌렀을 때 true
	if (!(m_bKeyDown[byKeyID]) && (bCurKeyState))
	{
		m_bKeyDown[byKeyID] = true;
		return true;
	}

	//	전에 누른 적 있고 현재 누르지 않았을 때 false
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

	//	전에 누른 적 있고 현재 누르지 않았을 때 true;
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
	_bool bPressed = false;

	if (m_byKeyState[byKeyID] & 0x80)
	{
		bPressed = true;
	}

	return  bPressed;
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

	//	전에 누른 적 있고 현재 누르지 않았을 때 true;
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
	if (m_tMouseState.rgbButtons[eMouse] & 0x80)
	{
		return true;
	}

	return false;
}

_long CDirectInput::Get_MouseMove(MOUSEMOVESTATE eMouseState)
{
	return *(reinterpret_cast<_long*>(&m_tMouseState) + eMouseState);
}

HRESULT CDirectInput::Initialize_InputDev(HINSTANCE hInst, HWND hWnd)
{
#pragma region Create_DirectInputCom
	// DInput 컴객체를 생성하는 함수
	FAILED_CHECK_RETURN(DirectInput8Create(hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pInputSDK,
		NULL), E_FAIL);
#pragma endregion

#pragma region Create_Keyboard
	// 키보드 객체 생성
	FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr), E_FAIL);

	// 생성된 키보드 객체의 대한 정보를 컴 객체에게 전달하는 함수
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// 장치에 대한 독점권을 설정해주는 함수, (클라이언트가 떠있는 상태에서 키 입력을 받을지 말지를 결정하는 함수)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// 장치에 대한 access 버전을 받아오는 함수
	m_pKeyBoard->Acquire();
#pragma endregion

#pragma region Create_Mouse
	// 마우스 객체 생성
	FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr), E_FAIL);

	// 생성된 마우스 객체의 대한 정보를 컴 객체에게 전달하는 함수
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// 장치에 대한 독점권을 설정해주는 함수, 클라이언트가 떠있는 상태에서 키 입력을 받을지 말지를 결정하는 함수
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// 장치에 대한 access 버전을 받아오는 함수
	m_pMouse->Acquire();
#pragma endregion

#pragma region Clear
	::ZeroMemory(m_bKeyDown, sizeof(_bool) * 256);
	::ZeroMemory(m_bKeyUp, sizeof(_bool) * 256);
#pragma endregion

	return S_OK;
}

void CDirectInput::Set_InputDev(void)
{
	m_pKeyBoard->GetDeviceState(256, m_byKeyState);
	m_pMouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);
}

void CDirectInput::Free(void)
{
	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pMouse);
	Safe_Release(m_pInputSDK);
}