#pragma once
#include "CObject.h"
class CPlatform :
    public CObject
{
public:
    virtual void Start()override;
    virtual void Update()override;
    virtual void Render(HDC _dc)override;
public:
    virtual void OnCollision(CCollider* _pOther)override;
    virtual void OnCollisionExit(CCollider* _pOther)override;
public:
    CLONE(CPlatform);
    CPlatform();
    ~CPlatform();
};

