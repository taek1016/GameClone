// MiniView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MiniView.h"
#include "ToolView.h"

// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
	: m_pTerrain(nullptr)
{
}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView �׸����Դϴ�.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
	CSINGLETON::pDirectMgr->Render_Begin();

	m_pTerrain->MiniRender();
	
	CSINGLETON::pDirectMgr->Render_End(m_hWnd);
}


// CMiniView �����Դϴ�.

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView �޽��� ó�����Դϴ�.


void CMiniView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CSplitterWnd* pSplitterWnd = dynamic_cast<CSplitterWnd*>(GetParentSplitter(this, FALSE)->GetParent());
	m_pTerrain = dynamic_cast<CToolView*>(pSplitterWnd->GetPane(0, 1))->GetTerrain();
	m_vecTile = m_pTerrain->GetTerrain();
}