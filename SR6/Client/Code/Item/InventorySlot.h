#ifndef InventorySlot_h__
#define InventorySlot_h__

#include "GameObject.h"
#include "ItemBase.h"

class Engine::CItemBase;

class CSlot : public Engine::CGameObject
{
private:
	explicit						CSlot(void);
	explicit						CSlot(const CSlot& rhs);
	virtual							~CSlot(void);

public:
	virtual HRESULT					Late_Initialize() override;
	virtual HRESULT					Initialize_GameObject() override;
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

private:
	Engine::CItemBase*				m_pItem = nullptr;
	Engine::_int					m_iItemCount = 0;
	ITEM_TYPE						m_eType;

public:
	static CSlot*					Create(void);
	virtual Engine::CGameObject*	Clone(const Engine::_vec3* pPos = nullptr) override;

private:
	inline virtual void				freeMem(void) override;
	virtual void					LoadData(HANDLE hFile) override;
};

#endif // InventorySlot_h__