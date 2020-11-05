#ifndef Font_h__
#define Font_h__

#include "GameObject.h"

class CFont : public Engine::CGameObject
{
private:
	explicit										CFont(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual											~CFont(void) = default;

public:
	virtual HRESULT									Initialize_GameObject(void) override;
	virtual HRESULT									Late_Initialize(void) override;
	virtual Engine::_int							Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void									Render_GameObject(void) override;

	void											Add_Font(const Engine::_tchar* pKey, Engine::CTexture* pTexture);
	void											Push_FontData(const FONT_INFO& rhs);
	void											Clear_Data(void);

private:
	void											render_SingleFont(const D3DXCOLOR& tColor, Engine::CTexture* pTexture);

	Engine::CTexture*								find_Texture(const Engine::_tchar* pKey);
	HRESULT											setUp_ConstantTable(const D3DXCOLOR& tColor, Engine::CTexture * pTexture, LPD3DXEFFECT & pEffect);

	unordered_map<const Engine::_tchar*, Engine::CTexture*>	m_FontMap;
	Engine::CRcTex*									m_pBuffer;

	Engine::CShader*								m_pShader;

	vector<FONT_INFO>								m_vecTextData;

public:
	static CFont*					Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	inline virtual void				Free(void) override;
};
#endif // Font_h__
