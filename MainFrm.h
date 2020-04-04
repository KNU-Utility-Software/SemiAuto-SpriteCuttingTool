
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once

class CControlView;
class CImageView;
class CFrameView;
//class CAnimView;
class CCenterView;

class CMainFrame : public CFrameWndEx
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CSplitterWnd	  m_wndSplitter1;	// ȭ�����
	CSplitterWnd	  m_wndSplitter2;
	//CSplitterWnd	  m_wndSplitter3;

private:
	CControlView* m_pControlView;
	CImageView* m_pImageView;
	CFrameView* m_pFrameView;
	//CAnimView* m_pAnimView;
public:
	CControlView* GetControlView() { return m_pControlView; }
	CImageView* GetImageView() { return m_pImageView; }
	CFrameView* GetFrameView() { return m_pFrameView; }
	//CAnimView* GetAnimView() { return m_pAnimView; }

// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnClose();
};


