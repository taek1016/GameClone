#ifndef EquipBase_h__
#define EquipBase_h__

#include "../SlotBase.h"

class CEquipBase : public CSlotBase
{
protected:
	explicit			CEquipBase(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CEquipBase(void) = default;
	
public:
	virtual void		Render_GameObject(void) override;
	virtual void		Click_Action(void) PURE;

protected:
	void				first_Update(void);
	void				make_Slots(void);

	Engine::CTexture*	m_pItemTexture;
	Engine::CRcTex*		m_pItemBuffer;

	wstring				m_wstrItemName;

protected:
	inline virtual void	Free(void) override;
};

#endif // EquipBase_h__
