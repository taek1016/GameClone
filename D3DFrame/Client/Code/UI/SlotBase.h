#ifndef SlotBase_h__
#define SlotBase_h__

#include "GameObject.h"
#include "Skill/SkillBase.h"

class CSlotBase : public Engine::CGameObject
{
protected:
	explicit						CSlotBase(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CSlotBase(void);

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

	virtual void					Set_Texture(const Engine::_tchar* pName) {}

	const Engine::_bool				Get_Clicked(void) const;
	virtual void					Click_Action(void) PURE;

protected:
	virtual void					set_Data(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	CSkillBase*						m_pTargetSkill;
	Engine::CTexture*				m_pTexture;
	Engine::CRcTex*					m_pBuffer;

	MY_RECT							m_tRect;

	Engine::_bool					m_bClicked;
	Engine::_bool					m_bCollided;

	LPD3DXLINE						m_pLine;

	Engine::_vec2					m_vColLine[5];
	D3DXCOLOR						m_tColor[2];

	Engine::_float					m_fClickTime;

public:
	// LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar* pName, const Engine::_vec3* pPos, const Engine::_vec3* pScale를 인자로 받는 Create 함수 필요.
	virtual Engine::CGameObject*	Clone(void) override;

protected:
	inline virtual void				Free(void) override;
};
#endif // SlotBase_h__
