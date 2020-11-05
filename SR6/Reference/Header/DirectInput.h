#ifndef InputDev_h__
#define InputDev_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CDirectInput : public CBase
{
	DECLARE_SINGLETON(CDirectInput)

private:
	explicit				CDirectInput(void);
	virtual					~CDirectInput(void);

public:
	_bool					KeyDown(const _ubyte byKeyID);
	_bool					KeyUp(const _ubyte byKeyID);
	_bool					KeyPressing(const _ubyte byKeyID);

	_bool					MouseDown(MOUSEKEYSTATE eMouse);
	_bool					MouseUp(MOUSEKEYSTATE eMouse);
	_bool					MousePress(MOUSEKEYSTATE eMouse);

	_long					Get_MouseMove(MOUSEMOVESTATE eMouseState)
	{
		return *(reinterpret_cast<_long*>(&m_tMouseState) + eMouseState);
	}
private:

public:
	HRESULT					Initialize_InputDev(HINSTANCE hInst, HWND hWnd);
	void					Set_InputDev(void);

private:
	_byte					Get_KeyState(_ubyte byKeyID) { return m_byKeyState[byKeyID]; }
	_byte					Get_MouseState(MOUSEKEYSTATE eMouse) { return m_tMouseState.rgbButtons[eMouse]; }

	LPDIRECTINPUT8			m_pInputSDK = nullptr;
	LPDIRECTINPUTDEVICE8	m_pKeyBoard = nullptr;
	LPDIRECTINPUTDEVICE8	m_pMouse = nullptr;

	_byte					m_byKeyState[256];

	_bool					m_bKeyDown[256];
	_bool					m_bKeyUp[256];

	DIMOUSESTATE			m_tMouseState;

	_bool					m_bMouseDown[DIM_END];
	_bool					m_bMouseUp[DIM_END];

public:
	virtual void			freeMem(void);

};
END
#endif // InputDev_h__
