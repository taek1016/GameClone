#ifndef EquipSlot_h__
#define EquipSlot_h__

#include "SlotBase.h"

class CEquipSlot : public CSlotBase
{
private:
	explicit				CEquipSlot(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CEquipSlot(void) = default;

public:
	virtual void			Render_GameObject(void) override;
	virtual void			Set_Texture(const Engine::_tchar* pName);

	virtual void			Click_Action(void);

private:
	void					initialize_TextureBuffer(void);

	wstring					m_wStrItemName;

	Engine::CTexture*		m_pItemTexture;
	Engine::CRcTex*			m_pItemBuffer;

	EQUIP_ENUM				m_eEquipData;

public:
	static CEquipSlot*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);

private:
	inline virtual void		Free(void) override;
};
#endif // EquipSlot_h__
