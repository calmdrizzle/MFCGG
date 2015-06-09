
// GraphicEditorDoc.h : CGraphicEditorDoc 클래스의 인터페이스
//


#pragma once
#include "Object.h"
#include "GEllipse.h"
#include "Line.h"
#include "GRectangle.h"
#include "PolyLine.h"


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
	PolyLine* GetPolyLine(BOOL bIsNew = FALSE);
	GraphicObjectType CurDrawType;	//현재 선택된 그리기 모드

	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);   // 문서 입/출력을 위해 재정의되었습니다.

	CPtrList& getDrawObjects();

	Line* getBeeLineDraw(bool bNew = FALSE);
	//FillDraw* getFillDraw(bool bNew = FALSE);
	//PencilDraw* getPencilDraw(bool bNew = FALSE);
	GEllipse* getEllipseDraw(bool bNew = FALSE);
	GRectangle* getRactangleDraw(bool bNew = FALSE);

// 작업입니다.
public:
	GraphicObjectType m_CurrentType;	//현재 그리기 타입
	CPoint m_ClickedPoint;				//현재 클릭한 포인트
	Object* m_CurrObject;				//
	GraphicObjectType m_CurrType;		//
	Object* m_sCurrObject;				//현재 그리는 그래피컬 개체
	
	CTypedPtrList<CObList, Object*> m_sGObjectList;	//그리기 저장 리스트




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
