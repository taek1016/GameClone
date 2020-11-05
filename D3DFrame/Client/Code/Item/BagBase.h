#ifndef BagBase_h__
#define BagBase_h__

#include "ItemBase.h"

class CItemSlot;

class CBagBase : public CItemBase
{
protected:
	explicit						CBagBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CBagBase(const CBagBase& rhs);
	virtual							~CBagBase(void) = default;

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

	Engine::_bool					Add_Items(Engine::_tchar* pItems);
	const Engine::_tchar*			Get_PickItem(const Engine::_int& iIdx);

protected:
	void							set_ItemSlots(const Engine::_int& iWidthNum, const Engine::_int& iHeightNum);
	void							make_ItemSlot(const Engine::_vec3* pPos, const Engine::_vec3* pScale, const Engine::_float& fTotalWidth, const Engine::_float& fTotalHeight);

	vector<CItemSlot*>				m_vecItemSlot;
	Engine::_int					m_iWidthNum;
	Engine::_int					m_iHeightNum;

	Engine::CTexture*				m_pTexture;
	Engine::CRcTex*					m_pBuffer;

public:
	virtual Engine::CGameObject*	Clone(void) override;

protected:
	inline virtual void				Free(void) override;
};

#endif // BagBase_h__
