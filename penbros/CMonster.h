#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
private:
    float       m_fSpeed;
    int         m_iDir;


    
public:
    virtual void Update()override;

    CLONE(CMonster);

public:
    CMonster();
    ~CMonster();
};

