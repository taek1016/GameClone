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
	LPDIRECT3DVERTEXBUFFER9			m_pVBTransform;		// ���� ���� ������ �����ϱ� ���� VB �ڷ���
	LPDIRECT3DVERTEXDECLARATION9	m_pDeclaration;	// ���ؽ� ���̴��� �ԷµǴ� ������ ������ ������ ��Ÿ����. ��, ��ġ, �÷�, ���� �� ������ ������ ������ FVF�� ��� �� �� �־ FVF�� ����ϴ� ��찡 �� ����.

public:
	static CPtTex*					Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CResources*				Clone(void) override;

private:
	inline virtual void				Free(void);
};

END
#endif // PtTex_h__
