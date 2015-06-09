
// GraphicEditorDoc.h : CGraphicEditorDoc Ŭ������ �������̽�
//


#pragma once
#include "Object.h"
#include "GEllipse.h"
#include "Line.h"
//#include "GRectangle.h"


class CGraphicEditorDoc : public CDocument
{
private:
	CPtrList m_DrawObjs;
	Object* m_Cur;

protected: // serialization������ ��������ϴ�.
	CGraphicEditorDoc();
	DECLARE_DYNCREATE(CGraphicEditorDoc)

// Ư���Դϴ�.
public:
	Line* GetLine(bool bIsNew = FALSE);
	
	//GRectangle* GetGRectangle(BOOL bIsNew = FALSE);
	GraphicObjectType CurDrawType;	//���� ���õ� �׸��� ���

	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);   // ���� ��/����� ���� �����ǵǾ����ϴ�.

	CPtrList& getDrawObjects();

	//FillDraw* getFillDraw(bool bNew = FALSE);
	//PencilDraw* getPencilDraw(bool bNew = FALSE);
	GEllipse* GetEllipse(bool bNew = FALSE);

// �۾��Դϴ�.
public:
	GraphicObjectType m_CurrentType;	//���� �׸��� Ÿ��
	CPoint m_ClickedPoint;				//���� Ŭ���� ����Ʈ
	Object* m_CurrObject;				//
	GraphicObjectType m_CurrType;		//
	Object* m_sCurrObject;				//���� �׸��� �׷����� ��ü
	
	CTypedPtrList<CObList, Object*> m_sGObjectList;	//�׸��� ���� ����Ʈ




// �������Դϴ�.
public:

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CGraphicEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
