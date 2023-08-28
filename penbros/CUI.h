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
    //COOL! �̹���
    CTexture* m_pCOOLimg;
    CTexture* m_pGameOverImg;
    //�÷��̾� Idle�̹���
    CImage* m_pPlayerIdle;

private:
    //����� ����
    bool m_bStageCleared;
    bool m_bGameOvered;
    

private:
    void RenderAlphabet(HDC _dc, Vector2D _vStartPos, wstring _str, int _size, int _interval);
    void RenderNum(HDC _dc, Vector2D _vStartPos, int _num, int _size, int _interval);
    void DrawPlayerImage(Vector2D _vPos);
    
    void RenderCOOLImg(HDC _dc);
    void RenderGameOverImg(HDC _dc);
public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;
    void SetCleared(bool _b) { m_bStageCleared = _b; }
    void SetGameOvered(bool _b) { m_bGameOvered = _b; }
public:
    CLONE(CUI);
    CUI();
    ~CUI();
};

