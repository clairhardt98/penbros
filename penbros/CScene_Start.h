#pragma once
#include "CScene.h"

class CTexture;
class CSound;
class CImage;
class CScene_Start :
    public CScene
{
private:
    CTexture*           m_pBGTex;
    CSound*             m_pBGSound;
    Gdiplus::Image*     m_pTitleImg;
    Gdiplus::Image*     m_pTitleLineImg;
    Gdiplus::Graphics*  m_pGr;
public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;
    virtual void Enter()override;
    virtual void Exit()override;
public:
    CScene_Start();
    ~CScene_Start();
};

