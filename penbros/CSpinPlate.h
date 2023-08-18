#pragma once
#include "CPlatform.h"

class CCollider;

class CSpinPlate :
    public CPlatform
{
private:
    bool m_bIsSpinning;
public:
    virtual void OnCollisionEnter(CCollider* _pOther)override;
    virtual void OnCollision(CCollider* _pOther)override;

public:
    void SetSpinning(bool _b) { m_bIsSpinning = _b; }
public:
    CLONE(CSpinPlate);
    CSpinPlate();
    ~CSpinPlate();
};

