#ifndef InventorySlot_h__
#define InventorySlot_h__

#include "SlotBase.h"

class CBagBase;

class CInventorySlot : public CSlotBase
{
private:
	explicit					CInventorySlot(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit					CInventorySlot(const CInventorySlot& rhs);
	virtual						~CInventorySlot(void) = default;

public:
	virtual HRESULT				Initialize_GameObject(void) override;
	virtual HRESULT				Late_Initialize(void) override;

	virtual Engine::_int		Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void				Render_GameObject(void) override;

	virtual void				Click_Action(void);
	void						Set_BagName(const Engine::_tchar* pName);

private:
	void						set_CurIdx(const Engine::_int& iIdx);

	wstring						m_wTextureName;
	Engine::_int				m_iCurIdx;

	Engine::CTexture*			m_pBagTexture;
	Engine::CRcTex*				m_pBagBuffer;

	CBagBase*					m_pBag;

	Engine::_float				m_fClicked;

public:
	static CInventorySlot*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale, const Engine::_int& iIdx);

};
#endif // InventorySlot_h__
