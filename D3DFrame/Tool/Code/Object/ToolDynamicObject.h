#ifndef ToolDynamicObject_h__
#define ToolDynamicObject_h__

#include "Engine_Defines.h"
#include "Object/ToolGameObject.h"
#include "Sphere.h"
#include "BoxCollider.h"
#include "ActionComponent.h"

class CToolDynamicObject : public CToolGameObject
{
protected:
	explicit					CToolDynamicObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit					CToolDynamicObject(const CToolDynamicObject& rhs);
	virtual						~CToolDynamicObject(void);

public:
	virtual HRESULT				Initialize_GameObject(void);
	virtual HRESULT				Late_Initialize(void);

	virtual Engine::_int		Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void				Render_GameObject(void);

	Engine::CDynamicMesh*		Get_DynamicMesh(void);

	void						Play_Animation(const Engine::_tchar* pKey);

	void						Set_RenderKey(const Engine::_tchar* pKey);

	const wstring&				Get_RenderKey(void) const;

	const map<wstring, const Engine::_int>*	Get_AnimationKey(void) const;
	const list<wstring>*					Get_BoneList(void) const;

	const wstring&				Get_ColliderBoneName(void) const;
	void						Set_ColliderBoneName(const Engine::_tchar* pKey);

	const map<wstring, Engine::CActionCom*>*	Get_ActionMap(void) const;
	void						Add_ActionCol(const Engine::_tchar* pName, const Engine::_float& fCoolTime, const Engine::_float& fRadius);
	void						Add_SphereCollider(const Engine::_float& fRadius);
	void						Delete_ActionCol(const Engine::_tchar* pName);

private: 
	HRESULT						SetUp_ConstantTable(LPD3DXEFFECT & pEffect);

	void						initialize_Bones(void);
	void						initialize_Animation(void);

	Engine::CDynamicMesh*		m_pMesh;
	wstring						m_wStrRenderKey;
	wstring						m_wStrColliderBoneName;

	list<wstring>							m_BoneList;
	map<wstring, const Engine::_int>		m_mapAnimationIndexMap;

	Engine::CSphereCollider*				m_pSphereCollider;

	map<wstring, Engine::CActionCom*>		m_mapActionCol;

	Engine::CShader*						m_pShaderCom;
public:
	static CToolDynamicObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar* pKey);
	virtual CGameObject*		Clone(void);
	virtual void				SaveData(HANDLE hFile);
	virtual void				LoadData(HANDLE hFile);

private:
	inline virtual void			Free(void) override;

};
#endif // ToolDynamicObject_h__
