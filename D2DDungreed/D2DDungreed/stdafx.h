// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#ifndef __STDAFX_H__
#define __STDAFX_H__

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include "vld.h"
#include <iostream>

#endif // _DEBUG

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
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
