#ifndef __TERRAIN_H__
#include "..\D2DDungreed\Object\GameObject.h"

class CTerrain : public CGameObject
{
private:
	CTerrain();

public:
	virtual ~CTerrain();

	static	CTerrain*	Create();
	static	CTerrain*	Create(const std::wstring& wstrPath);

	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render()		override;

	void MiniRender();
	// 맵 툴에서 활용할 것들
	void RenderMapTool();
	void RenderTileOption();

	void TileChange
	(
		const D3DXVECTOR3&	vPos, 
		const BYTE&			byDrawID 
	);
	void TileOptionChange(const D3DXVECTOR3&	vPos);

	const TILE_INFO* GetTileInfo				(const int index) const
	{
		return m_vecTile[index];
	}
	const std::vector<TILE_INFO*>& GetTerrain	() const
	{
		return m_vecTile;
	}

	void MakeTile();
	void SaveTile(const TCHAR* pFilePath);
	void LoadTile(const TCHAR* pFilePath);

	int FindTile(const D3DXVECTOR3& vecPos);

private:
	virtual void UpdateRect	() override;

public:
	static const int g_TileCountX;
	static const int g_TileCountY;

private:
	std::vector<TILE_INFO*>	m_vecTile;

	D3DXMATRIX				m_matScale;
	D3DXMATRIX				m_matMove;
};

#define __TERRAIN_H__
#endif // !__TERRAIN_H__