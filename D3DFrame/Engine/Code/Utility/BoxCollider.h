#ifndef BoxCollider_h__
#define BoxCollider_h__

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CBoxCollider : public Engine::CCollider
{
private:
	explicit					CBoxCollider(LPDIRECT3DDEVICE9 pGraphic);
	explicit					CBoxCollider(const CBoxCollider& rhs);
	virtual						~CBoxCollider(void);

public:
	const _vec3*				Get_Min(void) { return &m_vMin; }
	const _vec3*				Get_Max(void) { return &m_vMax; }
	
	HRESULT						Initialize_Collider(const _float& fWidth, const _float& fHeight, const _float& fDepth);
	HRESULT						Initialize_Collider(const _vec3* pPos, const _ulong& dwNumVtx, const _ulong& dwStride);

private:
	_vec3						m_vMin, m_vMax;

public:
	static CBoxCollider*		Create(LPDIRECT3DDEVICE9 pGraphicDev,
		const _float& fWidth, const _float& fHeight, const _float& fDepth);
	virtual CComponent*			Clone(void);
};
END

#endif // BoxCollider_h__
