#include "pch.h"
#include "CImage.h"
#include "CCore.h"

CImage::CImage()
	:m_pImg(nullptr)
	,m_pImgAttr(nullptr)
{
}

CImage::~CImage()
{
	delete m_pImg;
	delete m_pImgAttr;
}


void CImage::Load(const wstring& _strFilePath)
{
	m_pImg = Gdiplus::Image::FromFile(_strFilePath.c_str());
	Gdiplus::Color colorKey(255, 255, 0, 255);
	Gdiplus::Color targetColor(0, 0, 0, 0);
	m_pImgAttr = new Gdiplus::ImageAttributes;
	m_pImgAttr->SetColorKey(colorKey, colorKey, Gdiplus::ColorAdjustTypeDefault);
}

void CImage::Rotate(Vector2D _center, float _amount)
{
	using namespace Gdiplus;
	Graphics* pGr = CCore::GetInst()->GetGraphics();
	Gdiplus::Matrix mat;
	static float rot = 0;
	mat.RotateAt((rot), Gdiplus::PointF(_center.x, _center.y));

	pGr->SetTransform(&mat);
	rot += _amount;
	if (abs(rot) > 360.f)
		rot =0.f;
	//mat.Reset();
	//pGr->SetTransform(&mat);
}

void CImage::Invert(Vector2D _center)
{
	using namespace Gdiplus;
	Graphics* pGr = CCore::GetInst()->GetGraphics();
	Gdiplus::Matrix mat;
	mat.RotateAt(180.f, Gdiplus::PointF(_center.x, _center.y));
	pGr->SetTransform(&mat);
}
