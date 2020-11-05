#ifndef InstallSlot_h__
#define InstallSlot_h__

#include "GameObject.h"
#include "ItemBase.h"

class Engine::CItemBase;

class CInstallSlot : public Engine::CGameObject
{
private:
	explicit						CInstallSlot(void);
	explicit						CInstallSlot(const CInstallSlot& rhs);
	virtual							~CInstallSlot(void);

public:
	virtual HRESULT					Late_Initialize() override;
	virtual HRESULT					Initialize_GameObject() override;
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

	void							Add_Install(CGameObject* pObj);
	CGameObject*					Get_Install(void);
private:
	void							Set_Type(const INSTALL_TYPE& eType);
	void							Set_Pos(const Engine::_vec3* pPos);

	list<CGameObject*>				m_installList;
	wstring							m_wStrRenderKey;
	Engine::_int					m_iRenderIdx = 0;
	RECT							m_tRect;
	INSTALL_TYPE					m_eType;

	Engine::_int					m_iCurItem = 0;
	_matrix							m_matNumWorld;
	Engine::CTexture*				m_pNumTexture = nullptr;

	Engine::CTransform*				m_pTransform = nullptr;
	Engine::CTexture*				m_pTexture = nullptr;

public:
	static CInstallSlot*			Create(const Engine::_vec3* pPos, const INSTALL_TYPE& eType);
	virtual Engine::CGameObject*	Clone(const Engine::_vec3* pPos = nullptr) override;

private:
	virtual void					LoadData(HANDLE hFile) override { ; }
};

#endif // InstallSlot_h__