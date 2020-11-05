#ifndef __MULTI_TEXTURE_H__
#define __MULTI_TEXTURE_H__

#include "Texture.h"
class CMultiTexture : public CTexture
{
private:
	CMultiTexture();

public:
	virtual ~CMultiTexture();

public:
	// CTexture을(를) 통해 상속됨
	virtual const TEX_INFO * GetTexInfo(
		const std::wstring& wstrStateKey = L"", 
		const WORD&			wIndex = 0) const override;

	virtual HRESULT LoadTexture(
		LPDIRECT3DDEVICE9	pGraphicDev, 
		const std::wstring& wstrFilePath, 
		const std::wstring& wstrStateKey = L"", 
		const WORD&			wCnt = 0) override;

	static CMultiTexture*	Create(
		LPDIRECT3DDEVICE9	pGraphicDev,
		const std::wstring&	wstrFilePath,
		const std::wstring& wstrStateKey,
		const WORD&			wCnt);

private:
	virtual void Release() override;

private:
	std::unordered_map<std::wstring, std::vector<TEX_INFO*>> m_mapMulti;
};

#endif // !__MULTI_TEXTURE_H__