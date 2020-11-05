#ifndef ToolStaticObject_h__
#define ToolStaticObject_h__

#include "ToolGameObject.h"
#include "Collider.h"

class Engine::CTransform;
class Engine::CComponent;

class CToolStaticObject : public CToolGameObject
{
private:
	explicit					CToolStaticObject(LPDIRECT3DDEVICE9 pGraphcDev);
	explicit					CToolStaticObject(const CToolStaticObject& rhs);
	virtual						~CToolStaticObject(void);

public:
	virtual HRESULT				Initialize_GameObject(void);
	virtual HRESULT				Late_Initialize(void);

	virtual Engine::_int		Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void				Render_GameObject(void);

	void						Add_Collider(Engine::CCollider* pCol, const Engine::_float& fRadius);
	const Engine::_float&		Get_Radius(void) const;

	const Engine::_tchar*		Get_RenderKey(void) const;

	void						Set_RenderKey(const wstring& wStrRenderKey);
	
	void						Set_Info(const OBJECT_INFO& tInfo);

	void						Move_X(const Engine::_float& fX);
	void						Move_Y(const Engine::_float& fY);
	void						Move_Z(const Engine::_float& fZ);

	void						Scale_X(const Engine::_float& fX);
	void						Scale_Y(const Engine::_float& fY);
	void						Scale_Z(const Engine::_float& fZ);

	void						Rot_X(const Engine::_float& fX);
	void						Rot_Y(const Engine::_float& fY);
	void						Rot_Z(const Engine::_float& fZ);

	void						Set_Name(const Engine::_tchar* pKey);

	const OBJECT_INFO*			Get_Info(void);

	const Engine::_vec3*		Get_Scale(void) const;
	const Engine::_vec3*		Get_Angle(void) const;

private:
	HRESULT						SetUp_ConstantTable(LPD3DXEFFECT & pEffect);

	OBJECT_INFO					m_tInfo;
	Engine::CStaticMesh*		m_pStaticMesh;
	Engine::CShader*			m_pShaderCom;

	Engine::_float				m_fRadius;

public:
	virtual void				SaveData(HANDLE hFile);
	virtual void				LoadData(HANDLE hFile) override;

	static CToolStaticObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar* pRenderKey);
	virtual CGameObject*		Clone(void) override;

private:
	inline virtual void			Free(void) override;

};
#endif // ToolStaticObject_h__
