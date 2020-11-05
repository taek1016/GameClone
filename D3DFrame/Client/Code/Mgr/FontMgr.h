#ifndef FontMgr_h__
#define FontMgr_h__

#include "Base.h"

class CFont;

class CFontMgr : public CBase
{
	DECLARE_SINGLETON(CFontMgr)
private:
	explicit				CFontMgr(void);
	virtual					~CFontMgr(void);

public:
	void					Update_Font(const Engine::_float& fTimeDelta);
	void					Add_SingleFont(const Engine::_tchar* pFontType, 
											const Engine::_tchar* pKey,
											Engine::CTexture* pTexture);

	void					Create_Font(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar* pKey);
	void					Activate_Font(const Engine::_tchar* pKey);
	void					Print_Font(const Engine::_vec3* pPos, const Engine::_vec3* pScale,
										const Engine::_int& _iLinePerCount, const Engine::_tchar* pText,
										const D3DXCOLOR& _tColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

private:
	CFont*					find_Font(const Engine::_tchar* pKey);

	map<wstring, CFont*>	m_Font;
	wstring					m_wstrActivateKey;

private:
	inline virtual void		Free(void) override;
};
#endif // FontMgr_h__
