#include "stdafx.h"
#include "NPC_Thrall.h"

#include "UI/QuestUI.h"

USING(Engine)

CNPC_Thrall::CNPC_Thrall(LPDIRECT3DDEVICE9 pGraphicDev)
	: CNPCBase(pGraphicDev)
	, m_pCurrentQuest(nullptr)
{
	set_Name(L"Thrall");
}

CNPC_Thrall::CNPC_Thrall(const CNPC_Thrall & rhs)
	: CNPCBase(rhs)
	, m_pCurrentQuest(nullptr)
{
}

void CNPC_Thrall::initialize_QuestContent(void)
{
	const _tchar* pNames[] = { L"Boar", L"KodoBeast", L"Nefarian" };

	const _tchar* pBoarContents[] = { L"�ڵ� ��Ʈ�� ���� �츮�� �μż� ������ �����ƴٳ�.", L"�ٸ� ���� Ű���״� ������ 5���� ����ְ�." };
	const _tchar* pKodoBeastContents[] = { L"�ٸ� ���� Ű����� �ڵ���Ʈ�� ó���ؾ߰ڳ�.", L"�ڵ� ��Ʈ�� �� ���� ����ְ�." };
	const _tchar* pNefarianContents[] = { L"�ڵ� ��Ʈ�� �뿡 �з��� �����Ŀ� ������ �����ǳ�.", L"���ĸ����̶�� ���� ����ְ�." };

	list<FONT_INFO>* pList = nullptr;

	// UI �������� ��������� ��.
	const _float fHalf = 0.5f;
	const _float fQuarter = 0.25f;

	const _float fTotalWidth = 348.f;
	const _float fTotalHeight = 435.f;

	_vec3 vTotalScale(WINCX * fQuarter, WINCY * fHalf, 1.f);
	const _float fStartYPos = 0.f + vTotalScale.y * 0.5f - (98.f / fTotalHeight) * vTotalScale.y;
	const _float fNextYPos = 80.f / fTotalHeight * vTotalScale.y;

	_vec3 vPos(WINCX * fHalf * fQuarter - vTotalScale.x * fHalf + vTotalScale.x * (44.f / fTotalWidth), 0.f, 0.f);
	_vec3 vScale(15.f, 15.f, 1.f);

	const _int iLineCount = 17;

	D3DXCOLOR tColor(1.f, 1.f, 1.f, 1.f);
	// ���� ����Ʈ ����
	pList = new list<FONT_INFO>;

	_int iSize = sizeof(pBoarContents) / sizeof(pBoarContents[0]);

	vPos.y = fStartYPos;

	for (_int i = 0; i < iSize; ++i)
	{
		pList->push_back(FONT_INFO(&vPos, &vScale, iLineCount, pBoarContents[i], tColor));
		vPos.y -= fNextYPos;
	}
	m_QuestContent.emplace(pNames[0], pList);

	// �ڵ� ��Ʈ ����
	pList = new list<FONT_INFO>;

	vPos.y = fStartYPos;

	iSize = sizeof(pKodoBeastContents) / sizeof(pKodoBeastContents[0]);

	for (_int i = 0; i < iSize; ++i)
	{
		pList->push_back(FONT_INFO(&vPos, &vScale, iLineCount, pKodoBeastContents[i], tColor));
		vPos.y -= fNextYPos;
	}
	m_QuestContent.emplace(pNames[1], pList);

	pList = new list<FONT_INFO>;
	vPos.y = fStartYPos;

	iSize = sizeof(pNefarianContents) / sizeof(pNefarianContents[0]);

	for (_int i = 0; i < iSize; ++i)
	{
		pList->push_back(FONT_INFO(&vPos, &vScale, iLineCount, pNefarianContents[i], tColor));
		vPos.y -= fNextYPos;
	}
	m_QuestContent.emplace(pNames[2], pList);
}

void CNPC_Thrall::make_Content(const Engine::_tchar * pKey)
{
	CQuestUI* pQuestUI = dynamic_cast<CQuestUI*>(m_pUI);

	auto& iterList = m_QuestContent.find(m_pCurrentQuest);

	if (m_QuestContent.end() == iterList)
	{
		return;
	}

	for (auto iter : *iterList->second)
	{
		pQuestUI->Print_Contents(iter);
	}

}

void CNPC_Thrall::act(void)
{
	CQuestUI* pQuestUI = dynamic_cast<CQuestUI*>(m_pUI);

	if (pQuestUI->Get_Accept())
	{
		pQuestUI->Clear_Contents();

		DLL::pQuestMgr->Activate_HuntingQuest(m_pCurrentQuest);
		
		m_pCurrentQuest = DLL::pQuestMgr->Get_NextQuestName();

		make_Content(m_pCurrentQuest);

		m_bUIActivate = false;
		Set_AnimationSet(L"GoodBye");
		pQuestUI->Cancel_Accepted();
	}
}

void CNPC_Thrall::initialize_NPCUI(void)
{
	m_pUI = CQuestUI::Create(m_pGraphicDev);

	dynamic_cast<CQuestUI *>(m_pUI)->Quest_AcceptContent(L"�����Ѵ�");
	dynamic_cast<CQuestUI *>(m_pUI)->Quest_DenyContent(L"�����Ѵ�");

	m_pCurrentQuest = L"Boar";

	initialize_QuestContent();

	make_Content(m_pCurrentQuest);
}

CNPC_Thrall * CNPC_Thrall::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNPC_Thrall* pInstance = new CNPC_Thrall(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CNPC_Thrall::Clone(void)
{
	CNPC_Thrall* pInstance = new CNPC_Thrall(*this);

	pInstance->Late_Initialize();
	pInstance->Add_MainCollider(pInstance->m_fMainColSize);

	return pInstance;
}

inline void CNPC_Thrall::Free(void)
{
	CNPCBase::Free();

	for (auto iter : m_QuestContent)
	{
		Safe_Delete(iter.second);
	}
	m_QuestContent.clear();
}
