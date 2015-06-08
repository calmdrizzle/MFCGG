
// GraphicEditorDoc.h : CGraphicEditorDoc 클래스의 인터페이스
//


#pragma once
#include "Object.h"
#include "GEllipse.h"
#include "Line.h"
#include "GRectangle.h"


class CGraphicEditorDoc : public CDocument
{
private:
	CPtrList m_DrawObjs;
	Object* m_Cur;

protected: // serialization에서만 만들어집니다.
	CGraphicEditorDoc();
	DECLARE_DYNCREATE(CGraphicEditorDoc)

// 특성입니다.
public:
	Line* GetLine(BOOL bIsNew = FALSE);
	GRectangle* GetGRectangle(BOOL bIsNew = FALSE);

// 작업입니다.
public:
	GraphicObjectType m_CurrentType;	//현재 그리기 타입
	CPoint m_ClickedPoint;				//현재 클릭한 포인트
	Object* m_CurrObject;				//
	GraphicObjectType m_CurrType;		//



// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CGraphicEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
