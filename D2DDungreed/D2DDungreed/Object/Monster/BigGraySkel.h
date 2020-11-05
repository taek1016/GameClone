#ifndef __BIG_GRAY_SKEL_H__

#include "MeleeMonster.h"

class CBigGraySkel : public CMeleeMonster
{
private:
	CCoolTime		m_fSkillCool;
	CRect*			m_pSkillRect;

private:
	CBigGraySkel				();

public:
	virtual ~CBigGraySkel		();

	static CBigGraySkel* Create	(const D3DXVECTOR3& vecPos);

	virtual void Attack			() override;
	virtual void Act			() override;

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;

	virtual void UpdateRect		() override;

	void CreateEffect			();
	void Skill					();
	void ConvertSizeVector		();
};

#define __BIG_GRAY_SKEL_H__
#endif