#pragma once
#include "CObject.h"
class CLock :
    public CObject
{
public:
    virtual void Update()override;
    //virtual void Render(HDC _dc)override;
public:
    virtual void OnCollisionEnter(CCollider* _pOther)override;
public:
    CLONE(CLock);
    CLock();
    ~CLock();
};

