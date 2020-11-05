#include "stdafx.h"
#include "MultiTexture.h"


CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
	assert(0 == m_mapMulti.size());
}

const TEX_INFO * CMultiTexture::GetTexInfo(
	const std::wstring& wstrStateKey/* = L""*/, 
	const WORD&			wIndex/* = 0*/) const
{
	auto iter_find = m_mapMulti.find(wstrStateKey);

	// 상태 키에 따른 텍스쳐 정보가 없을 경우
	if (m_mapMulti.end() == iter_find)
	{
		return nullptr;
	}

	// 요구된 인덱스 사이즈가 실제 사이즈보다 클 경우
	if (iter_find->second.size() <= wIndex)
	{
		return nullptr;
	}

	return iter_find->second[wIndex];
}

HRESULT CMultiTexture::LoadTexture(
	LPDIRECT3DDEVICE9	pGraphicDev, 
	const std::wstring& wstrFilePath, 
	const std::wstring& wstrStateKey/* = L""*/, 
	const WORD&			wCnt/* = 0*/)
{
	auto iter_find = m_mapMulti.find(wstrStateKey);

	// 이미 갖고있는 경우.
	if (m_mapMulti.end() != iter_find)
	{
		return E_FAIL;
	}

	D3DXIMAGE_INFO		tImgInfo{};
	ZeroMemory(&tImgInfo, sizeof(D3DXIMAGE_INFO));

	LPDIRECT3DTEXTURE9	pTexture	= nullptr;
	HRESULT				hr			= 0;
	
	assert(nullptr == pTexture);
	assert(NOERROR == hr);

	TCHAR szFullPath[MAX_STR]{};

	TEX_INFO* pTexInfo = nullptr;
	assert(nullptr == pTexInfo);

	for (WORD i = 0; i < wCnt; ++i)
	{
		::swprintf_s(szFullPath, wstrFilePath.c_str(), i);

		// 이미지 정보 얻어오는 함수.
		hr = D3DXGetImageInfoFromFile(szFullPath, &tImgInfo);
		assert(NOERROR == hr);
		FAILED_CHECK_RETURN(hr, E_FAIL);

		// 텍스처 Com객체 생성 함수
		hr = D3DXCreateTextureFromFileEx(
			pGraphicDev, /* 장치 */
			szFullPath, /* 텍스처 경로 */
			tImgInfo.Width, /* 생성할 텍스처 가로 크기 */
			tImgInfo.Height, /* 생성할 텍스처 세로 크기 */
			tImgInfo.MipLevels,
			0,
			tImgInfo.Format,
			D3DPOOL_MANAGED, /* 메모리 보관 방식 */
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			nullptr,
			nullptr,
			&pTexture);
		assert(NOERROR == hr);
		FAILED_CHECK_RETURN(hr, E_FAIL);

		pTexInfo = new TEX_INFO;
		pTexInfo->pTexture = pTexture;
		pTexInfo->tImgInfo = tImgInfo;

		m_mapMulti[wstrStateKey].push_back(pTexInfo);
	}

	return S_OK;
}

CMultiTexture * CMultiTexture::Create(
	LPDIRECT3DDEVICE9	pGraphicDev, 
	const std::wstring& wstrFilePath, 
	const std::wstring& wstrStateKey, 
	const WORD&			wCnt)
{
	CMultiTexture*	pInstance = new CMultiTexture;

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

void CMultiTexture::Release()
{
	int textureRelease = 0;
	for (auto& MyPair : m_mapMulti)
	{
		for (auto& pTexInfo : MyPair.second)
		{
			textureRelease = pTexInfo->pTexture->Release();
			assert(0 == textureRelease);
			SafeDelete(pTexInfo);
			assert(nullptr == pTexInfo);
		}

		MyPair.second.clear();
		assert(0 == MyPair.second.size());
	}

	m_mapMulti.clear();
}
