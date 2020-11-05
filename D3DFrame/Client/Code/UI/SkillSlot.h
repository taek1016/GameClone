#ifndef SkillSlot_h__
#define SkillSlot_h__

#include "SlotBase.h"

class CPlayer;

class CSkillSlot : public CSlotBase
{
protected:
	explicit						CSkillSlot(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CSkillSlot(void) = default;

public:
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Set_Texture(const Engine::_tchar* pName) override;
	virtual void					Click_Action(void) override;
	void							Set_LevelLimit(const Engine::_int& iLevelLimit);

private:
	void							set_ActNum(const Engine::_int& iInputNum);
	void							set_CopyOnly(const Engine::_bool& bCopyOnly);

	wstring							m_wStrAnimationKey;
	wstring							m_wTextureName;
	Engine::_int					m_iInputData;
	Engine::_int					m_iInputNum;
	Engine::_int					m_iLevelLimit;

	Engine::_tchar					m_szSkillNum[8];

	Engine::_bool					m_bCopyOnly;

public:
	// -1이 들어오면 아무것도 동작하지 않는 것.
	static CSkillSlot*				Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale, const Engine::_int& iInputNum = -1, const Engine::_bool& bCopyOnly = false);


};

#endif // SkillSlot_h__
