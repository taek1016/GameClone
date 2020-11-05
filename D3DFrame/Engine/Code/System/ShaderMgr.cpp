#include "ShaderMgr.h"
#include "Shader.h"

USING(Engine)
IMPLEMENT_SINGLETON(CShaderMgr)

Engine::CShaderMgr::CShaderMgr(void)
{

}

Engine::CShaderMgr::~CShaderMgr(void)
{
	Free();
}

HRESULT Engine::CShaderMgr::Initialize_Shaders(const _tchar* pShaderTag, CShader* pInstance)
{
	CComponent*	pPrototype = find_Shader(pShaderTag);

	if (nullptr != pPrototype)
		return E_FAIL;

	m_mapPrototype.emplace(pShaderTag, pInstance);

	return S_OK;
}

Engine::CShader* Engine::CShaderMgr::Clone_Shader(const _tchar* pShaderTag)
{
	CShader*		pShader = find_Shader(pShaderTag);

	if (nullptr == pShader)
		return nullptr;

	return dynamic_cast<CShader*>(pShader->Clone());
}

Engine::CShader* Engine::CShaderMgr::find_Shader(const _tchar* pShaderTag)
{
	auto	iter = find_if(m_mapPrototype.begin(), m_mapPrototype.end(), CTag_Finder(pShaderTag));

	if (iter == m_mapPrototype.end())
		return nullptr;

	return iter->second;
}

void Engine::CShaderMgr::Free(void)
{
	for_each(m_mapPrototype.begin(), m_mapPrototype.end(), CDeleteMap());
	m_mapPrototype.clear();
}

