#ifndef __INVENTORY_H__

class CInventory
{
public:
	void Update			();
	void Render			();

	void ChangeActivate	();

	bool GetActivate	()
	{
		return m_bActivate;
	}
	bool SetItem		(CBaseItem* pObj);

	CBaseItem* GetEquipWeapon();
	CBaseItem* GetEquipShield();

	DECLARE_SINGLETON(CInventory)

private:
	CInventory();
	~CInventory();

	void Initialize();

private:
	int						m_iColor;
	int						m_iItemCount;
	int						m_iEquipCount;
	int						m_iAccessoryCount;

	bool					m_bActivate;
	bool					m_bTapClicked;

	const std::wstring		m_wStrKey;
	const std::wstring		m_wStrStatus;

	D3DXMATRIX				m_matWorld;

	class CMyButton*		m_pButton;

	class CInventoryItem**	m_pItem;

	class CInventoryItem**	m_pEquipLeftHand;
	class CInventoryItem**	m_pEquipRightHand;
	class CInventoryItem**	m_pAccessory;

	class CInventoryRender*	m_pRender;
};

#define __INVENTORY_H__
#endif