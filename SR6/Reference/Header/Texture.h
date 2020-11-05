#ifndef Texture_h__
#define Texture_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CTexture : public CResources
{
protected:
	explicit							CTexture(void);
	explicit							CTexture(const CTexture& rhs);
	virtual								~CTexture(void);

public:
	HRESULT								Initialize_Texture(const _tchar* pPath, TEXTURETYPE eType, const _uint& iCnt = 1);
	void								Render_Texture(const _uint& iIndex = 0);

private:
	vector<IDirect3DBaseTexture9*>		m_vecTexture;

public:
	static CTexture*					Create(const _tchar* pPath,
												TEXTURETYPE eType,
												const _uint& iCnt = 1);

	virtual CResources*					Clone(void);
	virtual HRESULT						Attach(CGameObject* pObj, COMPONENTID com_ID);

private:
	inline virtual void					freeMem(void) override;

};

END
#endif // Texture_h__
