#include "stdafx.h"
#include "ToolTerrain.h"

#include "ToolTerrainTex.h"
#include "NaviObject.h"
#include "Transform.h"
#include "ToolNaviCtrl.h"
#include "ToolGuideAxis.h"

#include "Shader.h"

USING(Engine)

CToolTerrain::CToolTerrain(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)

	, m_pNavi(nullptr)
	, m_pTerrainTool(nullptr)
	, m_pNaviCtrl(nullptr)
	, m_pMesh(nullptr)
	, m_pTexBuffer(nullptr)

	, m_bTerrainCtrl(false)
	, m_bNaviCtrlInitialized(false)
{
	set_Name(L"Terrain");
}

CToolTerrain::~CToolTerrain(void)
{
}

Engine::_int CToolTerrain::Update_GameObject(const Engine::_float & fTimeDelta)
{

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	if (m_pNaviCtrl)
	{
		m_pNaviCtrl->Update(fTimeDelta);
	}

	return iExit;
}

void CToolTerrain::Render_GameObject(void)
{
	if (m_pTexBuffer)
	{
		m_pTexBuffer->Render_Buffer();
	}
	if (m_pMesh)
	{
		LPD3DXEFFECT	pEffect = m_pShaderCom->Get_EffectHandle();
		NULL_CHECK(pEffect);
		pEffect->AddRef();

		_uint	iPassMax = 0;

		FAILED_CHECK_RETURN(SetUp_ConstantTable(pEffect), );

		pEffect->Begin(&iPassMax, 0);

		pEffect->BeginPass(0);

		m_pMesh->Render_Meshes(pEffect);

		pEffect->EndPass();

		pEffect->End();

		Safe_Release(pEffect);
	}
	if (m_pNavi)
	{
		m_pNavi->Render_NaviMesh();
	}

	if (m_bTerrainCtrl && m_pNaviCtrl)
	{
		m_pNaviCtrl->Render();
	}
}

HRESULT CToolTerrain::Initialize_GameObject(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransform = CTransform::Create();
	pComponent->Attach(L"Transform", this, ID_DYNAMIC);

	m_pShaderCom = DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh");
	m_pNavi = CToolNavi::Create(m_pGraphicDev);
	m_pNaviCtrl = CToolNaviCtrl::Create();

	return S_OK;
}

void CToolTerrain::Set_TerrainTool(CTerrainTool * pTerrainTool)
{
	m_pTerrainTool = pTerrainTool;
}

void CToolTerrain::Make_Tex(const Engine::_ulong & dwCntX, const Engine::_ulong & dwCntZ)
{
	Safe_Release(m_pTexBuffer);

	m_pTexBuffer = CToolTerrainTex::Create(dwCntX, dwCntZ, 1, 1);
	m_pTexBuffer->Attach(L"Buffer", this, ID_STATIC);
}

void CToolTerrain::Make_TerrainMesh(const Engine::_tchar* pKey)
{
	Safe_Release(m_pMesh);

	m_wStrRenderKey = pKey;
	m_pMesh = (DLL::pResourcesMgr->Clone<CStaticMesh>(0, m_wStrRenderKey.c_str()));
}

void CToolTerrain::Make_NaviMesh(void)
{
	Safe_Release(m_pNavi);

	m_pNavi = CToolNavi::Create(m_pGraphicDev);
}

void CToolTerrain::Make_GuideLine(void)
{
	m_pNaviCtrl->Activate(m_pNavi->Get_Vec());
}

void CToolTerrain::KeyInput(void)
{
	// TerrainTex Control
	if (nullptr == this)
	{
		return;
	}
	if (m_bTerrainCtrl)
	{
		if (!m_bNaviCtrlInitialized)
		{
			m_bNaviCtrlInitialized = true;
			m_pNaviCtrl->Initialize_Ctrl(m_pNavi, m_pMesh);
		}
		m_pNaviCtrl->KeyInput();
	}
	else
	{
		if (!m_bNaviCtrlInitialized)
		{
			m_bNaviCtrlInitialized = true;
			m_pNaviCtrl->Initialize_Ctrl(m_pNavi, m_pMesh);
		}

		m_pNavi->Set_Objects(m_pMesh, m_pNaviCtrl);
		m_pNavi->KeyInput();
		Engine::CCell* pCell = m_pNavi->Get_MadeCell();
		if (pCell)
		{
			m_pTerrainTool->Add_List(m_pNavi->Get_Vec());
		}
	}
}

void CToolTerrain::Change_CtrlTarget(const Engine::_tchar * pKey)
{
	if (0 == lstrcmp(pKey, L"NaviCtrl"))
	{
		m_bTerrainCtrl = true;
		Make_GuideLine();
	}

	if (0 == lstrcmp(pKey, L"NaviMesh"))
	{
		m_bTerrainCtrl = false;
	}
}

void CToolTerrain::Delete_Navi(const Engine::_ulong & dwIdx)
{
	m_pNavi->Delete_Cell(dwIdx);
}

Engine::CStaticMesh* CToolTerrain::Get_Buffer(void) const
{
	return m_pMesh;
}

CToolGuideAxis * CToolTerrain::Get_ActivatedAxis(void)
{
	return m_pNaviCtrl->Get_ActivatedAxis();
}

CToolNavi * CToolTerrain::Get_Navi(void)
{
	return m_pNavi;
}

CToolNaviCtrl * CToolTerrain::Get_NaviCtrl(void)
{
	return m_pNaviCtrl;
}

const wstring & CToolTerrain::Get_RenderKey(void) const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_wStrRenderKey;
}

HRESULT CToolTerrain::SetUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	_matrix			matWorld, matView, matProj;

	matWorld = *m_pTransform->Get_World();
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	const D3DLIGHT9*		pLight = DLL::pLightMgr->Get_LightInfo(0);
	NULL_CHECK_RETURN(pLight, S_OK);


	pEffect->SetVector("g_vLightDir", &_vec4(pLight->Direction, 0.f));
	pEffect->SetVector("g_vLightDiffuse", (_vec4*)&pLight->Diffuse);
	pEffect->SetVector("g_vLightSpecular", (_vec4*)&pLight->Specular);
	pEffect->SetVector("g_vLightAmbient", (_vec4*)&pLight->Ambient);


	D3DMATERIAL9		tMtrlInfo;
	ZeroMemory(&tMtrlInfo, sizeof(D3DMATERIAL9));

	tMtrlInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	tMtrlInfo.Power = 100.f;

	pEffect->SetVector("g_vMtrlDiffuse", (_vec4*)&tMtrlInfo.Diffuse);
	pEffect->SetVector("g_vMtrlSpecular", (_vec4*)&tMtrlInfo.Specular);
	pEffect->SetVector("g_vMtrlAmbient", (_vec4*)&tMtrlInfo.Ambient);

	_vec4		vCamPos;
	D3DXMatrixInverse(&matView, NULL, &matView);
	memcpy(&vCamPos, &matView.m[3][0], sizeof(_vec4));

	pEffect->SetVector("g_vCamPos", &vCamPos);
	pEffect->SetFloat("g_fPower", tMtrlInfo.Power);

	return S_OK;
}

CToolTerrain * CToolTerrain::Create(void)
{
	CToolTerrain*	pInstance = new CToolTerrain(DLL::pGraphicDev->GetDevice());

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

HRESULT CToolTerrain::SaveTerrain(HANDLE hFile)
{
	//DWORD dwBytes = 0;
	//_int iSize = m_wStrRenderKey.size();
	//WriteFile(hFile, &iSize, sizeof(_int), &dwBytes, NULL);
	//WriteFile(hFile, m_wStrRenderKey.c_str(), sizeof(_tchar) * iSize, &dwBytes, NULL);

	//OBJECTBASE_INFO tInfo(*m_pTransform->Get_Info(INFO_POS), *m_pTransform->Get_Scale(), *m_pTransform->Get_Angle());

	//WriteFile(hFile, &tInfo, sizeof(OBJECTBASE_INFO), &dwBytes, NULL);

	return m_pNavi->SaveNaviMesh(hFile);
}

void CToolTerrain::LoadData(HANDLE hFile)
{
	//DWORD dwBytes = 0;
	//const _int iMaxStr = 256;
	//TCHAR szRenderKey[iMaxStr]{};

	//_int iSize;
	//ReadFile(hFile, &iSize, sizeof(_int), &dwBytes, NULL);
	//ReadFile(hFile, szRenderKey, sizeof(_tchar) * iSize, &dwBytes, NULL);
	//m_wStrRenderKey = szRenderKey;

	//Make_TerrainMesh(m_wStrRenderKey.c_str());

	//OBJECTBASE_INFO tInfo;
	//ReadFile(hFile, &tInfo, sizeof(OBJECTBASE_INFO), &dwBytes, NULL);

	//m_pTransform->Set_Info(INFO_POS, &tInfo.vPos);
	//m_pTransform->Set_Scale(&tInfo.vScale);
	//m_pTransform->Set_Angle(&tInfo.vAngle);

	m_pNavi->LoadNaviMesh(hFile);
}

inline void CToolTerrain::Free()
{
	CGameObject::Free();

	Engine::Safe_Release(m_pNavi);
	Engine::Safe_Release(m_pMesh);
	Engine::Safe_Release(m_pNaviCtrl);
}