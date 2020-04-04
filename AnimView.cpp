// AnimView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SpriteTool.h"
#include "AnimView.h"
#include "SpriteManager.h"
#include "FrameInfo.h"
// CAnimView

IMPLEMENT_DYNCREATE(CAnimView, CScrollView)

CAnimView::CAnimView()
{

}

CAnimView::~CAnimView()
{

}


BEGIN_MESSAGE_MAP(CAnimView, CScrollView)
	ON_WM_CREATE()
END_MESSAGE_MAP()

void CAnimView::SetSpritInfo(CSpriteInfo* pSpriteInfo)
{
	m_pSeletedSprite = pSpriteInfo; 

	Invalidate(TRUE);
}

// CAnimView 그리기입니다.

void CAnimView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CAnimView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	if (!m_pSeletedSprite)
		return;

	// 프레임 정보 출력
	CImage* pImage = m_pSeletedSprite->GetImage();

	if (!pImage)
		return;

	VEC_FRAMEINFO& vecFrameInfo = m_pSeletedSprite->GetFrameInfoList();
	int width = 0;
	int height = 0;
	VEC_FRAMEINFO_ITER iter = vecFrameInfo.begin();
	LONGLONG current_time = GetTickCount64();
	for ( int i = 0; iter != vecFrameInfo.end();)
	{
		FRAME_INFO* pFrame = *iter;
		LONGLONG last_time = current_time;
		LONGLONG current_time = GetTickCount64();
		LONGLONG elapsed_time = current_time - last_time;
		static LONGLONG total_elapsed_time = 0;
		total_elapsed_time += elapsed_time;

		if(total_elapsed_time >= (pFrame->aniTime*1000))
		{
			total_elapsed_time = 0;

			pImage->BitBlt(pDC->m_hDC, 
				50, 
				50, 
				pFrame->rect.Width(), 
				pFrame->rect.Height(), 
				pFrame->rect.left, 
				pFrame->rect.top, 
				SRCCOPY);
			//WCHAR strTmp[20];
			//_itow_s(i, strTmp, 10);
			//pDC->TextOut(LEFT_MARGIN + width, TOP_MARGIN + pFrame->rect.Height() + 2, strTmp);

			//width += pFrame->rect.Width() + LEFT_MARGIN;
			//height = max(height, pFrame->rect.Height()); 
			/*Invalidate(TRUE);*/
			++iter; 
			i++;
		}
	}
}


// CAnimView 진단입니다.

#ifdef _DEBUG
void CAnimView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CAnimView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAnimView 메시지 처리기입니다.

int CAnimView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	return 0;
}
