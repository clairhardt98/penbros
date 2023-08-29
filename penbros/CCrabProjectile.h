#pragma once
#include "CObject.h"

class CTexture;

class CCrabProjectile :
    public CObject
{
private:
    int			m_iDir;
    CTexture*   m_pTexRight;
    CTexture*   m_pTexLeft;
public:
    void SetDirection(int _dir) { m_iDir = _dir; }
public:
    virtual void Update() override;
    virtual void Render(HDC _dc)override;
public:
    virtual void OnCollisionEnter(CCollider* _pOther)override;

public:
    CLONE(CCrabProjectile);
    CCrabProjectile();
    ~CCrabProjectile();
};

