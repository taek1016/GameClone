#ifndef CraftingMgr_h__
#define CraftingMgr_h__

#include "Crafting.h"

class CCraftingUI;
class CCraftFont;

class CCraftingMgr : public CBase
{
	DECLARE_SINGLETON(CCraftingMgr)

private:
	explicit								CCraftingMgr(void);
	virtual									~CCraftingMgr(void);

public:
	void									Register_Crafting(const Engine::_tchar* pKey, CCrafting* pCraft);
	void									Update_Crafting(const Engine::_float& fDelta);
	Engine::_bool							Make_Item(const Engine::_tchar* pKey, const INSTALL_TYPE& eType);
	Engine::_bool							Get_Activate() { return m_bActivate; }

	HRESULT									Initialize_Crafting(void);
	void									Set_Activate();
	void									Finish_Craft();

	Engine::CGameObject*					Clone(const INSTALL_TYPE& eType);
private:
	map<const Engine::_tchar*, CCrafting*>	m_mapCraft;
	Engine::_bool							m_bActivate = false;
	Engine::_bool							m_bCanMake = false;

	Engine::_float							m_fCurTime = 0.f;
	Engine::_float							m_fEndTime = 2.f;

	Engine::CGameObject*					m_pItem = nullptr;
	CCraftFont*								m_pCraftFont = nullptr;
	INSTALL_TYPE							m_eType;

private:
	inline virtual void						freeMem(void);
};


#endif // CraftingMgr_h__
