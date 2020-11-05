#ifndef Macros_L_h__
#define Macros_L_h__

// Define ���� �� #define �̸�_�ڱ�_�̴ϼȷ� ���.
#define BACK_BUFFER_BLUE_L	D3DXCOLOR(0.f, 0.f, 1.f, 1.f)

#define CALL_DESTROY_L(singleton)	\
if (nullptr != singleton)			\
{									\
	singleton->DestroyInstance();	\
	singleton = nullptr;			\
}

#define PRESS_KEY_L(key)	(DLL::pDirectInput->Get_KeyState(key) & 0x80)

#endif // Macros_L_h__
