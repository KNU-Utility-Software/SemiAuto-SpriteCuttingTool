#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CControlView 폼 뷰입니다.

class CControlView : public CFormView
{
	DECLARE_DYNCREATE(CControlView)

protected:
	CControlView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CControlView();
	 
public:
	enum { IDD = IDD_CONTROLVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	CListCtrl m_ImageList;
	CListCtrl m_SpriteList;
	int m_iTileWidth;
	int m_iTileHeight;
public:
	void SetSelectInfo(CPoint start, CPoint end);
	void UpdateImageList();
	void UpdateSpriteList();
	void SetRectInfo(int w, int h);
	void SetFrameIndex(int idx);
	void SetEditFrame(wchar_t* str_frame_name);
	void GetEditFrame(wchar_t* str_frame_name);
private:
	void ChangeSelectInfo();
	void UpdateSelectSprite();
	 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditSelectLeft();
	afx_msg void OnEnChangeEditSelectTop();
	afx_msg void OnEnChangeEditSelectRight();
	afx_msg void OnEnChangeEditSelectBottom();
	virtual void OnInitialUpdate();
	afx_msg void OnNMClickListImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAddSprite();
	afx_msg void OnBnClickedButtonSelectAdd();
	afx_msg void OnNMClickListSprite(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDeleteSprite();
	afx_msg void OnBnClickedButtonDeleteImage();
	afx_msg void OnBnClickedButtonSaveSprite();
	afx_msg void OnBnClickedButtonLoadSprite();
	afx_msg void OnBnClickedZoomIn();
	afx_msg void OnBnClickedZoomOut2();
	afx_msg void OnEnChangeEditTileX();
	afx_msg void OnEnChangeEditTileY();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChangeEditFrame();
};


