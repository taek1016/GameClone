#ifndef ItemMgr_h__
#define ItemMgr_h__

#include "Base.h"

class CItemMgr : public CBase
{
	DECLARE_SINGLETON(CItemMgr)

private:
	explicit								CItemMgr(void);
	virtual									~CItemMgr(void);

public:
	void									Initialize_Items(LPDIRECT3DDEVICE9& pGraphicDev);
	CItemBase*								Clone_Item(const Engine::_tchar* pName);
	const Engine::_bool						Is_Item(const Engine::_tchar* pName) const;
	//const Engine::_int						Get_ItemPrice(const Engine::_tchar* pItemType, const Engine::_tchar* pItemName);
	const Engine::_int						Get_ItemPrice(const Engine::_tchar* pItemName);

private:
	void									add_Item(const Engine::_tchar* pName, CItemBase* pItem, const Engine::_int& iMoney);
	
	map<wstring, pair<CItemBase*, const Engine::_int>>	m_mapItems;

private:
	inline virtual void						Free(void) override;
};

#endif // ItemMgr_h__
