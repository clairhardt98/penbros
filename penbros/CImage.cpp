#include "pch.h"
#include "CImage.h"
#include "CCore.h"

CImage::CImage()
	:m_pImg(nullptr)
	,m_pImgAttr(nullptr)
	,m_fRot(0.f)
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
	//Gdiplus::Color targetColor(0, 0, 0, 0);
	m_pImgAttr = new Gdiplus::ImageAttributes;
	m_pImgAttr->SetColorKey(colorKey, colorKey, Gdiplus::ColorAdjustTypeDefault);
}

bool CImage::Rotate(Gdiplus::Graphics* _Grp, Vector2D _center, float _amount)
{
	using namespace Gdiplus;
	Gdiplus::Matrix mat;
	m_fRot += _amount;
	mat.RotateAt((m_fRot), Gdiplus::PointF(_center.x, _center.y));

	_Grp->SetTransform(&mat);
	
	if (abs(m_fRot) > 180.f)
	{
		//초과분만큼 다시 원래대로 돌려주는 로직
		if (m_fRot > 0)
		{
			mat.Reset();
			mat.RotateAt(180.0f-m_fRot, Gdiplus::PointF(_center.x, _center.y));
			_Grp->SetTransform(&mat);
		}
		else
		{
			mat.Reset();
			mat.RotateAt(m_fRot - 180.f, Gdiplus::PointF(_center.x, _center.y));
			_Grp->SetTransform(&mat);
		}
		mat.Reset();
		m_fRot = 0.f;
		return true;
	}
	mat.Reset();
	return false;
}

