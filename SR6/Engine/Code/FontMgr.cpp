#include "FontMgr.h"

#include "Engine_Entry.h"
#include "Transform.h"
USING(Engine)
IMPLEMENT_SINGLETON(CFontMgr)

CFontMgr::CFontMgr(void)
{
	m_pGraphicDev = Ready_GraphicDev()->GetDevice();
	m_pTransform = CTransform::Create();
}

CFontMgr::~CFontMgr(void)
{
	freeMem();
}

void CFontMgr::Register_Key(const _tchar cKey, const _tchar * pKeyPath)
{
	//auto iter = find_if(m_mapFont.begin(), m_mapFont.end(), cKey);

	//if (m_mapFont.end() != iter)
	//{
	//	return;
	//}

	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	D3DXCreateTextureFromFile(m_pGraphicDev, pKeyPath, (LPDIRECT3DTEXTURE9*)&pTexture);
	m_mapFont.emplace(cKey, pTexture);
}

void CFontMgr::Render_FontMgr(wstring & wStr, const _float & fInterval, const _vec3 * pPos)
{
	_int iStrSize = static_cast<_int>(wStr.size());
	
	_vec3 vPos;
	_matrix matTrans, matScale;

	for (_int i = 0; i < iStrSize; ++i)
	{

	}
}

void CFontMgr::freeMem()
{
	for_each(m_mapFont.begin(), m_mapFont.end(), CDeleteMap());
	m_mapFont.clear();
}
