#ifndef GraphicDev_h__
#define GraphicDev_h__

#include "Base.h"
#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CGraphicDev : public CBase
{
	DECLARE_SINGLETON(CGraphicDev)

private:
	explicit	CGraphicDev(void);
	virtual		~CGraphicDev(void);

public:
	LPDIRECT3DDEVICE9		GetDevice(void)			{ return m_pGraphicDev; }
	LPD3DXSPRITE			GetSprite(void)			{ return m_pSprite; }
	LPD3DXLINE				GetLine(void)			{ return m_pLine; }

	void					GetScreenData(_float* pScreenX, _float* pScreenY);

public:
	HRESULT					Initialize_GraphicDev(HWND hWnd,
													WINMODE eMode,
													const _uint& iSizeX,
													const _uint& iSizeY);

	void					Render_Begin(D3DXCOLOR Color);
	void					Render_End(HWND hWindow = nullptr);

private:
	HRESULT					initialize_SDK();
	HRESULT					initialize_Device(HWND hWnd,
												WINMODE eMode,
												const _uint& iSizeX,
												const _uint& iSizeY);
	HRESULT					initialize_Line(void);

	LPDIRECT3D9				m_pSDK = nullptr;
	LPDIRECT3DDEVICE9		m_pGraphicDev = nullptr;
	LPD3DXSPRITE			m_pSprite = nullptr;
	LPD3DXFONT				m_pFont = nullptr;
	LPD3DXLINE				m_pLine = nullptr;

	_float					m_fScreenX;
	_float					m_fScreenY;

public:
	inline	virtual void	Free(void);
};

END

#endif // GraphicDev_h__
