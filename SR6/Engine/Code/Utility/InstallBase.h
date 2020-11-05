#ifndef InstallBase_h__
#define InstallBase_h__

#include "ItemBase.h"

BEGIN(Engine)

class ENGINE_DLL CInstallBase : public CItemBase
{
protected:
	explicit	CInstallBase(void);
	explicit	CInstallBase(const CInstallBase& rhs);
	virtual		~CInstallBase(void);

public:
	virtual HRESULT		Late_Initialize() PURE;
	virtual HRESULT		Initialize_GameObject() PURE;
	virtual _int		Update_Component(const _float& fTimeDelta);

	virtual void		Install();

protected:
	_vec3				m_vPos;
	_vec3				m_vSize;

public:
	virtual CGameObject* Clone(const _vec3* pPos) PURE;

	virtual void		LoadData(HANDLE hFile) PURE;
};

END

#endif // InstallBase_h__
