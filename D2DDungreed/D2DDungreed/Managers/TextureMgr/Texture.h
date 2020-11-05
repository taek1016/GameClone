#ifndef __TEXTURE_H__
#define	__TEXTURE_H__

class CTexture
{
protected:
	CTexture();

public:
	virtual ~CTexture();

public:
	virtual const TEX_INFO*	GetTexInfo(
		const std::wstring&	wstrStateKey = L"",
		const WORD&			wIndex = 0
	) const PURE;

	virtual	HRESULT	LoadTexture(
		LPDIRECT3DDEVICE9		pGraphicDev,
		const	std::wstring&	wstrFilePath,
		const	std::wstring&	wstrStateKey = L"",
		const	WORD&			wCnt = 0
	) PURE;

	virtual void Release() PURE;
};

#endif // !__TEXTURE_H__