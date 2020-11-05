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

	const _tchar* pBoarContents[] = { L"코도 비스트가 돼지 우리를 부셔서 돼지가 도망쳤다네.", L"다른 동물 키울테니 돼지를 5마리 잡아주게." };
	const _tchar* pKodoBeastContents[] = { L"다른 동물 키우더라도 코도비스트는 처리해야겠네.", L"코도 비스트를 한 마리 잡아주게." };
	const _tchar* pNefarianContents[] = { L"코도 비스트가 용에 밀려서 도망쳐온 것으로 생각되네.", L"네파리안이라는 용을 잡아주게." };

	list<FONT_INFO>* pList = nullptr;

	// UI 기준으로 움직여줘야 함.
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
	// 돼지 퀘스트 내용
	pList = new list<FONT_INFO>;

	_int iSize = sizeof(pBoarContents) / sizeof(pBoarContents[0]);

	vPos.y = fStartYPos;

	for (_int i = 0; i < iSize; ++i)
	{
		pList->push_back(FONT_INFO(&vPos, &vScale, iLineCount, pBoarContents[i], tColor));
		vPos.y -= fNextYPos;
	}
	m_QuestContent.emplace(pNames[0], pList);

	// 코도 비스트 내용
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

	dynamic_cast<CQuestUI *>(m_pUI)->Quest_AcceptContent(L"수락한다");
	dynamic_cast<CQuestUI *>(m_pUI)->Quest_DenyContent(L"거절한다");

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
