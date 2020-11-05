#ifndef PtTex_h__
#define PtTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CPtTex : public CVIBuffer
{
private:
	explicit						CPtTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CPtTex(const CPtTex& rhs);
	virtual							~CPtTex(void);

public:
	virtual HRESULT					Initialize_Buffer(void) override;
	virtual void					Render_Buffer(LPDIRECT3DVERTEXBUFFER9 pVB = nullptr)override;

private:
	LPDIRECT3DVERTEXBUFFER9			m_pVBTransform;		// 기존 정점 정보를 복제하기 위한 VB 자료형
	LPDIRECT3DVERTEXDECLARATION9	m_pDeclaration;	// 버텍스 쉐이더로 입력되는 정점의 데이터 정보를 나타낸다. 즉, 위치, 컬러, 법선 등 보통의 데이터 선언은 FVF로 대신 할 수 있어서 FVF를 사용하는 경우가 더 많다.

public:
	static CPtTex*					Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CResources*				Clone(void) override;

private:
	inline virtual void				Free(void);
};

END
#endif // PtTex_h__
