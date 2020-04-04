#pragma once

// CFrameView ���Դϴ�.

class CSpriteInfo;

class CFrameView : public CScrollView
{
	DECLARE_DYNCREATE(CFrameView)

protected:
	CFrameView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.
	int GetFrameIndex(CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


