#include "GraphicDev.h"

USING(Engine)
IMPLEMENT_SINGLETON(CGraphicDev)

CGraphicDev::CGraphicDev(void)
	: CBase()
	, m_fScreenX(0.f)
	, m_fScreenY(0.f)
{
}

CGraphicDev::~CGraphicDev(void)
{
	Free();
}

void CGraphicDev::GetScreenData(_float * pScreenX, _float * pScreenY)
{
	*pScreenX = m_fScreenX;
	*pScreenY = m_fScreenY;
}

HRESULT CGraphicDev::Initialize_GraphicDev(HWND hWnd, WINMODE eMode, const _uint & iSizeX, const _uint & iSizeY)
{
	FAILED_CHECK_RETURN(initialize_SDK(), E_FAIL);
	FAILED_CHECK_RETURN(initialize_Device(hWnd, eMode, iSizeX, iSizeY), E_FAIL);
	FAILED_CHECK_RETURN(initialize_Line(), E_FAIL);

	return S_OK;
}

HRESULT CGraphicDev::initialize_SDK()
{
#pragma region CREATE_SDK
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	NULL_CHECK_RETURN(m_pSDK, E_FAIL);
#pragma endregion

	return S_OK;
}

HRESULT CGraphicDev::initialize_Device(HWND hWnd, WINMODE eMode, const _uint & iSizeX, const _uint & iSizeY)
{
#pragma region DEV_CAPS
	D3DCAPS9			DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		return E_FAIL;
	}

	_ulong		uFlag = 0;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		uFlag |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	}
	else
	{
		uFlag |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	}
#pragma endregion

#pragma region D3DPRESENT_PARAMETERS
	D3DPRESENT_PARAMETERS			Present_Parameter;
	ZeroMemory(&Present_Parameter, sizeof(D3DPRESENT_PARAMETERS));

	m_fScreenX = static_cast<_float>(iSizeX);
	m_fScreenY = static_cast<_float>(iSizeY);

	Present_Parameter.BackBufferWidth = iSizeX;
	Present_Parameter.BackBufferHeight = iSizeY;
	Present_Parameter.BackBufferFormat = D3DFMT_A8R8G8B8;
	Present_Parameter.BackBufferCount = 1;

	Present_Parameter.MultiSampleType = D3DMULTISAMPLE_NONE;
	Present_Parameter.MultiSampleQuality = 0;

	Present_Parameter.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Present_Parameter.hDeviceWindow = hWnd;

	Present_Parameter.Windowed = eMode;
	Present_Parameter.EnableAutoDepthStencil = TRUE;
	Present_Parameter.AutoDepthStencilFormat = D3DFMT_D24S8;

	Present_Parameter.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	Present_Parameter.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
#pragma endregion

#pragma region CREATE_REGION
	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, uFlag, &Present_Parameter, &m_pGraphicDev)))
	{
		return E_FAIL;
	}
#pragma endregion

	return S_OK;
}

HRESULT CGraphicDev::initialize_Line(void)
{
	HRESULT hr = D3DXCreateLine(m_pGraphicDev, &m_pLine);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	m_pLine->SetWidth(3.f);
	return S_OK;
}

inline void CGraphicDev::Free(void)
{
	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pSDK);
}

void CGraphicDev::Render_Begin(D3DXCOLOR Color)
{
#pragma region CLEAR_SCREEN
	m_pGraphicDev->Clear(0,
		nullptr,
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		Color,
		1.f,
		0);
#pragma endregion

	m_pGraphicDev->BeginScene();
}

void CGraphicDev::Render_End(HWND hWindow)
{
	m_pGraphicDev->EndScene();
	m_pGraphicDev->Present(NULL, NULL, hWindow, NULL);
}