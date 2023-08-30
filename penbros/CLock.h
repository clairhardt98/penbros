#pragma once
#include "CObject.h"
class CTexture;
class CSound;
class CLock :
    public CObject
{
private:
    CTexture*   m_pIdleTex;
    CSound*     m_pOpenLockSound;
    bool        m_bIsOpened;
public:
    virtual void Update()override;
    virtual void Render(HDC _dc)override;
public:
    virtual void OnCollisionEnter(CCollider* _pOther)override;
public:
    CLONE(CLock);
    CLock();
    ~CLock();
};

