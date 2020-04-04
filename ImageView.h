#pragma once
#include <vector>

using namespace std;
// CImageView ���Դϴ�.
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
	CImageView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CImageView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	CPoint m_startPoint;		// �簢�� ������ ����
	CPoint m_endPoint;			// �簢�� ������ ��
	bool m_bMouseDown;			// �簢�� ���� ������ ���� ���콺�� ������
	COLORREF m_ColorKey;		// �������� ������ ����
	bool m_bDrawSelect;			// ������ ������ �׷���� �ϴ°�
	CImage* m_pSelectedImage;	// ��Ʈ�Ѻ信�� ������ �̹��� ���� 
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
	bool CalcRect();		// ������ ��������Ʈ ������ �ڵ� ���
	PIXEL_INFO SetupStartPoint();
	int MoveWidth(PIXEL_INFO start_pixel);
	int MoveHeight(PIXEL_INFO start_pixel);
	bool IgnorSelectedColor(COLORREF _color);
	CPoint GetColorRect(COLORREF _color);
protected:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.
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


