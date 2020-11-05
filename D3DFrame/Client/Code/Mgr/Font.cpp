#include "stdafx.h"
#include "Font.h"

USING(Engine)

CFont::CFont(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pBuffer(nullptr)
	, m_pShader(nullptr)
{
}

HRESULT CFont::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Font")->Attach(L"Shader", this, ID_STATIC);

	return S_OK;
}

HRESULT CFont::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pBuffer = Get_Component<CRcTex>(L"Buffer", ID_STATIC);
	m_pShader = Get_Component<CShader>(L"Shader", ID_STATIC);

	return S_OK;
}

Engine::_int CFont::Update_GameObject(const _float & fTimeDelta)
{
	if (false == m_vecTextData.empty())
	{
		DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);
	}

	return 0;
}

void CFont::Render_GameObject(void)
{
	auto pScale = m_pTransform->Get_Scale();

	CTexture* pTexture = nullptr;
	
	const _tchar* pText;
	_tchar szText[2]{};
	for (auto iter : m_vecTextData)
	{
		_int iTextCount = static_cast<_int>(lstrlen(iter.pTextData));
		_int iCount = 0;

		pText = iter.pTextData;
		m_pTransform->Set_Info(INFO_POS, &iter.vPos);

		while (iCount < iTextCount)
		{
			m_pTransform->Set_Scale(&iter.vScale);
			
			m_pTransform->Update_Component(0.f);
			m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

			memcpy(&szText[0], pText, sizeof(_tchar));
			pTexture = find_Texture(szText);

			//pTexture->Render_Texture();
			//m_pBuffer->Render_Buffer();

			render_SingleFont(iter.tColor, pTexture);

			m_pTransform->Move_Pos(&_vec3(pScale->x, 0.f, 0.f));

			if (0 == (iCount++ + 1) % iter.iLinePerText)
			{
				iter.vPos -= _vec3(0.f, pScale->y, 0.f);
				m_pTransform->Set_Info(INFO_POS, &iter.vPos);
			}

			pText++;
		}
	}

	Clear_Data();
}

void CFont::Add_Font(const Engine::_tchar * pKey, Engine::CTexture * pTexture)
{
	auto iter = m_FontMap.find(pKey);

	if (m_FontMap.end() != iter)
	{
		Safe_Release(iter->second);
		m_FontMap[pKey] = pTexture;
		return;
	}

	m_FontMap.emplace(pKey, pTexture);
}

void CFont::Push_FontData(const FONT_INFO & rhs)
{
	m_vecTextData.push_back(FONT_INFO(rhs));
}

void CFont::Clear_Data(void)
{
	m_vecTextData.clear();
}

void CFont::render_SingleFont(const D3DXCOLOR& tColor, Engine::CTexture * pTexture)
{
	LPD3DXEFFECT	pEffect = m_pShader->Get_EffectHandle();
	NULL_CHECK(pEffect);
	pEffect->AddRef();

	_uint	iPassMax = 0;


	FAILED_CHECK_RETURN(setUp_ConstantTable(tColor, pTexture, pEffect), );

	pEffect->Begin(&iPassMax, 0);	// 1인자 : 현재 쉐이더 파일 갖고 있는 최대 패스의 개수

	pEffect->BeginPass(0);

	m_pBuffer->Render_Buffer();

	pEffect->EndPass();

	pEffect->End();

	Engine::Safe_Release(pEffect);
}

Engine::CTexture * CFont::find_Texture(const Engine::_tchar * pKey)
{
	auto iter = find_if(m_FontMap.begin(), m_FontMap.end(), CTag_Finder(pKey));

	if (m_FontMap.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

HRESULT CFont::setUp_ConstantTable(const D3DXCOLOR& tColor, Engine::CTexture * pTexture, LPD3DXEFFECT & pEffect)
{
	_matrix			matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->Get_World());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	
	pEffect->SetVector("g_vColor", &D3DXVECTOR4(tColor));

	pTexture->Set_Texture(pEffect, "g_BaseTexture", (_uint)0);

	return S_OK;
}

CFont * CFont::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFont* pInstance = new CFont(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();

	return pInstance;
}

inline void CFont::Free(void)
{
	CGameObject::Free();

	for (auto iter : m_FontMap)
	{
		CDeleteMap(iter);
	}

	m_FontMap.clear();

	m_vecTextData.clear();
}
