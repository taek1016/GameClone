#ifndef Sphere_h__
#define Sphere_h__

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CSphereCollider : public CCollider
{
protected:
	explicit		CSphereCollider(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit		CSphereCollider(const CSphereCollider& rhs);
	virtual			~CSphereCollider(void);

public:
	const _vec3*	Get_CenterPos(void);
	const _float*	Get_Radius(void) const;

	HRESULT			Initialize_Collider(const _float& fRadius, const _ulong & dwSlice, const _ulong & dwStack,
		const _matrix* pWorld, const _matrix* pBone = nullptr, const _vec3* pPos = nullptr);

	void			Set_Collider(const _matrix * pWorld, const _matrix * pBone = nullptr, const _vec3 * pPos = nullptr);

protected:
	_vec3			m_vCenterPos;
	_float			m_fRadius;

public:
	static CSphereCollider*	Create(LPDIRECT3DDEVICE9 pGraphicDev, 
									const _float& fRadius, 
									const _ulong & dwSlice, 
									const _ulong & dwStack, 
									const _matrix* pWorld, 
									const _matrix* pBone = nullptr,
									const _vec3* pPos = nullptr);
	virtual CComponent*		Clone(void) override;
};
END

#endif // Sphere_h__
