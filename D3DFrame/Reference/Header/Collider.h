#ifndef Collider_h__
#define Collider_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CCollider : public CComponent
{
protected:
	explicit					CCollider(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit					CCollider(const CCollider& rhs);
	virtual						~CCollider(void);

public:
	const _matrix*				Get_ColliderMatrix(void) { return &m_matWorld; }

	virtual void				Render_Collider(COLLTYPE eType);
	virtual void				Render_Collider(COLLTYPE eType, const _matrix* pMatrix);

protected:
	void						set_Material(void);
	void						set_Texture(void);

	_matrix						m_matWorld;
	_matrix						m_matPosition;

	LPD3DXMESH					m_pMesh;
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	LPDIRECT3DTEXTURE9			m_pTexture[COL_END];

	D3DMATERIAL9				m_Material[COL_END];

	const _matrix*				m_pWorld;
	const _matrix*				m_pBone;

public:
	virtual CComponent*			Clone(void) override PURE;

private:
	virtual void				Free(void) override;
};

END
#endif // Collider_h__