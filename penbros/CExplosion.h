#pragma once
#include "CObject.h"

class CCollider;
class CSound;
class CExplosion :
    public CObject
{
private:
    CSound* m_pExplosionSound;
private:

    virtual void Update()override;
    virtual void Render(HDC _dc)override;
private:
    virtual void OnCollisionEnter(CCollider* _pOther)override;
public:
    CLONE(CExplosion);
    CExplosion();
    ~CExplosion();
};

