#ifndef Macros_L_h__
#define Macros_L_h__

// Define 잡을 때 #define 이름_자기_이니셜로 잡기.
#define BACK_BUFFER_BLUE_L	D3DXCOLOR(0.f, 0.f, 1.f, 1.f)

#define CALL_DESTROY_L(singleton)	\
if (nullptr != singleton)			\
{									\
	singleton->DestroyInstance();	\
	singleton = nullptr;			\
}

#define PRESS_KEY_L(key)	(DLL::pDirectInput->Get_KeyState(key) & 0x80)

#endif // Macros_L_h__
