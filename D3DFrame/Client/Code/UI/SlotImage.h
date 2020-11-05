#ifndef SlotImage_h__
#define SlotImage_h__

#include "UIBase.h"

class CSlotImage : public CUIBase
{
private:
	explicit				CSlotImage(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CSlotImage(const CSlotImage& rhs);
	virtual					~CSlotImage(void) = default;

public:
	virtual HRESULT			Initialize_GameObject(void) override;
	virtual HRESULT			Late_Initialize(void) override;

	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	void					Set_Texture(const Engine::_tchar* pName);

private:
	void					set_Vector(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale);

public:
	static CSlotImage*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
};
#endif // SlotImage_h__
