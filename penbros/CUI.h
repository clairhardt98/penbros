#pragma once
#include "CObject.h"
class CTexture;
class CImage;
class CUI :
    public CObject
{
private:
    Vector2D m_vFontSize;
    //숫자 폰트
    CTexture* m_pNumFont;
    //알파벳 폰트
    CTexture* m_pAlphabetFont;
    //플레이어 Idle이미지
    CImage* m_pPlayerIdle;

private:
    //출력할 정보
    

private:
    void RenderAlphabet(HDC _dc, Vector2D _vStartPos, wstring _str, int _size, int _interval);
    void RenderNum(HDC _dc, Vector2D _vStartPos, int _num, int _size, int _interval);
    void DrawPlayerImage(Vector2D _vPos);
    
public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;

public:
    CLONE(CUI);
    CUI();
    ~CUI();
};

