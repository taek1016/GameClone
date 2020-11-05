#include "stdafx.h"
#include "DirectMgr.h"

IMPLEMENT_SINGLETON(CDirectMgr)

CDirectMgr::CDirectMgr()
	: m_pFont(nullptr)
	, m_pSDK(nullptr)
	, m_pGraphicDev(nullptr)
	, m_pSprite(nullptr)
	, m_pLine(nullptr)

	, m_hWnd(nullptr)
	
	, m_iHeight(0)
	, m_iWidth(0)
	, m_iColorValue(D3DCOLOR_ARGB(255, 0, 0, 0))
{
	AssertMember();
}

CDirectMgr::~CDirectMgr()
{
	Release();
	AssertMember();
}

HRESULT CDirectMgr::InitDevice(DISPLAY_MODE eMode)
{
	FAILED_CHECK_RETURN(InitializeCOMDevice(), E_FAIL);

	// 그래픽에서 장치 생성하기
	FAILED_CHECK_RETURN(InitializeDevice(eMode), E_FAIL);

	// 스프라이트 생성
	FAILED_CHECK_RETURN(InitializeSprite(), E_FAIL);

	// 폰트 생성하기
	FAILED_CHECK_RETURN(InitializeFont(), E_FAIL);

	// 라인 생성하기
	FAILED_CHECK_RETURN(InitializeLine(), E_FAIL);

	return S_OK;
}

void CDirectMgr::Render_Begin()
{
	// 후면버퍼 비우기.
	m_pGraphicDev->Clear(
		0,
		nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		m_iColorValue,
		1.f,
		0
	);

	// 후면 버퍼에 그리기 시작.
	m_pGraphicDev->BeginScene();

	// 스프라이트 그리기 시작.
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDirectMgr::Render_End(HWND hWnd/* = nullptr*/)
{
	m_pSprite->End();

	m_pGraphicDev->EndScene();

	m_pGraphicDev->Present(nullptr, nullptr, hWnd, nullptr);
}

void CDirectMgr::Release()
{
	m_pLine->Release();
	m_pFont->Release();
	m_pSprite->Release();
	m_pGraphicDev->Release();
	m_pSDK->Release();

	m_pLine = nullptr;
	m_pFont = nullptr;
	m_pSprite = nullptr;
	m_pGraphicDev = nullptr;
	m_pSDK = nullptr;
	m_hWnd = nullptr;

	AssertMember();
}

void CDirectMgr::RenderImage
(
	const TEX_INFO*		pTexInfo,
	const D3DXMATRIX&	matWorld,
	const int			colorARGB
)
{
	D3DXVECTOR3	vecCenter{ pTexInfo->tImgInfo.Width TO_HALF, pTexInfo->tImgInfo.Height TO_HALF, 0.f };
	m_pSprite->SetTransform(&matWorld);

	m_pSprite->Draw
	(
		pTexInfo->pTexture,
		nullptr,
		&vecCenter,
		nullptr,
		colorARGB
	);
}

void CDirectMgr::RenderRect
(
	const RECT& rc,
	const int	iColor, 
	const bool	bScroll
) const
{
	m_pSprite->End();
	
	D3DXVECTOR2	Line[5]{};

	if (bScroll)
	{
		const D3DXVECTOR3& cameraPos = CSINGLETON::pCameraMgr->GetPos();
		Line[0] = { static_cast<FLOAT>(rc.left - cameraPos.x),	static_cast<FLOAT>(rc.top - cameraPos.y) };
		Line[1] = { static_cast<FLOAT>(rc.right - cameraPos.x),	static_cast<FLOAT>(rc.top - cameraPos.y) };
		Line[2] = { static_cast<FLOAT>(rc.right - cameraPos.x),	static_cast<FLOAT>(rc.bottom - cameraPos.y) };
		Line[3] = { static_cast<FLOAT>(rc.left - cameraPos.x),	static_cast<FLOAT>(rc.bottom - cameraPos.y) };
		Line[4] = { static_cast<FLOAT>(rc.left - cameraPos.x),	static_cast<FLOAT>(rc.top - cameraPos.y) };
	}
	else
	{
		Line[0] = { static_cast<FLOAT>(rc.left),	static_cast<FLOAT>(rc.top) };
		Line[1] = { static_cast<FLOAT>(rc.right),	static_cast<FLOAT>(rc.top) };
		Line[2] = { static_cast<FLOAT>(rc.right),	static_cast<FLOAT>(rc.bottom) };
		Line[3] = { static_cast<FLOAT>(rc.left),	static_cast<FLOAT>(rc.bottom) };
		Line[4] = { static_cast<FLOAT>(rc.left),	static_cast<FLOAT>(rc.top) };
	}
	m_pLine->SetWidth(2.f);
	HRESULT hr = m_pLine->Draw(
		Line,
		5,
		iColor
	);
	assert(NO_ERROR == hr);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDirectMgr::RenderFont(const D3DXVECTOR3& vecPos, const std::wstring& m_wStr, const int iColor)
{
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, vecPos.x, vecPos.y, vecPos.z);

	m_pSprite->SetTransform(&matTrans);

	m_pFont->DrawText(
		CSINGLETON::pDirectMgr->GetSprite(), /* 스프라이트 COM 객체 */
		m_wStr.c_str(), /* 출력할 문자열 */
		m_wStr.length(), /* 문자열 길이 */
		nullptr, /* 사각형 영역 */
		0,
		iColor);
}

void CDirectMgr::AssertMember()
{
	assert(nullptr == m_pSDK);
	assert(nullptr == m_pGraphicDev);
	assert(nullptr == m_pSprite);
	assert(nullptr == m_pFont);
	assert(nullptr == m_pLine);
	assert(nullptr == m_hWnd);
}

HRESULT CDirectMgr::InitializeDevice(DISPLAY_MODE eMode)
{
	D3DCAPS9	d3dcaps{};
	ZeroMemory(&d3dcaps, sizeof(D3DCAPS9));


	HRESULT	hr = m_pSDK->GetDeviceCaps(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		&d3dcaps);
	assert(NOERROR == hr);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	DWORD	vp = 0;

	if (d3dcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}	
	
	vp |= D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS	d3dpp{};
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = m_iWidth;
	d3dpp.BackBufferHeight = m_iHeight;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = m_hWnd;
	d3dpp.Windowed = eMode;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	hr = m_pSDK->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWnd,
		vp,
		&d3dpp,
		&m_pGraphicDev);

	assert(NOERROR == hr);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	return S_OK;
}

HRESULT CDirectMgr::InitializeSprite()
{
	HRESULT hr = D3DXCreateSprite(m_pGraphicDev, &m_pSprite);
	assert(NOERROR == hr);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	return S_OK;
}

HRESULT CDirectMgr::InitializeFont()
{
	D3DXFONT_DESC	tFontInfo{};
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESC));

	tFontInfo.Width = 10;
	tFontInfo.Height = 20;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"consolas");

	// 폰트 생성
	HRESULT hr = D3DXCreateFontIndirect(m_pGraphicDev, &tFontInfo, &m_pFont);
	assert(NOERROR == hr);
	FAILED_CHECK_RETURN(hr, E_FAIL);
	return S_OK;
}

HRESULT CDirectMgr::InitializeCOMDevice()
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	assert(nullptr != m_pSDK);
	NULL_CHECK_RETURN(m_pSDK, E_FAIL);

	return S_OK;
}

HRESULT CDirectMgr::InitializeLine()
{
	HRESULT hr = D3DXCreateLine(CDirectMgr::GetDevice(), &m_pLine);
	assert(nullptr != m_pLine);
	assert(NOERROR == hr);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	m_pLine->SetWidth(2.f);
	return S_OK;
}