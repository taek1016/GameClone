#ifndef GameObject_h__
#define GameObject_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CComponent;

class CTransform;

class ENGINE_DLL CGameObject : public CBase
{
protected:
	explicit							CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit							CGameObject(const CGameObject& rhs);
	virtual								~CGameObject(void);

public:
	_float								Get_ViewZ(void) const;

	CComponent*							Add_Component(const _tchar* pComponentTag, CComponent* pComponent, COMPONENTID eID);

	template<typename T>
	T* Get_Component(const _tchar* pComponentTag, COMPONENTID eID)
	{
		auto iter = find_Component(pComponentTag, eID);

		if (nullptr == iter)
		{
			return nullptr;
		}

		return dynamic_cast<T*>(iter);
	}

	virtual HRESULT								Initialize_GameObject(void) { return S_OK; }
	virtual HRESULT								Late_Initialize(void) { return S_OK; }

	virtual _int								Update_GameObject(const _float& fTimeDelta);
	virtual void								Render_GameObject(void);

	virtual void								Set_Initialze(void) {};
	void										Set_Pos(const _vec3* pPos);
	void										Set_Look(const _vec3* pLook);
	void										Set_Scale(const _vec3* pScale);
	void										Set_Rotation(ROTATION eRot, const _float& fAngle);

	void										Compute_ViewZ(void);

	const _tchar*								Get_Name(void) const;
	const _vec3*								Get_Pos(void);

	virtual const _vec3*						Get_CenterPos(void);

	virtual Engine::_bool						skill_Act(void) { return false; };
	virtual Engine::_bool						attack_Act(void) { return false; };

protected:
	void										set_Name(const Engine::_tchar* pName);
	CComponent*									find_Component(const _tchar* pComponentTag, COMPONENTID eID);

	// 순서를 지키면서 태그를 활용하기 위해서 list와 pair를 조합.
	list<pair<const _tchar*, CComponent*>>		m_listComponent[ID_END];
	LPDIRECT3DDEVICE9							m_pGraphicDev;

	wstring										m_wStrName;

	CTransform*									m_pTransform;

	_float										m_fViewZ;

public:
	virtual CGameObject*						Clone(void) { return nullptr; }

protected:
	inline virtual void							Free(void);
};

END
#endif // GameObject_h__
