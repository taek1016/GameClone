#ifndef ActionComponent_h__
#define ActionComponent_h__

#include "Sphere.h"

BEGIN(Engine)
class ENGINE_DLL CActionCom : public CSphereCollider
{
private:
	explicit				CActionCom(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar* pName, const _float& fCoolTime);
	explicit				CActionCom(const CActionCom& rhs);
	virtual					~CActionCom(void);

public:
	virtual HRESULT			Initialize_Collider(const _float& fRadius, const _ulong & dwSlice, const _ulong & dwStack, const _matrix* pWorld);

	virtual _int			Update_Component(const _float& fTimeDelta) override;
	const _bool				Can_Act(void);
	void					Reset_Act(void);
	const _float*			Get_CoolTime(void) const;
	const _tchar*			Get_Name(void) const;

private:
	_bool					m_bCanAction;
	_float					m_fCurTime;
	_float					m_fCoolTime;
	wstring					m_wStrActionName;

public:
	static CActionCom*		Create(LPDIRECT3DDEVICE9 pGraphicDev,
									const Engine::_tchar* pName,
									const _float& fCoolTime,
									const _float& fRadius,
									const _ulong& dwSlice,
									const _ulong& dwStack,
									const _matrix* pWorld);

	virtual CComponent*		Clone(void) override;
};
END

#endif // ActionComponent_h__
