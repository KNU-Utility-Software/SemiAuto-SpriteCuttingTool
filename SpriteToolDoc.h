
// SpriteToolDoc.h : CSpriteToolDoc Ŭ������ �������̽�
//


#pragma once


class CSpriteToolDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CSpriteToolDoc();
	DECLARE_DYNCREATE(CSpriteToolDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CSpriteToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


