#ifndef FieldSkybox_h__
#define FieldSkybox_h__

#include "SkyboxBase.h"

class CFieldSkybox : public CSkyBox
{
private:
	explicit						CFieldSkybox(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CFieldSkybox(const CFieldSkybox& rhs);
	virtual							~CFieldSkybox(void) = default;

public:
	static CFieldSkybox*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // FieldSkybox_h__
