#include "stdafx.h"
#include "QuestButton.h"

USING(Engine)

CQuestButton::CQuestButton(LPDIRECT3DDEVICE9 pGraphicDev)
	: CButton(pGraphicDev)
{
}

Engine::_int CQuestButton::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CButton::Update_GameObject(fTimeDelta);



	return iExit;
}

void CQuestButton::Print_AcceptContent(const FONT_INFO & tInfo)
{
	memcpy(&m_tFontInfo, &tInfo, sizeof(FONT_INFO));
}

CQuestButton * CQuestButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	return nullptr;
}
