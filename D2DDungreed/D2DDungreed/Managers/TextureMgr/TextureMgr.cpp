#include "stdafx.h"
#include "Texture.h"
#include "SingleTexture.h"
#include "MultiTexture.h"
#include "TextureMgr.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
	: m_mapTexture{}
{
}

CTextureMgr::~CTextureMgr()
{
	Release();
	assert(0 == m_mapTexture.size());
}

const TEX_INFO * CTextureMgr::GetTexInfo(
	const std::wstring& wstrObjectKey, 
	const std::wstring& wstrStateKey, 
	const WORD&			wIndex) const
{
	auto iter_find = m_mapTexture.find(wstrObjectKey);

	if (m_mapTexture.end() == iter_find)	// 찾지 못했을 때
	{
		return nullptr;
	}
	return iter_find->second->GetTexInfo(wstrStateKey, wIndex);
}

HRESULT CTextureMgr::LoadTexture(
	LPDIRECT3DDEVICE9		pGraphic,
	TEXTURE_TYPE			eTextureType,
	const std::wstring&		wstrFilePath,
	const std::wstring&		wstrObjectKey,
	const std::wstring&		wstrStateKey,
	const WORD&				wCnt)
{
	CTexture*	pTexture = nullptr;
	assert(nullptr == pTexture);

	auto iter_find = m_mapTexture.find(wstrObjectKey);

	if (m_mapTexture.end() == iter_find)
	{
		switch (eTextureType)
		{
		case TEXTURE_SINGLE:
			pTexture = CSingleTexture::Create(pGraphic, wstrFilePath);
			break;
		case TEXTURE_MULTI:
			pTexture = CMultiTexture::Create(pGraphic, wstrFilePath, wstrStateKey, wCnt);
			break;
		}

		assert(nullptr != pTexture);
		NULL_CHECK_RETURN(pTexture, E_FAIL);
		m_mapTexture.insert(std::make_pair(wstrObjectKey, pTexture));
	}
	else
	{
		HRESULT	hr = 0;

		switch (eTextureType)
		{
		case TEXTURE_SINGLE:
			return E_FAIL;

		case TEXTURE_MULTI:
			hr	= m_mapTexture[wstrObjectKey]->LoadTexture(
				pGraphic,
				wstrFilePath,
				wstrStateKey,
				wCnt);
			assert(NOERROR == hr);
			FAILED_CHECK_RETURN(hr, E_FAIL);
			break;
		}
	}
	return S_OK;
}

HRESULT CTextureMgr::LoadTextrueFromPathInfo(LPDIRECT3DDEVICE9 pGraphic, const std::wstring & wstrFilePath)
{
	std::wifstream fin;

	fin.open(wstrFilePath);

	if (fin.fail())
	{
		return E_FAIL;
	}

	TCHAR	szObjectKey[MAX_STR]{};
	TCHAR	szObjectStatus[MAX_STR]{};
	TCHAR	szCount[MAX_STR]{};
	TCHAR	szRelative[MAX_STR]{};

	HRESULT hr;

	while (true)
	{
		fin.getline(szObjectKey, MAX_STR, '|');
		fin.getline(szObjectStatus, MAX_STR, '|');
		fin.getline(szCount, MAX_STR, '|');
		fin.getline(szRelative, MAX_STR);
		
		if (fin.eof())
		{
			break;
		}

		hr = LoadTexture
		(
			pGraphic,
			TEXTURE_MULTI,
			szRelative,
			szObjectKey,
			szObjectStatus,
			static_cast<WORD>(_ttoi(szCount))
		);

		if (FAILED(hr))
		{
			fin.close();
			return E_FAIL;
		}
	}

	fin.close();

	return S_OK;
}

void CTextureMgr::Release()
{
	for (auto& MyPair : m_mapTexture)
	{
		SafeDelete(MyPair.second);
	}
	m_mapTexture.clear();
}
