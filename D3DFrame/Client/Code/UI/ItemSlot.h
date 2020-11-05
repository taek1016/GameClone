#ifndef ItemSlot_h__
#define ItemSlot_h__

#include "SlotBase.h"

class CItemSlot : public CSlotBase
{
protected:
	explicit						CItemSlot(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CItemSlot(void);

public:
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;
	virtual void					Set_Texture(const Engine::_tchar* pName);

	virtual void					Click_Action(void);

	Engine::_bool					Is_Empty(void) const;

	virtual void					Set_Item(const Engine::_tchar* pName);

	void							Clear_Item(void);
	const Engine::_tchar*			Get_Item(void) const;

protected:
	void							initialize_TextureBuffer(void);

	wstring							m_wStrItemName;
	
	Engine::_bool					m_bIsInShop;
	Engine::CTexture*				m_pItemTexture;
	Engine::CRcTex*					m_pItemBuffer;

public:
	static CItemSlot*				Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale, const Engine::_bool& bIsInShop = false);

protected:
	inline virtual void				Free(void) override;
};

#endif // ItemSlot_h__
