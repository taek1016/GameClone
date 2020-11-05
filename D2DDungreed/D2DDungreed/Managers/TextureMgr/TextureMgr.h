#ifndef __TEXTURE_MGR_H__
#define	__TEXTURE_MGR_H__

class CTexture;
class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)

private:
	CTextureMgr();
	~CTextureMgr();

public:
	const	TEX_INFO*	GetTexInfo(
		const	std::wstring&	wstrObjectKey,
		const	std::wstring&	wstrStateKey = L"",
		const	WORD&			wCnt = 0
	) const;

	HRESULT	LoadTexture(
		LPDIRECT3DDEVICE9		pGraphic,
		TEXTURE_TYPE			eTextureType,
		const	std::wstring&	wstrFilePath,
		const	std::wstring&	wstrObjectKey,
		const	std::wstring &	wstrStateKey = L"",
		const	WORD&			wCnt = 0
	);

	HRESULT LoadTextrueFromPathInfo
	(
		LPDIRECT3DDEVICE9		pGraphic,
		const std::wstring&		wstrFilePath
	);

private:
	void Release();

private:
	std::unordered_map<std::wstring, CTexture*>	m_mapTexture;
};

#endif // !__TEXTURE_MGR_H__