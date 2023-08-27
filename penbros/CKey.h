#pragma once
#include "CObject.h"
class CKey :
    public CObject
{
public:
    CObject*    m_pPlayer;
    bool        m_bIsCaptured;
public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;
public:
    virtual void OnCollisionEnter(CCollider* _pOther)override;
public:
    CLONE(CKey);
    CKey();
    ~CKey();
};

