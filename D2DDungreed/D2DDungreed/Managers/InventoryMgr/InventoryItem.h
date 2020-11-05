#ifndef __ITEM_IN_INVENTORY_H__

class CBaseItem;
class CInventoryItem
{
private:
	CInventoryItem();

public:
	~CInventoryItem();

	static CInventoryItem* Create
	(
		const D3DXVECTOR3	vecPos,
		const D3DXVECTOR3	vecSize,
		const std::wstring&	wStrObjectKey		= L"",
		const std::wstring& wStrObjectStatus	= L""
	);

	int Update				();
	void Render				();
	void DeleteItem			()
	{
		SafeDelete(m_pItem);
	}

	bool GetClicked			()
	{
		return m_bClicked;
	}
	bool IsEmpty			()
	{
		if (m_pItem)
		{
			return false;
		}
		return true;
	}
	void SetItem			(CBaseItem* pObj)
	{
		m_pItem = pObj;
	}
	CBaseItem*	GetItem		()
	{
		return m_pItem;
	}

private:
	void SetKey			(const std::wstring&	wStrObjectKey)
	{
		m_wStrObjectKey = wStrObjectKey;
	}
	void SetStatus		(const std::wstring& wStrObjectStatus)
	{
		m_wStrObjectStatus = wStrObjectStatus;
	}
	void UpdateRect		();

private:
	bool			m_bClicked;

	D3DXMATRIX		m_matWorld;
	
	D3DXVECTOR3		m_vecPos;
	D3DXVECTOR3		m_vecSize;

	RECT			m_tRECT;

	FRAME			m_tFrame;

	std::wstring	m_wStrObjectKey;
	std::wstring	m_wStrObjectStatus;

	CBaseItem*		m_pItem;
};

#define __ITEM_IN_INVENTORY_H__
#endif