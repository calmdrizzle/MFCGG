#pragma once

#include "stdafx.h"
#include "Object.h"

class GPLine : public Object
{
public:
	GPLine();
	void virtual draw(CDC*);
	void virtual move(int dx, int dy);
	void virtual set(int left, int top, int right, int bottom);

	void drawBoundary(CDC*);
	CRect virtual getBoundary();

	bool virtual isin(CPoint p);

	void setArr();
	void complete();

	void onePointdel();

	void virtual serialize(CArchive& ar, bool serialize_flag);
private:
	CArray<CPoint, CPoint&> pt_arr;
	int pt_num;


};