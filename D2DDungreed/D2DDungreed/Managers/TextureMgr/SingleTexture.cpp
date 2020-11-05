#include "stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
	: m_pTexInfo(nullptr)
{
	AssertMember();
}


CSingleTexture::~CSingleTexture()
{
	Release();
	AssertMember();
}

const TEX_INFO* CSingleTexture::GetTexInfo(
	const std::wstring& wstrStateKey/* = L""*/,
	const WORD&			wIndex/* = 0*/) const
{
	wstrStateKey;
	wIndex;
	return m_pTexInfo;
}

HRESULT CSingleTexture::LoadTexture(
	LPDIRECT3DDEVICE9		pGraphicDev,
	const std::wstring&		wstrFilePath,
	const std::wstring&		wstrStateKey/* = L""*/,
	const WORD&				wCnt/* = 0*/)
{
	wstrStateKey;
	wCnt;
	// Direct3D 이미지 정보 구조체.
	D3DXIMAGE_INFO	tImgInfo{};
	assert(tImgInfo.Depth			== 0);
	assert(tImgInfo.Format			== 0);
	assert(tImgInfo.Height			== 0);
	assert(tImgInfo.ImageFileFormat == 0);
	assert(tImgInfo.MipLevels		== 0);
	assert(tImgInfo.ResourceType	== 0);
	assert(tImgInfo.Width			== 0);

	HRESULT	hr = D3DXGetImageInfoFromFile(
		wstrFilePath.c_str(),
		&tImgInfo
	);
	assert(NO_ERROR == hr);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	// Direct3D 텍스쳐를 만들어 저장.
	LPDIRECT3DTEXTURE9	pTexture = nullptr;

	hr = D3DXCreateTextureFromFileEx(
		pGraphicDev,
		wstrFilePath.c_str(),
		tImgInfo.Width,
		tImgInfo.Height,
		tImgInfo.MipLevels,
		0,
		tImgInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		&pTexture
	);
	assert(NOERROR == hr);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	m_pTexInfo = new TEX_INFO;
	m_pTexInfo->pTexture = pTexture;
	m_pTexInfo->tImgInfo = tImgInfo;

	return S_OK;
}

CSingleTexture * CSingleTexture::Create(
	LPDIRECT3DDEVICE9		pGraphicDev,
	const std::wstring&		wstrFilePath,
	const std::wstring&		wstrStateKey,
	const WORD&				wCnt)
{
	// 싱글 텍스쳐 가져오기.
	CSingleTexture*	pInstance = new CSingleTexture;

	if (FAILED(pInstance->LoadTexture(
		pGraphicDev,
		wstrFilePath,
		wstrStateKey,
		wCnt)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CSingleTexture::Release()
{
	if (m_pTexInfo->pTexture)
	{
		m_pTexInfo->pTexture->Release();
	}
	SafeDelete(m_pTexInfo);
}

void CSingleTexture::AssertMember() const
{
	assert(nullptr == m_pTexInfo);
}
