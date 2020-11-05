#ifndef FontMgr_h__
#define FontMgr_h__
#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CFontMgr : public CBase
{
	
	DECLARE_SINGLETON(CFontMgr)

private:
	explicit									CFontMgr(void);
	virtual										~CFontMgr(void);

public:
	void										Register_Key(const _tchar cKey, const _tchar* pKeyPath);
	void										Render_FontMgr(wstring& wStr, const _float& fInterval, const _vec3* pPos = nullptr);

private:
	class CTransform*							m_pTransform = nullptr;
	LPDIRECT3DDEVICE9							m_pGraphicDev = nullptr;
	map<const _tchar, IDirect3DBaseTexture9*>	m_mapFont;

private:
	virtual void								freeMem();
};
END
#endif // FontMgr_h__
