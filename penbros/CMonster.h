#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
protected:
    float       m_fSpeed;
    int         m_iDir;
    bool        m_bDead;

public:
    void SetDead(bool _b);
    bool IsDead() { return m_bDead; }

protected:
    void Remove();
    
public:
    virtual void Update()override;

    CLONE(CMonster);

public:
    CMonster();
    virtual ~CMonster();
};

