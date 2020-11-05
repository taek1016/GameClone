#ifndef WaterElemental_h__
#define WaterElemental_h__

#include "SupporterBase.h"

class CWaterElemental : public CSupporterBase
{
	enum WATER_ELEMENTAL_PATTERN	{ WATER_ELE_STAND, WATER_ELE_PLAYER_FOLLOW, WATER_ELE_MONSTER_FOLLOW, WATER_ELE_ATTACK, WATER_ELE_END };

private:
	explicit						CWaterElemental(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CWaterElemental(const CWaterElemental& rhs);
	virtual							~CWaterElemental(void) = default;

private:
	void							initialize_ActionCol(void);
	virtual void					act_Determine(const Engine::_float& fTimeDelta) override;
	virtual void					make_Weapon(void);

	Engine::_bool					determine_AI(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							attack_Act(const Engine::_float& fTimeDelta);

public:
	static CWaterElemental*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // WaterElemental_h__
