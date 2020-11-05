#ifndef __ATTACK_RECT_H__

class CPlayer;
class CRect
{
private:
	bool						m_bCanAct;
	
	bool						m_bMelee;

	float						m_fRange;

	RECT						m_tRect;

	const CPlayer*				m_pPlayer;

	const D3DXVECTOR3*			m_pMonsterPos;

public:
	CRect						(float fRange);

	~CRect						();
	
	static CRect*	Create		(const float fRange, const D3DXVECTOR3& vecPos, const bool bMelee = false);

	void Update					();
	void LateUpdate				();
	void Render					();

	bool GetCanAct			()
	{
		return m_bCanAct;
	}

private:
	void UpdateRect();

};

#define __ATTACK_RECT_H__
#endif