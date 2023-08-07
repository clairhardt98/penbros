#pragma once
//펜과 브러시를 선택해주는 임시 객체 생성용도
class SelectGDI
{
private:
	HDC		m_hdc;
	HPEN	m_hDefaultPen;
	HBRUSH	m_hDefaultBrush;
public:
	SelectGDI(HDC _dc, PEN_TYPE _ePenType);
	SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType);
	~SelectGDI();
};

