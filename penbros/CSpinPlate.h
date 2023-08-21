#pragma once
#include "CPlatform.h"

class CCollider;
class CImage;

class CSpinPlate :
    public CPlatform
{
private:
    bool        m_bIsSpinning;
    int         m_bSpinClockwise;
    CImage*     pImg;
public:
    virtual void OnCollisionEnter(CCollider* _pOther)override;
    virtual void OnCollision(CCollider* _pOther)override;
    virtual void Update()override;
    virtual void Render(HDC _dc)override;
    

public:
    void SetSpinning(bool _b) { m_bIsSpinning = _b; }
    void DrawImage();
    void RotateImage();
public:
    CLONE(CSpinPlate);
    CSpinPlate();
    ~CSpinPlate();
};

