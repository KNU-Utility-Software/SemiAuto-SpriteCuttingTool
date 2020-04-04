#pragma once

// CFrameView 뷰입니다.

class CSpriteInfo;

class CFrameView : public CScrollView
{
	DECLARE_DYNCREATE(CFrameView)

protected:
	CFrameView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CFrameView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	enum
	{
		LEFT_MARGIN = 20,
		TOP_MARGIN = 20
	};

private:
	CSpriteInfo* m_pSeletedSprite;
	int m_frame_index;
public:
	void SetSpritInfo(CSpriteInfo* pSpriteInfo);
	void SetFrameName(wchar_t* str_frame_name);
protected:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual void OnInitialUpdate();     // 생성된 후 처음입니다.
	int GetFrameIndex(CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


