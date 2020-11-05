#include "Shader.h"

USING(Engine)

CShader::CShader(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_pEffect(nullptr)
	, m_pErrMsg(nullptr)
{
	m_pGraphicDev->AddRef();
}

CShader::CShader(const CShader & rhs)
	: m_pGraphicDev(rhs.m_pGraphicDev)
	, m_pEffect(rhs.m_pEffect)
	, m_pErrMsg(rhs.m_pErrMsg)
{
	m_pGraphicDev->AddRef();
	m_pEffect->AddRef();
}

CShader::~CShader(void)
{
}

HRESULT CShader::Initialize_Shader(const _tchar * pFilePath)
{
	// m_pEffect ���� �ְ�, m_pErrMsg ���� ���� ��� : ���������� ���̴� ������ �۵��ϴ� ���

	// m_pEffect ���� ����, m_pErrMsg ���� �ִ� ��� : ������ ����
	// m_pEffect ���� �ְ�, m_pErrMsg ���� �ִ� ��� : ���


	if (FAILED(D3DXCreateEffectFromFile(m_pGraphicDev,
		pFilePath,
		NULL,				// ���̴����� ����� ��ũ�� ����
		NULL,				// ���̴����� ����� ���� ����
		D3DXSHADER_DEBUG,	// ���̴��� ������ϰڴٴ� �ɼ�(����� ������ �ܺζ��̺귯���� �����ؾ������� ������ ����ؼ� ������ ���� ���� ��)
		NULL,				// ���� ���ҽ� ������ ��� ������ ���ΰ�(null�� ��� �׷��� �޸𸮿� ���� ��)
		&m_pEffect,			// ���̴� ��ü
		&m_pErrMsg)))		// ����� �Ұ��������� ���� �� ��� ���� ��� �����ϱ� ���� �޸� ����
	{
		MessageBoxA(NULL, (char*)m_pErrMsg->GetBufferPointer(), "Shader_Error", MB_OK);
		return E_FAIL;
	}

	else if (nullptr != m_pErrMsg)
	{
		MessageBoxA(NULL, (char*)m_pErrMsg->GetBufferPointer(), "Shader_Warning", MB_OK);
	}

	return S_OK;
}

CShader * CShader::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar * pFilePath)
{
	CShader*	pInstance = new CShader(pGraphicDev);

	if (FAILED(pInstance->Initialize_Shader(pFilePath)))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CShader::Clone(void)
{
	return new CShader(*this);
}

inline void CShader::Free(void)
{
	Safe_Release(m_pEffect);
	Safe_Release(m_pGraphicDev);
}