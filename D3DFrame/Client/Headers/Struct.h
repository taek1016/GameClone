#ifndef Struct_h__
#define Struct_h__

class CSkillBase;
typedef struct tagMyRect
{
	float	fLeft;
	float	fTop;
	float	fRight;
	float	fBottom;
}MY_RECT;

typedef	struct tagSkill
{
	CSkillBase*	pSkill;

	wstring		wStrReadyAnimationKey;
	wstring		wStrCastingAnimationKey;

	float		fCastingTime;
	float		fCoolTime;
	float		fNeedMana;

	bool		bUsing;
	bool		bCanUse;

	tagSkill(void)
		: pSkill(nullptr)
		, fCastingTime(0.f)
		, fCoolTime(0.f)
		, fNeedMana(0.f)
		, bUsing(false)
		, bCanUse(true)
	{ }

	tagSkill(CSkillBase* _pSkill, const Engine::_tchar* pReadyKey, const Engine::_tchar* pCastingKey, const float& _fCastingTime, const float& _fCoolTime, const float& fMana = 0.f)
		: pSkill(_pSkill)
		
		, wStrReadyAnimationKey(pReadyKey)
		, wStrCastingAnimationKey(pCastingKey)

		, fCastingTime(_fCastingTime)
		, fCoolTime(_fCoolTime)
		, fNeedMana(fMana)
		, bUsing(false)
		, bCanUse(true)
	{ }

}SKILL_INFO;

class CItemBase;

typedef struct tagItemInfo
{
	CItemBase*			pItem;
	const D3DXMATRIX*	pMatBone;
	const D3DXMATRIX*	pMatWorld;

	tagItemInfo()
		: pItem(nullptr)
		, pMatBone(nullptr)
		, pMatWorld(nullptr)
	{ }
} ITEM_INFO;

struct FONT_INFO
{
	const Engine::_tchar*	pTextData;
	Engine::_vec3			vPos;
	Engine::_vec3			vScale;
	Engine::_int			iLinePerText;
	D3DXCOLOR				tColor;

	FONT_INFO(void)
		: pTextData(nullptr)
		, vPos(0.f, 0.f, 0.f)
		, vScale(0.f, 0.f, 0.f)
		, iLinePerText(0)
		, tColor(0.f, 0.f, 0.f, 1.f)
	{ }

	FONT_INFO(const Engine::_vec3* pPos, const Engine::_vec3* pScale, 
		const Engine::_int& _iLinePerCount, const Engine::_tchar* pText, 
		const D3DXCOLOR& _tColor = D3DXCOLOR(0.f, 0.f, 0.f, 1.f))
		: pTextData(pText)
		, vPos(*pPos)
		, vScale(*pScale)
		, iLinePerText(_iLinePerCount)
		, tColor(_tColor)
	{ }

	void operator=(const FONT_INFO& rhs)
	{
		pTextData = rhs.pTextData;
		vPos = rhs.vPos;
		vScale = rhs.vScale;
		iLinePerText = rhs.iLinePerText;
		tColor = rhs.tColor;
	}
};

#endif // Struct_h__
