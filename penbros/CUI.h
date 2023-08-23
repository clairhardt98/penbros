#pragma once
#include "CObject.h"
class CTexture;
class CImage;
class CUI :
    public CObject
{
private:
    Vector2D m_vFontSize;
    //���� ��Ʈ
    CTexture* m_pNumFont;
    //���ĺ� ��Ʈ
    CTexture* m_pAlphabetFont;
    //�÷��̾� Idle�̹���
    CImage* m_pPlayerIdle;

private:
    int m_pPlayerCnt;

private:
    void RenderAlphabet(HDC _dc, Vector2D _vStartPos, wstring _str);
    void RenderNum(HDC _dc, Vector2D _vStartPos, int _num, int _size, int _interval);
    void DrawImage(Vector2D _vPos);
    
public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;

public:
    CLONE(CUI);
    CUI();
    ~CUI();
};

