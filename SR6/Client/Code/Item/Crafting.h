#ifndef Crafting_h__
#define Crafting_h__

#include "Base.h"
#include "Engine_Defines.h"

#include "ItemBase.h"
#include "WeaponSlot.h"

class CCrafting : public CBase
{
private:
	explicit	CCrafting(void);
	virtual		~CCrafting(void);

public:
	Engine::CGameObject*	Make_Item(const Engine::_int& iWoodCnt, const Engine::_int& iIronCnt);

	void					Setup_Craft(Engine::CGameObject* pItem, const Engine::_int iNeedWood, const Engine::_int iNeedIron);
	void					Get_NeedMaterial(_int* pWood, _int* pIron);

	Engine::CGameObject*	Clone(void);

private:
	Engine::_bool			Can_Make(const _int& iWoodCnt, const _int& iIronCnt);

	Engine::CGameObject*	m_pItem = nullptr;
	Engine::_int			m_iWoodCnt;
	Engine::_int			m_iIronCnt;

public:
	static CCrafting*		Create(void);

private:
	inline virtual void		freeMem(void);
};

#endif // Crafting_h__
