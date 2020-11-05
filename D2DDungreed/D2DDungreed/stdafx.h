// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#ifndef __STDAFX_H__
#define __STDAFX_H__

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include "vld.h"
#include <iostream>

#endif // _DEBUG

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <unordered_map>
#include <string>
#include <cassert>
#include <algorithm>
#include <functional>
#include <fstream>
#include <process.h>

using namespace std;

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


#include "../Headers/Define.h"
#include "../Headers/enum.h"
#include "../Headers/struct.h"
#include "../Headers/function.h"
#include "../Headers/Typedef.h"

#include "SoundMgr.h"
#include "CallSingleton.h"

#include "../D2DDungreed/Object/GameObject.h"
#include "../D2DDungreed/Object/Terrain/Terrain.h"
#include "../D2DDungreed/CoolTime/CoolTime.h"

#endif // !__STDAFX_H__
