#ifndef Scene_h__
#define Scene_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CScene : public CBase
{
protected:
	explicit			CScene(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CScene(void);

public:
	virtual HRESULT		Initialize_Scene(void) PURE;
	virtual _int		Update_Scene(const _float& fTimeDelta) PURE;
	virtual void		Render_Scene(void)	PURE;

protected:
	LPDIRECT3DDEVICE9	m_pGraphicDev;

protected:
	inline virtual void	Free(void) override;
};

END
#endif // Scene_h__
