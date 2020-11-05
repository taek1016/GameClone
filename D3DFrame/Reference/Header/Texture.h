#ifndef Texture_h__
#define Texture_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CTexture : public CResources
{
protected:
	explicit							CTexture(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit							CTexture(const CTexture& rhs);
	virtual								~CTexture(void);

public:
	HRESULT								Initialize_Texture(const _tchar* pPath, TEXTURETYPE eType, const _uint& iCnt = 1);
	void								Render_Texture(const _uint& iIndex = 0);
	void								Set_Texture(LPD3DXEFFECT & pEffect, const char * pShaderName, const _uint & iIndex);

	_int								Get_Height(void) const;
	_int								Get_Width(void) const;

private:
	vector<IDirect3DBaseTexture9*>		m_vecTexture;

	_int								m_iHeight;
	_int								m_iWidth;

public:
	static CTexture*					Create(LPDIRECT3DDEVICE9 pGraphicDev, 
												const _tchar* pPath,
												TEXTURETYPE eType,
												const _uint& iCnt = 1);

	virtual CResources*					Clone(void);

private:
	inline virtual void					Free(void) override;
};

END
#endif // Texture_h__
