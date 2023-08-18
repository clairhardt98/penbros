#pragma once
#include "CRes.h"
class CImage :
    public CRes
{
private:
    Gdiplus::Image* m_pImg;
    Gdiplus::ImageAttributes* m_pImgAttr;

public:
    void Load(const wstring& _strFilePath);
    void Rotate(Vector2D _center, float _amount);
    void Invert(Vector2D _center);
    Gdiplus::Image* GetImagePtr() { return m_pImg; }
    Gdiplus::ImageAttributes* GetImgAttr() { return m_pImgAttr; }

public:
    UINT Width() 
    { 
        if (nullptr != m_pImg)
            return m_pImg->GetWidth(); 
        else 
            return 0; 
    };
    UINT Height() 
    { 
        if (nullptr != m_pImg) 
            return m_pImg->GetHeight(); 
        else 
            return 0; 
    };

private:
    CImage();
    virtual ~CImage();

    friend class CResMgr;
};

