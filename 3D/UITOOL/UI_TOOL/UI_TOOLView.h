
// UI_TOOLView.h: CUITOOLView 클래스의 인터페이스
//

#pragma once


class CUITOOLView : public CView
{
protected: // serialization에서만 만들어집니다.
	CUITOOLView() noexcept;
	DECLARE_DYNCREATE(CUITOOLView)

// 특성입니다.
public:
	CUITOOLDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CUITOOLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // UI_TOOLView.cpp의 디버그 버전
inline CUITOOLDoc* CUITOOLView::GetDocument() const
   { return reinterpret_cast<CUITOOLDoc*>(m_pDocument); }
#endif

