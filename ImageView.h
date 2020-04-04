#pragma once
#include <vector>

using namespace std;
// CImageView 뷰입니다.
struct PIXEL_INFO
{
	CPoint pt;
	CPoint size;
	COLORREF color;
};

class CImageView : public CScrollView
{
	DECLARE_DYNCREATE(CImageView)

protected:
	CImageView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CImageView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	CPoint m_startPoint;		// 사각형 범위의 시작
	CPoint m_endPoint;			// 사각형 범위의 끝
	bool m_bMouseDown;			// 사각형 범위 지정을 위해 마우스를 눌렀나
	COLORREF m_ColorKey;		// 투명으로 선택한 색상
	bool m_bDrawSelect;			// 선택한 범위를 그려줘야 하는가
	CImage* m_pSelectedImage;	// 콘트롤뷰에서 선택한 이미지 정보 
	int m_iZoomRate;
	CPoint m_move_orgin;
	CPoint m_move_target;
	vector<PIXEL_INFO> m_vecPixel;
	HBITMAP m_hBackBitmap;
	BOOL m_ChangeCursor;
public:
	void SetSelectInfo(CPoint start, CPoint end);
	void SetSelectImage(LPWSTR strName);
	void ZoomIn();
	void ZoomOut();
	void CalcFrameRect();
private:
	bool CalcRect();		// 선택한 스프라이트 범위를 자동 계산
	PIXEL_INFO SetupStartPoint();
	int MoveWidth(PIXEL_INFO start_pixel);
	int MoveHeight(PIXEL_INFO start_pixel);
	bool IgnorSelectedColor(COLORREF _color);
	CPoint GetColorRect(COLORREF _color);
protected:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual void OnInitialUpdate();     // 생성된 후 처음입니다.
	virtual void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


