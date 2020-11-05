#ifndef PrototypeMgr_h__
#define PrototypeMgr_h__

#include "Engine_Defines.h"
#include "Base.h"
#include "Component.h"

BEGIN(Engine)

class CShader;

class ENGINE_DLL CShaderMgr : public CBase
{
	DECLARE_SINGLETON(CShaderMgr)

private:
	explicit			CShaderMgr(void);
	virtual				~CShaderMgr(void);

public:
	HRESULT				Initialize_Shaders(const _tchar* pShaderTag, CShader* pInstance);
	CShader*			Clone_Shader(const _tchar* pShaderTag);

private:
	CShader*			find_Shader(const _tchar* pShaderTag);

private:
	map<const _tchar*, CShader*>	m_mapPrototype;
public:
	virtual void					Free(void);
};

END
#endif // PrototypeMgr_h__
