#ifndef InventoryMgr_h__
#define InventoryMgr_h__

#include "Base.h"

class CBagBase;

class CInventoryMgr : public CBase
{
	DECLARE_SINGLETON(CInventoryMgr)

private:
	explicit				CInventoryMgr(void);
	virtual					~CInventoryMgr(void);

public:
	void					Initialize_Inventory(LPDIRECT3DDEVICE9& pGraphicDev);
	void					Update_Inventory(const Engine::_float& fTimeDelta);

	void					Activate_Bag(const Engine::_int& iIndex);

	void					Add_Money(const Engine::_int& iMoney);
	CBagBase*				Get_Bag(const Engine::_int& iIndex);
	CBagBase*				Add_Bag(CBagBase* pBag, const Engine::_int& iIndex);

	Engine::_int			Get_Money(void) const;
	Engine::_bool			Can_BuyItem(const Engine::_int& iMoney);
	void					Convert_Money(Engine::_int iMoney);

private:
	Engine::_int			m_iMoney;
	Engine::_int			m_iGold;
	Engine::_int			m_iSilver;
	Engine::_int			m_iCooper;

	Engine::_vec3			m_vStartPos;
	Engine::_float			m_fSlotScaleWidth;
	Engine::_float			m_fSlotScaleHeight;

	vector<pair<CBagBase*, Engine::_bool>>	m_vecBags;
	
private:
	inline virtual void		Free(void) override;
};

#endif // InventoryMgr_h__
