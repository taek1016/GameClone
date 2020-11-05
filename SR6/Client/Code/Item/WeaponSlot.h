#ifndef InventorySlot_h__
#define InventorySlot_h__

#include "GameObject.h"
#include "ItemBase.h"

class Engine::CItemBase;

class CWeaponSlot : public Engine::CGameObject
{
private:
	explicit						CWeaponSlot(void);
	explicit						CWeaponSlot(const CWeaponSlot& rhs);
	virtual							~CWeaponSlot(void);

public:
	virtual HRESULT					Late_Initialize() override;
	virtual HRESULT					Initialize_GameObject() override;
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

	Engine::CItemBase*				Get_Item(void) { return m_pItem; }
	void							Set_Item(Engine::CItemBase* pItem);
	void							Deactivate_Slot(void) { m_bSelected = false; }
	void							Activate_Slot(void);

private:
	void							Set_Pos(const Engine::_vec3* pPos);

	Engine::_bool					m_bSelected = false;
	wstring							m_wStrRenderKey;
	Engine::_int					m_iRenderIdx = 0;
	RECT							m_tRect;

	Engine::CItemBase*				m_pItem = nullptr;
	Engine::CTransform*				m_pTransform = nullptr;
	Engine::CTexture*				m_pTexture = nullptr;

public:
	static CWeaponSlot*				Create(const Engine::_vec3* pPos, Engine::CItemBase* pItem);
	virtual Engine::CGameObject*	Clone(const Engine::_vec3* pPos = nullptr) override;

private:
	inline virtual void				freeMem(void) override;
	virtual void					LoadData(HANDLE hFile) override { ; }
};

#endif // InventorySlot_h__