#ifndef __DIRECT_MGR_H__
#define __DIRECT_MGR_H__

class CDirectMgr
{
	DECLARE_SINGLETON(CDirectMgr)

private:
	CDirectMgr();
	~CDirectMgr();

public:
	LPDIRECT3DDEVICE9 GetDevice	() const { return m_pGraphicDev; }
	LPD3DXSPRITE GetSprite		() const { return m_pSprite; }
	LPD3DXLINE GetLine			() const { return m_pLine; }

	HRESULT				InitDevice(DISPLAY_MODE eMode);
	void				Render_Begin();
	void				Render_End(HWND	hWnd = nullptr);
	void				Release();

	void				RenderImage
	(
		const TEX_INFO*		pTexInfo,
		const D3DXMATRIX&	matWorld,
		const int			colorARGB
	);

	void RenderRect
	(
		const RECT& rc, 
		const int	iColor = D3DCOLOR_ARGB(255, 0, 0, 0),
		const bool	bScroll = true
	) const;

	void RenderFont
	(
		const D3DXVECTOR3&	vecPos, 
		const std::wstring& m_wStr, 
		const int			iColor
	);

	void SetHwnd(HWND hWnd)
	{
		m_hWnd = hWnd;
	}
	void SetHeight(int iHeight)
	{
		m_iHeight = iHeight;
	}
	void SetWidth(int iWidth)
	{
		m_iWidth = iWidth;
	}
	void SetBackColor(int iColor)
	{
		m_iColorValue = iColor;
	}

private:
	void AssertMember();

	HRESULT InitializeDevice	(DISPLAY_MODE eMode);
	HRESULT InitializeSprite	();
	HRESULT InitializeFont		();
	HRESULT InitializeCOMDevice	();
	HRESULT InitializeLine		();

private:
	LPDIRECT3D9			m_pSDK;
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	LPD3DXSPRITE		m_pSprite;
	LPD3DXFONT			m_pFont;
	LPD3DXLINE			m_pLine;

	int					m_iHeight;
	int					m_iWidth;
	int					m_iColorValue;

	HWND				m_hWnd;
};

#endif // !__DIRECT_MGR_H__
