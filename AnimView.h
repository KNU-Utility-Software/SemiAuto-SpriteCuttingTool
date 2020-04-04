#pragma once

#include "SpriteInfo.h"

// CAnimView ���Դϴ�.

class CAnimView : public CScrollView
{
	DECLARE_DYNCREATE(CAnimView)

protected:
	CAnimView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CAnimView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	CSpriteInfo* m_pSeletedSprite;

protected:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.
	

	DECLARE_MESSAGE_MAP()
public:
	void SetSpritInfo(CSpriteInfo* pSpriteInfo);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


