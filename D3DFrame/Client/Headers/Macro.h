#ifndef Macro_h__
#define Macro_h__

#define DESTROY_SINGLETON(pSingleton) { pSingleton->DestroyInstance(); pSingleton = nullptr; }

#define WINCX							1280
#define WINCY							static_cast<int>(WINCX / 16.f * 9)
#endif // Macro_h__
