#ifndef __SINGLE_TEXTURE_H__
#define __SINGLE_TEXTURE_H__

#include "Texture.h"
class CSingleTexture : public CTexture
{
private:
	CSingleTexture();

public:
	virtual ~CSingleTexture();

public:
	// CTexture을(를) 통해 상속됨
	virtual const TEX_INFO * GetTexInfo(
		const std::wstring & wstrStateKey = L"", 
		const WORD & wIndex = 0) const override;

	virtual HRESULT LoadTexture(
		LPDIRECT3DDEVICE9 pGraphicDev, 
		const std::wstring & wstrFilePath, 
		const std::wstring & wstrStateKey = L"", 
		const WORD & wCnt = 0) override;

	static CSingleTexture* Create(
		LPDIRECT3DDEVICE9	pGraphicDev,
		const std::wstring&	wstrFilePath,
		const std::wstring&	wstrStateKey = L"",
		const WORD&			wCnt = 0);

	virtual void Release() override;
	
private:
	void	AssertMember() const;

private:
	TEX_INFO*		m_pTexInfo;

};

#endif // !__SINGLE_TEXTURE_H__