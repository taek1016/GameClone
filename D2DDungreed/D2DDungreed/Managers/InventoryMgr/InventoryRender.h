#ifndef __INVENTORY_RENDER_H__
class CInventoryRender
{
private:
	CInventoryRender();

public:
	virtual ~CInventoryRender();

	static CInventoryRender* Create
	(
		const D3DXVECTOR3	vecPos,
		const D3DXVECTOR3	vecSize,
		const WORD&			wIndex,
		const std::wstring&	wStrKey,
		const std::wstring&	wStrStatus
	);

	void Update();
	void Render();

	void SetKey(const std::wstring& wstr)
	{
		m_wStrKey = wstr;
	}
	void SetStatus(const std::wstring& wstr)
	{
		m_wStrStatus = wstr;
	}

private:
	std::wstring	m_wStrKey;
	std::wstring	m_wStrStatus;

	D3DXVECTOR3		m_vecPos;
	D3DXVECTOR3		m_vecSize;

	D3DXMATRIX		m_matWorld;

	WORD			m_wIndex;
};

#define __INVENTORY_RENDER_H__
#endif