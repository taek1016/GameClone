#ifndef Sphere_h__
#define Sphere_h__

#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CSphere : public CCollider
{
private:
	explicit		CSphere(void);
	explicit		CSphere(const CSphere& rhs);
	virtual			~CSphere(void);

public:
	virtual HRESULT		Initialize_Component() override;
	virtual void		Render_Collider();

	virtual bool		Is_Collide(CCollider* pOther, _float* pDistance = nullptr);

private:
	void				Set_Radius(const _float& fRadius)
	{
		m_fRadius = fRadius;
	}

	_bool				m_bCollide = false;

	_float				m_fRadius = 0.f;

	LPD3DXBUFFER		m_pBuffer = nullptr;
	LPD3DXMESH			m_pMesh = nullptr;

public:
	static CSphere*		Create(const _float& fRadius);
	virtual CComponent*	Clone(void);

private:
	inline virtual void	freeMem();
};

END
#endif // Sphere_h__
