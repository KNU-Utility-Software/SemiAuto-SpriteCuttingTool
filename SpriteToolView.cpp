
// SpriteToolView.cpp : CSpriteToolView Ŭ������ ����
//

#include "stdafx.h"
#include "SpriteTool.h"

#include "SpriteToolDoc.h"
#include "SpriteToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSpriteToolView

IMPLEMENT_DYNCREATE(CSpriteToolView, CView)

BEGIN_MESSAGE_MAP(CSpriteToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSpriteToolView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSpriteToolView ����/�Ҹ�

CSpriteToolView::CSpriteToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CSpriteToolView::~CSpriteToolView()
{
}

BOOL CSpriteToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CSpriteToolView �׸���

void CSpriteToolView::OnDraw(CDC* /*pDC*/)
{
	CSpriteToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CSpriteToolView �μ�


void CSpriteToolView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CSpriteToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CSpriteToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CSpriteToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CSpriteToolView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSpriteToolView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CSpriteToolView ����

#ifdef _DEBUG
void CSpriteToolView::AssertValid() const
{
	CView::AssertValid();
}

void CSpriteToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpriteToolDoc* CSpriteToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpriteToolDoc)));
	return (CSpriteToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CSpriteToolView �޽��� ó����
